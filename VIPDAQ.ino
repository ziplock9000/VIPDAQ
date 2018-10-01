
const unsigned long ONE_SECOND = 500UL; //500 = 1 per second. 
const unsigned long FIVE_SECONDS = (ONE_SECOND * 5);
const unsigned long ONE_MINUTE = (ONE_SECOND * 60);
const unsigned long FIVE_MINUTES = (ONE_MINUTE * 5);
const unsigned long LoopSize = FIVE_SECONDS;

#include <AD770X.h>

// Init the ADC. The value in parenthesis is the scaler
AD770X ad7705(2.5); //AD770X ad7706(2.5);

void setup()
{
	Serial.begin(9600);
	ad7705.reset();
	ad7705.init(AD770X::CHN_AIN1);
	//ad7705.init(AD770X::CHN_AIN2);

}


void loop()
{
	
	unsigned long accumulator;
	accumulator = 0;

	for(int i=0;i<LoopSize;i++)
	{
		accumulator += ad7705.readADResult(AD770X::CHN_AIN1);
	}
	float a = accumulator / LoopSize;
	float b = (a*0.000076295109)-0.002289;
	Serial.print(b,6);
	Serial.println('v');
	

	/*
	unsigned int ADCValue1 = ad7705.readADResult(AD770X::CHN_AIN1);
	unsigned int ADCValue2 = ad7705.readADResult(AD770X::CHN_AIN2);
	Serial.print(ADCValue1);
	Serial.print(":");
	Serial.println(ADCValue2);
	delay(1000);
	*/
}