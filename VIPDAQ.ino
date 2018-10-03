
const unsigned long ONE_SECOND = 500UL; //500 = 1 per second. 
const unsigned long FIVE_SECONDS = (ONE_SECOND * 5); //168.39 .46 .59
const unsigned long THIRTY_SECONDS = (ONE_SECOND * 30); //168.39 .46 .59
const unsigned long ONE_MINUTE = (ONE_SECOND * 60); //168.77
const unsigned long FIVE_MINUTES = (ONE_MINUTE * 5); //160.76 168.39 168.46 156.79 149 165 150 164 168 (1h 36m)
const unsigned long HALF_HOUR = (ONE_MINUTE * 30); //163.88

const unsigned long SingleLoopSize = FIVE_SECONDS;
const unsigned long LoopRepeats = 1;

//30 Minutes
//00:30:26 - 163.88mA
//01:00:39 - 166.63mA
//01:06:31 - 155.49mA

//1,800,000ms (30m)
/*
00:30 : 27 - 147.48mA
01 : 00 : 55 - 142.60mA
01 : 31 : 22 - 144.73mA
02 : 01 : 50 - 135.35mA
02 : 32 : 18 - 132.83mA
03 : 02 : 46 - 132.83mA
03 : 33 : 13 - 131.54mA
04 : 03 : 41 - 131.38mA
04 : 34 : 09 - 133.98mA
05:04 : 37 - 130.77mA
05 : 35 : 04 - 131.31mA
06 : 05 : 32 - 131.38mA
06 : 36 : 00 - 131.61mA
07 : 06 : 28 - 143.74mA
07 : 36 : 56 - 129.63mA
08 : 07 : 23 - 132.83mA
08 : 37 : 51 - 132.15mA
09 : 08 : 19 - 135.35mA
09 : 38 : 47 - 132.07mA
10 : 09 : 14 - 132.99mA
10 : 39 : 42 - 130.85mA
11 : 10 : 10 - 131.08mA
11 : 40 : 38 - 133.90mA
12 : 11 : 06 - 131.00mA
12 : 41 : 34 - 133.82mA
13 : 12 : 01 - 130.85mA
13 : 42 : 29 - 131.84mA
14 : 12 : 57 - 131.99mA
14 : 43 : 25 - 143.74mA
15 : 13 : 53 - 132.30mA
15 : 44 : 20 - 129.02mA
16 : 14 : 48 - 143.29mA
16 : 45 : 16 - 154.42mA
17 : 15 : 44 - 151.91mA
17 : 46 : 12 - 166.86mA
18 : 16 : 39 - 166.63mA
*/



#include <AD770X.h>

AD770X ad7705(65535); 

unsigned long zerotime;

void setup()
{
	Serial.begin(9600);
	ad7705.reset();
	ad7705.init(AD770X::CHN_AIN1);
	//ad7705.init(AD770X::CHN_AIN2);

	Serial.print ("Sample window @ 500sps :");
	Serial.print(SingleLoopSize*LoopRepeats*2);
	Serial.println("ms");
	Serial.println("H:M:S - mA");

	zerotime = millis();
}


void loop()
{
	
	unsigned long accumulator;
	accumulator = 0;

	for (unsigned long n = 0; n < LoopRepeats; n++)
	{
		for (unsigned long i = 0; i < SingleLoopSize; i++)
		{
			accumulator += ad7705.readADResult(AD770X::CHN_AIN1);
		}
		Serial.print(".");
	}
	Serial.println("");

	delay(500);
	float a = accumulator / (SingleLoopSize * LoopRepeats);
	float millivolts = ((a*0.000076295109)-0.00076)*1000;

	Serial.print(DurationInHMSstring());
	Serial.print(" - ");
	Serial.print(millivolts, 2);
	Serial.println("mA");
	delay(500);

}

char * DurationInHMSstring()
{
	return MilliSecondsToHMSstring(millis() - zerotime);
}

char * MilliSecondsToHMSstring(unsigned long time_in_ms)
{
	return SecondsToHMSstring(time_in_ms / 1000);
}

char * SecondsToHMSstring(unsigned long time_in_seconds)
{
	static char str[12];

	unsigned long h = time_in_seconds / 3600;
	unsigned long d = h / 24;
	time_in_seconds = time_in_seconds % 3600;
	int m = time_in_seconds / 60;
	int s = time_in_seconds % 60;
	sprintf(str, "%02ld:%02d:%02d", h, m, s);
	return str;
}


