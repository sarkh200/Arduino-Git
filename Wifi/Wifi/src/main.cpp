#include <Arduino.h>
#include <WiFi.h>

void wifiScanner(){
  int numbOfNetworks = WiFi.scanNetworks();
  Serial.print("There are ");
  Serial.print(numbOfNetworks);
  Serial.println(" network(s) available.");

  for(int i = 0; i < numbOfNetworks; i++){
    Serial.print(WiFi.SSID(i));
    Serial.print("(");
    Serial.print(WiFi.RSSI(i));
    Serial.println(")");
  }
  Serial.println();
}

// put your setup code here, to run once:
void setup() {
  Serial.begin(115200);
}

// put your main code here, to run repeatedly:
void loop() {
  wifiScanner();
}