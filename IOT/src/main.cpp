#include <Arduino.h>

// mqtt
#include "EspMQTTClient.h"
void Imprimir(const String &payload);
EspMQTTClient client(
    "Mallware",
    "TuPutaMadre1993",
    "mqtt-dashboard.com", // MQTT Broker server ip
    "MQTTUsername",       // Can be omitted if not needed
    "MQTTPassword",       // Can be omitted if not needed
    "alumno",
    1883 // Client name that uniquely identify your device
);
unsigned long prev = 0;
unsigned long prev2 = 0;

void setup()
{
  Serial.begin(921600);
}

void onConnectionEstablished()
{

  client.subscribe("PruebasEupla", [] (const String &payload)  {
  Serial.println(payload);
  } );
  client.subscribe("Instrumentacionavanzada", Imprimir);
}

void loop()
{
  client.loop();
  if (millis() - prev >= 2000)
  {
    prev = millis();
    if (client.isMqttConnected())
    {
      client.publish("PruebasEupla", "Conexion temp");
    }
  }
  if (millis() - prev2 >= 2000)
  {
    prev2 = millis();
    if (client.isMqttConnected())
    {
      client.publish("Instrumentacionavanzada", "Intruso");
    }
  }
}
void Imprimir(const String &payload)
{
  Serial.println(payload);
}