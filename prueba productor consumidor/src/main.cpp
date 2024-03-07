#include <Arduino.h>
#include "esp_freertos_hooks.h"
TaskHandle_t productor;
TaskHandle_t consumidor;

bool iddleArduino(void);

void productorcode(void *pvParameters);
void consumidorcode(void *pvParameters);

uint32_t Senal;

QueueHandle_t colaInt;
QueueHandle_t timeSend;
QueueHandle_t timeRecive;

void setup()
{
  Serial.begin(921600);
  colaInt = xQueueCreate(10, sizeof(uint32_t));
  timeSend = xQueueCreate(10, sizeof(int));
  timeRecive = xQueueCreate(10, sizeof(int));
  esp_register_freertos_idle_hook(iddleArduino);
  xTaskCreatePinnedToCore(
      consumidorcode, /* Task function. */
      "consumidor",   /* name of task. */
      10000,          /* Stack size of task */
      NULL,           /* parameter of the task */
      1,              /* priority of the task */
      &consumidor,    /* Task handle to keep track of created task */
      1);             /* pin task to core 1 */
      
  xTaskCreatePinnedToCore(
      productorcode, /* Task function. */
      "productor",   /* name of task. */
      10000,         /* Stack size of task */
      NULL,          /* parameter of the task */
      1,             /* priority of the task */
      &productor,    /* Task handle to keep track of created task */
      0);            /* pin task to core 0 */
  // vTaskDelay(500 / 1);
}

void loop()
{
  int env, rec;
  if (xQueueReceive(colaInt, &(env), (TickType_t)8) != pdTRUE)
  {
    Serial.println("No se ha podido recibir el tiempo envio a la cola");
  }
  if (xQueueReceive(colaInt, &(rec), (TickType_t)8) != pdTRUE)
  {
    Serial.println("No se ha podido recibir el tiempo recibir a la cola");
  }
  Serial.print("El tiempo de envio es:");
  Serial.print(env);
  Serial.print("\t");
  Serial.print("El tiempo de recibir es:");
  Serial.println(rec);
}

bool iddleArduino(void)
{
  //Serial.println("Estamos en iddle");
  return true;
}

void productorcode(void *pvParameters)
{
  if (colaInt != 0)
  {
    for (;;)
    {
      int prevTime = millis();
      for (int deg = 0; deg < 360; deg = deg + 1)
      {
        int f_dac_out = 127 + 127 * sin(2 * PI * deg / 360); // Function generates Sine Wave.
        // xQueueGenericSend(colaInt, (void *)&Señal, (TickType_t)10, queueSEND_TO_BACK); // envio del dato a la cola
        Senal = f_dac_out;
        if (xQueueGenericSend(colaInt, (void *)&Senal, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
        {
          Serial.println("No se ha podido enviar el dato a la cola");
        }
        vTaskDelay(1);
      }
      int time = millis() - prevTime;

      if (xQueueGenericSend(colaInt, (void *)&time, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
      {
        Serial.println("No se ha podido enviar el tiempo envio a la cola");
      }
    }
  }
}

void consumidorcode(void *pvParameters)
{
  int count = 0;
  for (;;)
  {
    int prevTime = micros();
    uint32_t signalR;
    if (xQueueReceive(colaInt, &(signalR), (TickType_t)8) == pdTRUE)
    {
      //Serial.print(">Señal recibida: ");
      //Serial.println(signalR);
      if (count < 20)
      {
        count++;
        signalR;
      }
      else
      {
        //Serial.print(">Señal Comprimida: ");
        //Serial.println(signalR);
        count = 0;
      }
    }
    else
    {
      Serial.println("No se ha podido recibir el dato a la cola");
    }
    int time = micros() - prevTime;
    // Serial.println(time);
    if (xQueueGenericSend(colaInt, (void *)&time, (TickType_t)10, queueSEND_TO_BACK) != pdPASS)
    {
      Serial.println("No se ha podido enviar el tiempo recibir a la cola");
    }
  }
}