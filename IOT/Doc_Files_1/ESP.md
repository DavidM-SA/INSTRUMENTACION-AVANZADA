@page ESP ESP-32.
@tableofcontents

@section IntroESP Introducción.

En esta practica hemos usado el ESP32 DEV KIT que es un microcontrolador de la empresa **Expressif Systems**. Es un claro sucesor del ESP8266

@section EstrucESP Estructura ESP-32.

Este es el diagrama del ESP-32: \n
![](diagrama.jpeg)
\n \n
Esta placa electrónica contiene los siguientes pines:

* 19 canales de convertidor analógico a digital (ADC)
* 3 interfaces SPI
* 3 interfaces UART
* 2 interfaces I2C
* 16 canales de salida PWM
* 2 convertidores de digital a analógico (DAC)
* 2 interfaces I2S
* 10 GPIO de detección capacitiva

Se presenta también el diagrama de bloques de esta tarjeta electrónica.

![](BLOQUES-ESP32.jpeg)

@section ProgramESP Programar ESP-32.

Para poder programar el ESP-32, podemos usar dos entornos:
* **Arduino IDE**
Es un entorno de facil uso ya que si se viene de programar placas Arduino, podria ser un entorno amigable, pero es un entorno que podria tener limitaciones en diferentes sectores.
* **ESP-IDF (Espressif IoT Development Framework)**
Es el entorno de desarrollo de software desarrollado por Espressif, puede ayudar a los usuarios a desarrollar rápidamente aplicaciones de Internet de las cosas (IoT) para satisfacer las necesidades de los usuarios de Wi-Fi, Bluetooth y bajo consumo de energía. \n
Es el usado por muchos desarrolladores; y para poder programar usando esta aplicación se deben tener en cuenta ciertos requerimientos, los cuales se describen en el siguiente enlace: https://docs.espressif.com/projects/esp-idf/en/release-v4.1/get-started/index.html