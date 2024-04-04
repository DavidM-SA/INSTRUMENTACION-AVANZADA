/**
 * @file main.cpp
 * @author David Martín-Sacristán Avilés (https://github.com/DavidM-SA/INSTRUMENTACION-AVANZADA)
 * @brief main con tareas y colas creadas
 * @version 0.1
 * @date 2024-04-04
 * @see fir_filter.h fir_filter.cpp
 * @note Esto es una prueba de la Práctica 1 de **Instrumentación Avanzada**.
 * @attention El programa esta pensado para correr en un ESP-32.
 * @warning Para conectarse a la red debe rellenar bien los datos de MQTT-Client o no podra conectarse a internet y darse de alta en el topic.
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
void filterCode(void *pvParameters);
void Signal_Values_Code(void *pvParameters);

// variables:
SampleFilter filterFIR;
uint32_t signal;
uint64_t repet = 0, averaje, max, min;

// handle de las colas
QueueHandle_t colaSignal;
QueueHandle_t colaFiltro;

// Conversor analogico digital
esp_adc_cal_characteristics_t adc_chars;
esp_adc_cal_value_t val_type;

// handle tareas
TaskHandle_t analog;
TaskHandle_t filter;
TaskHandle_t data_obtain;

// mqtt
void Imprimir(const String &payload);
/**
 * @brief Datos de la red y del Broker para la conexion MQTT
 *
 */
EspMQTTClient client(
    "Mallware",           // Network name
    "TuPutaMadre1993",    // Network password
    "mqtt-dashboard.com", // MQTT Broker server ip
    "MQTTUsername",       // Can be omitted if not needed
    "MQTTPassword",       // Can be omitted if not needed
    "alumno",
    1883 // Client name that uniquely identify your device
);


/// @brief otra forma de poner un brief. Esto es el Setup
///
/// esto es un *comentario* mas detallado del **Setup**
/// ### Example
//! void setup() // Setup declaration \n
//!{ \n
//! Serial.begin(921600); //monitor_speed = 921600 \n
//! }
void setup()
{
  Serial.begin(921600);

  // inicializar adc
  /**
   * @brief Inicializamos el Conversor Analógico-Digital.
   * 
   */
  val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 3300, &adc_chars);

  // inicializamos filtro
  /**
   * @brief Creamos un nuevo objeto SampleFilter_init .
   * 
   */
  SampleFilter_init(&filterFIR);

  // crear colas
  /**
   * @brief Creamos la cola de la señal.
   * 
   */
  colaSignal = xQueueCreate(10, sizeof(uint32_t));
  /**
   * @brief Creamos la cola de la señal filtrada.
   * 
   */
  colaFiltro = xQueueCreate(10, sizeof(uint32_t));

  // crear tareas
  /**
   * @brief creamos la tarea para obtener la señal del Conversor Analógico-Digital
   * 
   */
  xTaskCreatePinnedToCore(
      signalCode, /* Task function. */
      "signal",   /* name of task. */
      10000,      /* Stack size of task */
      NULL,       /* parameter of the task */
      3,          /* priority of the task */
      &analog,    /* Task handle to keep track of created task */
      1);         /* pin task to core 1 */
  /**
   * @brief creamos la tarea para filtrar la señal del Conversor Analógico-Digital
   * 
   */
  xTaskCreatePinnedToCore(
      filterCode, /* Task function. */
      "filter",   /* name of task. */
      10000,      /* Stack size of task */
      NULL,       /* parameter of the task */
      2,          /* priority of the task */
      &filter,    /* Task handle to keep track of created task */
      0);         /* pin task to core 0 */
  /**
   * @brief creamos la tarea para calcular los valores maximos minimos y media de la señal filtrada
   * 
   */
  xTaskCreatePinnedToCore(
      Signal_Values_Code, /* Task function. */
      "Average",          /* name of task. */
      10000,              /* Stack size of task */
      NULL,               /* parameter of the task */
      2,                  /* priority of the task */
      &data_obtain,       /* Task handle to keep track of created task */
      1);                 /* pin task to core 1 */
}
/**
 * @brief funcion para darnos de alta en los topics cuando la conexion este establecida.
 *
 */
void onConnectionEstablished()
{
  // Dos formas de darse de alta en un topic.
  client.subscribe("Eupla806131", [](const String &payload)
                   { Serial.println(payload); });
  client.subscribe("Eupla806131/filtros", Imprimir);
}

/**
 * @brief Ejecutamos client.loop() a fondo perdido para no perder la conexion con el Broker 
 * 
 */
void loop()
{
  client.loop();
}

/**
 * @brief Tarea para leer el dato con el conversor analogico digital
 *
 * @param pvParameters parametros internos de la tarea
 */
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

/**
 * @brief Tarea para filtrar el dato obtenida con el conversor analogico digital
 *
 * @param pvParameters parametros internos de la tarea
 */
void filterCode(void *pvParameters)
{
  for (;;)
  {
    int signalR;
    if (xQueueReceive(colaSignal, &(signalR), (TickType_t)8) != pdTRUE)
    {
      Serial.println("No se ha podido recibir el dato de la cola");
    }

    SampleFilter_put(&filterFIR, signalR);
    double filtro = SampleFilter_get(&filterFIR);

    if (xQueueGenericSend(colaFiltro, (void *)&filtro, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
    {
      Serial.println("No se ha podido enviar el dato filtrado a la cola");
    }
  }
}

/**
 * @brief Tarea para sacar el valor medio de la señal
 *
 * @param pvParameters parametros internos de la tarea
 */
void Signal_Values_Code(void *pvParameters)
{
  for (;;)
  {
    int value;
    if (xQueueReceive(colaFiltro, &(value), (TickType_t)8) != pdTRUE)
    {
      Serial.println("No se ha podido recibir para media");
    }
    else
    {
      /// Sacamos la media
      averaje = averaje + value;
      /// sacamos el maximo
      if (value > max)
      {
        max = value;
      }
      /// sacamos el minimo
      if (value < min)
      {
        min = value;
      }
      repet++;
      if (repet > 1000)
      {
        if (client.isMqttConnected())
        {
          client.publish("Eupla806131/filtros/media", String(averaje / 1000));
          client.publish("Eupla806131/filtros/max", String(max));
          client.publish("Eupla806131/filtros/min", String(min));
        }
        repet = 0;
        averaje = 0;
        max = 0;
        min = 0;
      }
    }
  }
}

/**
 * @brief otra forma de imprimir la orden para darse de alta
 *
 * @param payload valor de la libreria para darse de alta en un topic
 */
void Imprimir(const String &payload)
{
  Serial.println(payload);
}