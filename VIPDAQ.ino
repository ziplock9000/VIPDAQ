
const unsigned long ONE_SECOND = 500UL; //500 = 1 per second. 
const unsigned long FIVE_SECONDS = (ONE_SECOND * 5); //168.39 .46 .59
const unsigned long ONE_MINUTE = (ONE_SECOND * 60); //168.77
const unsigned long FIVE_MINUTES = (ONE_MINUTE * 5); //160.76 168.39 168.46 156.79 149 165 150 164 168 (1h 36m)
const unsigned long HALF_HOUR = (ONE_MINUTE * 30); //163.88

//30 Minutes
//00:30:26 - 163.88mA
//01:00:39 - 166.63mA
//01:06:31 - 155.49mA

const unsigned long LoopSize = HALF_HOUR;

#include <AD770X.h>

// Init the ADC. The value in parenthesis is the scaler
AD770X ad7705(2.5); //AD770X ad7706(2.5);

unsigned long zerotime;

void setup()
{
	Serial.begin(9600);
	ad7705.reset();
	ad7705.init(AD770X::CHN_AIN1);
	//ad7705.init(AD770X::CHN_AIN2);

	Serial.print ("Sample window :");
	Serial.print(LoopSize);
	Serial.println("ms");
	Serial.println("H:M:S - mA");

	zerotime = millis();
}


void loop()
{
	
	unsigned long accumulator;
	accumulator = 0;

	for(unsigned long i=0;i<LoopSize;i++)
	{
		accumulator += ad7705.readADResult(AD770X::CHN_AIN1);
	}
	float a = accumulator / LoopSize;
	float millivolts = ((a*0.000076295109)-0.00076)*1000;

	Serial.print(DurationInHMSstring());
	Serial.print(" - ");
	Serial.print(millivolts, 2);
	Serial.println("mA");

	/*
	unsigned int ADCValue1 = ad7705.readADResult(AD770X::CHN_AIN1);
	unsigned int ADCValue2 = ad7705.readADResult(AD770X::CHN_AIN2);
	Serial.print(ADCValue1);
	Serial.print(":");
	Serial.println(ADCValue2);
	delay(1000);
	*/
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


