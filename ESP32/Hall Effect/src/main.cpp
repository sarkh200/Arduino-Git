#include <Arduino.h>
#include <WiFi.h>
#include <WebHTML.h>
#define SSID "****"
#define password "****"
#define hostName "ESP32-WROOM-32"

WiFiServer server(80);
WiFiClient client;
String request;

// put your setup code here, to run once:
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostName);
  WiFi.begin(SSID, password);
  WiFi.waitForConnectResult();
  Serial.print("Connected as: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

// put your main code here, to run repeatedly:
void loop()
{
  client = server.available();
  if (!client)
  {
    return;
  }

  while (client.connected())
  {
    if (client.available())
    {
      char c = client.read();
      request += c;

      if (c == '\n')
      {
        client.println(PAGE1);
        client.print(touchRead(4));
        client.println(PAGE2);
        break;
      }
    }
  }

  delay(1);
  request = "";
  client.stop();
}