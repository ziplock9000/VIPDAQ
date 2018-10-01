
#define LoopSize 500UL //500 = 1 per second. 
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
	Serial.print((accumulator / LoopSize)*0.000076295109);
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