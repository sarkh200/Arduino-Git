#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ESP32_New_ISR_Servo.h>

/* Create PrivateInfo.h in in ./include with values for:
    char ssid[]
    char password[]
    int mqtt_broker
    int mqtt_port
    char client_id[]
    char subTopic[]*/
#include "PrivateInfo.h"

#define motorPin1 4
#define motorPin2 5
#define motorPin3 6

// Arbitrary length for maximum length of message that can be read from topic (Can be changed to any value)
#define MaxMessageLength 100

// PubSubClient instance
WiFiClient espClient;
PubSubClient client(espClient);

// Function prototypes here:
void callback(char *topic, byte *payload, unsigned int length);

int servoIndex1 = -1;
int servoIndex2 = -1;
int servoIndex3 = -1;

void setup()
{
  // Begin Serial
  Serial.begin(115200);

  delay(20);

  ESP32_ISR_Servos.useTimer(3);

  servoIndex1 = ESP32_ISR_Servos.setupServo(4);
  servoIndex2 = ESP32_ISR_Servos.setupServo(5);
  servoIndex3 = ESP32_ISR_Servos.setupServo(6);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (!WiFi.isConnected())
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.printf("Connected to %s as ", WiFi.SSID());
  Serial.println(WiFi.localIP());

  // Connect to MQTT
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

  // Set function to run on message received
  client.setCallback(callback);

  // Subscribe to topic
  Serial.printf("Subscribing to topic: %s\n", subTopic);
  client.subscribe(subTopic);
  Serial.printf("Subscribed to: %s\n", subTopic);
}

void loop()
{
  // Must be run to keep connection alive
  client.loop();
}

// Gets run everytime a new message is published
void callback(char *topic, byte *payload, unsigned int length)
{
  // char array to store payload
  char message[MaxMessageLength] = {'0'};
  // ints to store rgb values
  float x = 0, y = 0, z = 0;

  // Trims message down to be under MaxMessageLength
  if (length > MaxMessageLength)
  {
    length = MaxMessageLength - 1;
  }
  // Stored payload as char[]
  for (int i = 0; i < length; i++)
  {
    message[i] = (char)payload[i];
  }

  // Gets servo values from message
  sscanf(message, "%f %f %f", &x, &y, &z);

  // Sets onboard LED to values defined in message
  Serial.printf("Setting arm to: (%f, %f, %f)\n", x, y, z);
  ESP32_ISR_Servos.setPosition(servoIndex1, x);
  ESP32_ISR_Servos.setPosition(servoIndex2, y);
  ESP32_ISR_Servos.setPosition(servoIndex3, z);
}