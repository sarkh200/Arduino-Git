#include <Arduino.h>
#include <ESP32Servo.h>

const int pinout1 = 18;
const int pinout2 = 18;
const int pinout3 = 18;

Servo servo;

void setup()
{
	Serial.begin(115200);
	servo.attach(pinout1, 500, 2400);
	servo.setPeriodHertz(50);
	servo.write(0);
}

void loop()
{
	for (int i = 0; i < 6; i++)
	{
		servo.write(i * 45);
		Serial.println(i * 45);
		delay(1000);
	}
}