@mainpage Práctica 1 Instrumentación Avanzada.
@subpage doc

@tableofcontents

Práctica 1 de Instrumentación Avanzada, en la que se demuestran competencias como el desarrollo de tareas y colas, resolviendo problemas típicos como la concurrencia, tambien se demuestran competencias calibrando conversores en este caso en Analógico-Digital, y la adquisicion de datos para su posterior filtrado ayudandonos de la siguiente página (http://t-filter.engineerjs.com/). \n \n
En esta práctica analizaremos mediante un ESP-32, una señal sinusoidal producia por un generador de señales, que mediante el conversor Analógico-Digital la digitalizaremos, para mas tarde filtrarla con el programa producido por http://t-filter.engineerjs.com/ para la ejecucion del filtro, que lo habremos calibrado para los siguientes valores:\n \n

| Frecuencia de muestreo | 1000 Hz ||
| :----: | :----: | :----: |
| Frequency | 0 Hz - 20 Hz |50 Hz - 500 Hz|
| Gain  | 1    | 0    |
| Ripple deseado | 0.1 dB | -40 dB |
| Ripple actual | 0.060686422707968264 dB | -41.69131531643894 dB. |
Una vez filtrada la señal la analizaremos sacadando cada segundo el máximo, el mínimo, y la media de todos los valores obtenidos, para ser enviados a un broker (mqtt-dashboard.com), mediante un cliente en mi casi ha sido este https://www.hivemq.com/demos/websocket-client/ o desde el mismo ESP-32 dandonos de alta en el topic, podriamos obtener los datos filtrados desde cualquier lugar. Creando así nuestro primer dispositivo IoT.