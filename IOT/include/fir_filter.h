/**
  * @file funciones.h
  * @version 0.1
  * @date 2024-04-04
  * @author David Martín-Sacristán Avilés (https://github.com/DavidM-SA/INSTRUMENTACION-AVANZADA)
  * @title Filtro Digital->MQTT
  * @brief sampling frequency: 1000 Hz \n
    * 0 Hz - 20 Hz -> gain = 1 \n
    * 50 Hz - 500 Hz -> gain = 0 \n
  * @code
  * main(){
     SampleFilter_init(&filtroFIR);
     SampleFilter_put(&filtroFIR, signalR);
     double filtro = SampleFilter_get(&filtroFIR);
   }
  * @endcode
  */
#ifndef SAMPLEFILTER_H_
#define SAMPLEFILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 1000 Hz

* 0 Hz - 20 Hz
  gain = 1
  desired ripple = 0.1 dB
  actual ripple = 0.060686422707968264 dB

* 50 Hz - 500 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = -41.69131531643894 dB

*/

#define SAMPLEFILTER_TAP_NUM 73

/**
 * @brief Estructura creada para ejecutar el filtro
 * 
 */
typedef struct
{
  double history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
} SampleFilter;
/**
 * @brief SampleFilter_init inicializa el Filtro figital.
 *
 * @param f Puntero a la variable tipo SampleFilter para inicializar el filtro .
 */
void SampleFilter_init(SampleFilter *f);
/**
 * @brief SampleFilter_put pasamos a la funcion la variable a filtrar.
 *
 * @param f Puntero a la variable tipo SampleFilter para inicializar el filtro.
 * @param input Variable a filtrar.
 */
void SampleFilter_put(SampleFilter *f, double input);
/**
 * @brief SampleFilter_put Devuelve la variable filtrada.
 *
 * @param f Puntero a la variable tipo SampleFilter para inicializar el filtro.
 * @return double Devuelve el valor filtrado.
 */
double SampleFilter_get(SampleFilter *f);

#endif