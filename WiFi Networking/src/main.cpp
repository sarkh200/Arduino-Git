#include <Arduino.h>
#include <WiFi.h>
#define ssid "Test"
#define pass "password12"

WiFiServer server(23);
bool alreadyConnected = false;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAP("Test", "password12");
  WiFi.begin();
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();

  if(client){
    if(!alreadyConnected){
      client.flush();
      Serial.println("We have a new client!");
      client.println("Hello!");
      alreadyConnected = true;
    }

    if(client.available() > 0){
      char thisChar = client.read();
      server.write(thisChar);
      Serial.write(thisChar);
    }
  }
}