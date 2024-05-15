@page MQTT Lenguaje MQTT. IoT.

@section IntroMQTT Introducción.
MQTT son las siglas de *Message Queuing Telemetry Transport*. Se trata de un protocolo de mensajería ligero para usar en casos de clientes que necesitan una huella de código pequeña, que están conectados a redes no fiables o con recursos limitados en cuanto al ancho de banda. Se utiliza principalmente para comunicaciones de máquina a máquina (M2M) o conexiones del tipo de IoT. \n

MQTT fue estandarizado como código abierto por medio de la organización para el avance de estándares de información estructurada (OASIS) en 2013.*OASIS* aún gestiona el estándar MQTT.\n

@section CaracMQTT Caracteristicas del lenguaje MQTT.

* *Ligero y eficiente*\n
La implementación de MQTT en el dispositivo IoT requiere recursos mínimos, por lo que se puede usar incluso en pequeños microcontroladores. Por ejemplo, un mensaje de control MQTT mínimo puede tener tan solo dos bytes de datos. Los encabezados de los mensajes MQTT también son pequeños para poder optimizar el ancho de banda de la red.

* *Escalable* \n
La implementación de MQTT requiere una cantidad mínima de código que consume muy poca energía en las operaciones. El protocolo también tiene funciones integradas para admitir la comunicación con una gran cantidad de dispositivos IoT. Por tanto, puede implementar el protocolo MQTT para conectarse con millones de estos dispositivos.

* *Fiable* \n
Muchos dispositivos IoT se conectan a través de redes celulares poco fiables con bajo ancho de banda y alta latencia. MQTT tiene funciones integradas que reducen el tiempo que tarda el dispositivo IoT en volver a conectarse con la nube. También define tres niveles diferentes de calidad de servicio a fin de garantizar la fiabilidad para los casos de uso de IoT.

* *Seguro* \n
MQTT facilita a los desarrolladores el cifrado de mensajes y la autenticación de dispositivos y usuarios mediante protocolos de autenticación modernos, como OAuth, TLS1.3, certificados administrados por el cliente, etc. Pero esto aumenta el ancho de banda requerido.

* *Admitido* \n
Varios lenguajes, como Python, o C, tienen un amplio soporte para la implementación del protocolo MQTT. Por lo tanto, los desarrolladores pueden implementarlo rápidamente con una codificación mínima en cualquier tipo de aplicación.

Para mantener el protocolo al mínimo, sólo se pueden efectuar cuatro acciones en cualquier comunicación: publicar, suscribirse, cancelar suscripción o hacer ping.\n \n

* *Publicar*: envía un bloque de datos que contiene el mensaje que se va a enviar. Estos datos son específicos de cada implementación, pero pueden ser algo tan simple como una indicación de encendido/apagado o un valor de un determinado sensor, como temperatura, presión, etc. En el caso de que el topic que se está publicando no exista, este se crea en el bróker. \n
* *Suscribirse*: convierte a un cliente en suscriptor de un topic. Se puede suscribir a topics en concreto o mediante comodines, que permiten suscripciones a toda una rama de topics o a parte de ella. Para suscribirse, un cliente envía un paquete SUBSCRIBE y recibe un paquete SUBACK a cambio. Si hay un mensaje retenido para el topic, el nuevo suscriptor también lo recibe.\n
* *PING:* un cliente puede hacer ping al bróker. El suscriptor envía un paquete PINGREQ y, como respuesta, se recibe un paquete PINGRESP. Se pueden utilizar pings para garantizar que la conexión siga funcionando y que la sesión TCP no haya sido cerrada inesperadamente por otro equipo de red, como un router o una puerta de enlace. \n
* *DESCONECTAR:* un suscriptor o editor puede enviar un mensaje de DISCONNECT al bróker. Este mensaje informa al bróker de que ya no necesitará enviar o poner en cola mensajes para un suscriptor y que ya no recibirá datos de un editor. Este tipo de cierre permite al cliente volver a conectarse utilizando la misma identidad de cliente que en ocasiones anteriores. Cuando un cliente se desconecta sin enviar un mensaje de desconexión, se envía su última voluntad y testamento a los suscriptores.\n

El objetivo original del protocolo MQTT era hacer posible la transmisión de datos de una forma más pequeña y eficiente a través de líneas de comunicación costosas y poco fiables. Como tal, la seguridad no fue una de las principales preocupaciones durante el diseño e implementación de MQTT.

Sin embargo, hay algunas opciones de seguridad disponibles a costa de una carga superior en la transmisión de datos.

@section cli Cliente.
Un cliente MQTT es cualquier dispositivo, desde un servidor hasta un microcontrolador, que ejecuta una biblioteca MQTT. Si el cliente envía mensajes, actúa como editor, y si recibe mensajes, actúa como receptor. Básicamente, cualquier dispositivo que se comunique mediante MQTT a través de una red puede denominarse dispositivo cliente MQTT.


@section Broker Broker.
El Broker MQTT es el sistema de back-end que coordina los mensajes entre los diferentes clientes. Las responsabilidades del broker incluyen recibir y filtrar mensajes, identificar a los clientes suscritos a cada mensaje y enviarles los mensajes. También se encarga de otras tareas como:

* La autorización y autenticación de clientes MQTT.
* Pasar mensajes a otros sistemas para su posterior análisis.
* El control de mensajes perdidos y sesiones de clientes.

Este protocolo se puede implementar con distintas tecnologías sobre los brokers y los clientes. Algunas de estas tecnologías son Mosquitto, RabbitMQ o EMQ.



* [Documentacion](@ref doc)
* [ESP-32](@ref ESP)
* [Filtros](@ref filter)