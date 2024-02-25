#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "PrivateInfo.h"

#define MaxMessageLength 100

// PubSubClient instance
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length);

void setup()
{
  Serial.begin(115200);

  delay(20);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (!WiFi.isConnected())
  {
    Serial.print(".");
    delay(50);
  }
  Serial.println();
  Serial.printf("Connected to %s as ", WiFi.SSID());
  Serial.println(WiFi.localIP());

  Serial.print("Connecting to MQTT broker: ");
  Serial.println(mqtt_broker);
  client.setServer(mqtt_broker, mqtt_port);

  while (!client.connected())
  {
    if (client.connect(client_id))
    {
      Serial.println("Connected to MQTT broker!");
    }
    else
    {
      Serial.printf("Connection failed to MQTT broker; client state = %d\n Trying again in 10 seconds...", client.state());
      delay(10000);
    }
  }

  client.setCallback(callback);

  Serial.printf("Subscribing to topic: %s\n", subTopic);
  client.subscribe(subTopic);
  Serial.printf("Subscribed to: %s\n", subTopic);
}

void loop()
{
  client.loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
  char message[12] = {'0'};
  int r = 0, g = 0, b = 0;

  if (length > MaxMessageLength)
  {
    length = MaxMessageLength - 1;
  }
  for (int i = 0; i < length; i++)
  {
    message[i] = (char)payload[i];
  }

  sscanf(message, "%d %d %d", &r, &g, &b);

  neopixelWrite(RGB_BUILTIN, r, g, b);
}