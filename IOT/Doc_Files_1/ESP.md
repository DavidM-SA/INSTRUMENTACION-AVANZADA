@page ESP ESP-32.


@section IntroESP Introducción.

En esta practica hemos usado el ESP32 DEV KIT que es un microcontrolador de la empresa **Expressif Systems**. Es un claro sucesor del ESP8266

@section EstrucESP Estructura ESP-32.

Este es el diagrama del ESP-32: \n
![](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\diagrama.jpeg)
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

![](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\BLOQUES-ESP32.jpeg)

@section ProgramESP Programar ESP-32.

Para poder programar el ESP-32, podemos usar dos entornos:
* **Arduino IDE**
Es un entorno de facil uso ya que si se viene de programar placas Arduino, podria ser un entorno amigable, pero es un entorno que podria tener limitaciones en diferentes sectores.
* **ESP-IDF (Espressif IoT Development Framework)**
Es el entorno de desarrollo de software desarrollado por *Espressif*, puede ayudar a los usuarios a desarrollar rápidamente aplicaciones de Internet de las cosas (IoT) para satisfacer las necesidades de los usuarios de Wi-Fi, Bluetooth y bajo consumo de energía. \n
Es el usado por muchos desarrolladores; y para poder programar usando esta aplicación se deben tener en cuenta ciertos requerimientos, los cuales se describen en el siguiente enlace: https://docs.espressif.com/projects/esp-idf/en/release-v4.1/get-started/index.html\n
Hay que destacar que el entorno de desarrollo de *Espressif* esta basado sobre *FreeRTOS*.
@subsection FreeRTOS FreeRTOS.
FreeRTOS es un sistema operativo en tiempo real (RTOS) para microcontroladores y microprocesadores. Y está distribuido bajo la licencia MIT.\n
La programación sin un sistema operativo, conocida como programación “bare-metal”, puede ser más exigente para el programador. Una de las principales ventajas de usar un sistema operativo es la multitarea, que permite que un hilo suspenda su ejecución para que otro hilo se ejecute sin que el hilo original pierda su contexto. Esto aumenta la confiabilidad del sistema.\n
El RTOS ofrece recursos que permiten garantizar una respuesta del sistema flexible. Semáforos, mutex, colas de mensajes y tareas con prioridad definida están entre estos recursos. Los sistemas se pueden dividir en dos categorías principales: Real-Time Soft y Hard, según los requisitos del sistema.\n
* Ventajas de FreeRTOS
 - Las prioridades de las tareas ayudan a cumplir con los tiempos de respuesta de la aplicación.
 - Mejora el mantenimiento y la escalabilidad del sistema.
 - Ayuda a la modularidad de las tareas.
 - Ayuda a la definición de interfaces de los distintos módulos.
 - Facilita la reutilización de código.
 - Permite realizar tareas (idle task) cuando el sistema está desocupado o ir a un estado de bajo consumo.
 - Es flexible con el manejo de interrupciones.
* Implementación de FreeRTOS.\n
FreeRTOS está diseñado para ser pequeño y simple. El núcleo consta de solo tres archivos implementados en C. Proporciona métodos para múltiples subprocesos o hilos, mutexes, semáforos y temporizadores de software. Además, admite prioridades de hilos y tiene un modo tickless para reducir el consumo energético. En FreeRTOS, las aplicaciones pueden asignarse de manera completamente estática.\n 

En resumen, FreeRTOS es una opción poderosa y flexible para el desarrollo de aplicaciones de tiempo real en microcontroladores y microprocesadores, proporcionando una amplia gama de características y ventajas para optimizar el rendimiento y la eficiencia del sistema.





* [Documentacion](@ref doc)
* [Filtros](@ref filter)
* [Lenguaje MQTT](@ref MQTT)