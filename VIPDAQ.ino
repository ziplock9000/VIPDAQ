
#include <AD770X.h>

// Init the ADC. The value in parenthesis is the scaler
AD770X ad7705(65536); //AD770X ad7706(2.5);

void setup()
{
	ad7705.reset();
	ad7705.init(AD770X::CHN_AIN1);	//Ch1
	ad7705.init(AD770X::CHN_AIN2);	//Ch2
	Serial.begin(9600);
}


void loop()
{
	unsigned int ADCValue1, ADCValue2;
	byte b1, b2;

	ADCValue1 = ad7705.readADResult(AD770X::CHN_AIN1);
	ADCValue2 = ad7705.readADResult(AD770X::CHN_AIN2);
	Serial.print(ADCValue1);
	Serial.print(":");
	Serial.println(ADCValue2);

	// Convert data to 2 bytes for sending
	//b1 = ADCValue & 0xFF;
	//b2 = (ADCValue >> 8) & 0xFF;
	delay(1000);
}