#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#define SSID "Don't Hack me"
#define PASS "Robot123!"

void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);
}

void loop()
{
  
}