#include <Arduino.h>
#include "esp_freertos_hooks.h"
#include "fir_filter.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

// Cabeceras funciones
void productorcode(void *pvParameters);
void consumidorcode(void *pvParameters);
//  void plottercode(void *pvParameters);

// variables:
SampleFilter filtroFIR;
uint32_t Senal;

// Conversor analogico digital
esp_adc_cal_characteristics_t adc_chars;
esp_adc_cal_value_t val_type;

// handle de las colas
QueueHandle_t queuePut;
// QueueHandle_t queueGet;

// handle tareas
TaskHandle_t productor;
TaskHandle_t consumidor;
//  TaskHandle_t plotter;

void setup()
{
  Serial.begin(921600);

  // inicializar adc
  val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 3300, &adc_chars);
  
  // inicializamos filtro
  SampleFilter_init(&filtroFIR);

  // crear colas
  queuePut = xQueueCreate(10, sizeof(uint32_t));
  // queueGet = xQueueCreate(10, sizeof(double));

  // crear tareas
  xTaskCreatePinnedToCore(
      consumidorcode, /* Task function. */
      "consumidor",   /* name of task. */
      10000,          /* Stack size of task */
      NULL,           /* parameter of the task */
      2,              /* priority of the task */
      &consumidor,    /* Task handle to keep track of created task */
      1);             /* pin task to core 1 */

  xTaskCreatePinnedToCore(
      productorcode, /* Task function. */
      "productor",   /* name of task. */
      10000,         /* Stack size of task */
      NULL,          /* parameter of the task */
      2,             /* priority of the task */
      &productor,    /* Task handle to keep track of created task */
      0);            /* pin task to core 0 */

  // xTaskCreatePinnedToCore(
  //     plottercode, /* Task function. */
  //     "plotter",   /* name of task. */
  //     10000,       /* Stack size of task */
  //     NULL,        /* parameter of the task */
  //     1,           /* priority of the task */
  //     &plotter,    /* Task handle to keep track of created task */
  //     1);
}

void loop()
{
}

void productorcode(void *pvParameters)
{
  for (;;)
  {
    // leemos datos conversor analogico
    uint32_t reading = adc1_get_raw(ADC1_CHANNEL_7);
    uint32_t voltaje = esp_adc_cal_raw_to_voltage(4095 - reading, &adc_chars);

    // mandamos dato a la cola
    if (xQueueGenericSend(queuePut, (void *)&voltaje, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
    {
      Serial.println("No se ha podido enviar el dato a la cola");
    }
    //********Test para la cola********
    // imprimimos dato: 
    //Serial.print(">sin:");
    //Serial.println(voltaje);
    /*
    SampleFilter_put(&filtroFIR, voltaje);
    double filtro = SampleFilter_get(&filtroFIR);

    Serial.print(">con:");
    Serial.println(filtro);
    */
    // retraso para que no valla a fondo perdido
    vTaskDelay(1);
  }
}

void consumidorcode(void *pvParameters)
{
  for (;;)
  {
    //int prevTime = micros();
    int signalR;
    if (xQueueReceive(queuePut, &(signalR), (TickType_t)8) != pdTRUE)
    {
      Serial.println("No se ha podido recibir el dato de la cola");
    }
    Serial.print(">sin:");
    Serial.println(signalR);

    SampleFilter_put(&filtroFIR, signalR);
    double filtro = SampleFilter_get(&filtroFIR);

    Serial.print(">con:");
    Serial.println(filtro);
    //Serial.print(">time cons:");
    //Serial.println(micros()-prevTime);
  }
}
/*void plottercode(void *pvParameters)
{
  for (;;)
  {
    // double SampleFilter_get(&filtroFIR);
  }
}*/