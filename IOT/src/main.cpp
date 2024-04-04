/**
 * @file main.cpp
 * @author David Martín-Sacristán Avilés (https://github.com/DavidM-SA/INSTRUMENTACION-AVANZADA)
 * @brief main con tareas y colas creadas
 * @version 0.1
 * @date 2024-04-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino.h>
#include "esp_freertos_hooks.h"
#include "fir_filter.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "EspMQTTClient.h"

// Cabeceras funciones
void signalCode(void *pvParameters);
void filtroCode(void *pvParameters);
void mediaCode(void *pvParameters);
void maxCode(void *pvParameters);
void minCode(void *pvParameters);

// variables:
SampleFilter filtroFIR;
uint32_t Senal;
uint64_t repet = 0, medval;

// handle de las colas
QueueHandle_t colaSignal;
QueueHandle_t colaFiltro;
QueueHandle_t colaMedia;
QueueHandle_t colaMax;
QueueHandle_t colaMin;

// Conversor analogico digital
esp_adc_cal_characteristics_t adc_chars;
esp_adc_cal_value_t val_type;

// handle tareas
TaskHandle_t analog;
TaskHandle_t filtro;
TaskHandle_t maximum;
TaskHandle_t minimum;
TaskHandle_t media;

// mqtt
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

  // inicializar adc
  val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 3300, &adc_chars);

  // inicializamos filtro
  SampleFilter_init(&filtroFIR);

  // crear colas
  colaSignal = xQueueCreate(10, sizeof(uint32_t));
  colaFiltro = xQueueCreate(10, sizeof(uint32_t));
  colaMedia = xQueueCreate(10, sizeof(uint32_t));
  colaMax = xQueueCreate(10, sizeof(uint32_t));
  colaMin = xQueueCreate(10, sizeof(uint32_t));

  // crear tareas
  xTaskCreatePinnedToCore(
      signalCode, /* Task function. */
      "senal",    /* name of task. */
      10000,      /* Stack size of task */
      NULL,       /* parameter of the task */
      3,          /* priority of the task */
      &analog,    /* Task handle to keep track of created task */
      1);         /* pin task to core 1 */

  xTaskCreatePinnedToCore(
      filtroCode, /* Task function. */
      "filtro",   /* name of task. */
      10000,      /* Stack size of task */
      NULL,       /* parameter of the task */
      2,          /* priority of the task */
      &filtro,    /* Task handle to keep track of created task */
      0);         /* pin task to core 0 */

  xTaskCreatePinnedToCore(
      mediaCode, /* Task function. */
      "media",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      2,         /* priority of the task */
      &media,    /* Task handle to keep track of created task */
      1);        /* pin task to core 1 */

  xTaskCreatePinnedToCore(
      maxCode,  /* Task function. */
      "maximo", /* name of task. */
      10000,    /* Stack size of task */
      NULL,     /* parameter of the task */
      2,        /* priority of the task */
      &maximum, /* Task handle to keep track of created task */
      1);       /* pin task to core 1 */

  xTaskCreatePinnedToCore(
      minCode,  /* Task function. */
      "minimo", /* name of task. */
      10000,    /* Stack size of task */
      NULL,     /* parameter of the task */
      2,        /* priority of the task */
      &minimum, /* Task handle to keep track of created task */
      1);       /* pin task to core 1 */
}

void onConnectionEstablished()
{

  client.subscribe("FiltrosEupla", [](const String &payload)
                   { Serial.println(payload); });
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
void signalCode(void *pvParameters)
{
  for (;;)
  {
    // leemos datos conversor analogico
    uint32_t reading = adc1_get_raw(ADC1_CHANNEL_7);
    uint32_t voltaje = esp_adc_cal_raw_to_voltage(4095 - reading, &adc_chars);

    // mandamos dato a la cola
    if (xQueueGenericSend(colaSignal, (void *)&voltaje, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
    {
      Serial.println("No se ha podido enviar el dato sin filtrar a la cola");
    }
    vTaskDelay(1);
  }
}

void filtroCode(void *pvParameters)
{
  for (;;)
  {
    int signalR;
    if (xQueueReceive(colaSignal, &(signalR), (TickType_t)8) != pdTRUE)
    {
      Serial.println("No se ha podido recibir el dato de la cola");
    }

    SampleFilter_put(&filtroFIR, signalR);
    double filtro = SampleFilter_get(&filtroFIR);

    if (xQueueGenericSend(colaFiltro, (void *)&filtro, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
    {
      Serial.println("No se ha podido enviar el dato filtrado a la cola");
    }
  }
}

void mediaCode(void *pvParameters)
{
  for (;;)
  {
    int media;
    if (xQueueReceive(colaFiltro, &(media), (TickType_t)8) != pdTRUE)
    {
      Serial.println("No se ha podido recibir para media");
    }
    else
    {
      medval = medval + media;
      repet++;
      // mandamos dato a la cola
      if (xQueueGenericSend(colaMedia, (void *)&media, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
      {
        Serial.println("No se ha podido enviar la media a la cola");
      }
      if (repet > 1000)
      {
        if (client.isMqttConnected())
        {
          client.publish("Eupla/filtros/media", String(medval / 1000));
        }
        repet = 0;
        media = 0;
      }
    }
  }
}

void minCode(void *pvParameters)
{
  for (;;)
  {
    int cola, max;
    if (xQueueReceive(colaFiltro, &(cola), (TickType_t)8) != pdTRUE)
    {
      Serial.println("No se ha podido recibir para media");
    }
    if (max > cola)
    {
      max = cola;
    }
    // mandamos dato a la cola
    if (xQueueGenericSend(colaMin, (void *)&cola, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
    {
      Serial.println("No se ha podido enviar el dato sin filtrar a la cola");
    }
    if (client.isMqttConnected())
    {
      client.publish("Eupla/filtros/minimo", String(max));
    }
  }
}

void maxCode(void *pvParameters)
{
  for (;;)
  {
    // leemos datos conversor analogico
    uint32_t reading = adc1_get_raw(ADC1_CHANNEL_7);
    uint32_t voltaje = esp_adc_cal_raw_to_voltage(4095 - reading, &adc_chars);

    // mandamos dato a la cola
    if (xQueueGenericSend(colaSignal, (void *)&voltaje, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
    {
      Serial.println("No se ha podido enviar el dato sin filtrar a la cola");
    }
    vTaskDelay(1);
  }
}

void Imprimir(const String &payload)
{
  Serial.println(payload);
}