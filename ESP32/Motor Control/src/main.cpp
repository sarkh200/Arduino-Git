#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo;

int val;
int servoPin = 18;
int potPin = 34;
int ADC_Max = 4096; 

void setup()
{
  servo.setPeriodHertz(50);// Standard 50hz servo
  servo.attach(servoPin, 500, 2400);
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop()
{
  val = analogRead(potPin);            // read the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, ADC_Max, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  servo.write(val);                  // set the servo position according to the scaled value
  delay(200);                          // wait for the servo to get there
}