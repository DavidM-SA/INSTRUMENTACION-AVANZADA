/**
 * @file fir_filter.cpp
 * @author David Martín-Sacristán Avilés (https://github.com/DavidM-SA/INSTRUMENTACION-AVANZADA)
 * @brief Valores calculados con http://t-filter.engineerjs.com/
 * @version 0.1
 * @date 2024-04-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "fir_filter.h"
/**
 * @brief Valores del filtro para que funcione a nuestras especificaciones calculados con http://t-filter.engineerjs.com/
 * 
 */
static double filter_taps[SAMPLEFILTER_TAP_NUM] = {
  0.0051507710019452835,
  0.0022311024026411435,
  0.0025167970755835215,
  0.0026659760771963964,
  0.002637072379443213,
  0.002390657256751146,
  0.001902619610688507,
  0.0011539203938814766,
  0.00014917056818735704,
  -0.0010918469689543153,
  -0.002528887223962684,
  -0.004099334447717108,
  -0.005719829138895196,
  -0.0072922903687947654,
  -0.008702538167082092,
  -0.009825638163982166,
  -0.010533079500107777,
  -0.010700129731590024,
  -0.010212195481655601,
  -0.008972301507848375,
  -0.006908206606065885,
  -0.003978756799881306,
  -0.00017752028054812837,
  0.004465176427337767,
  0.009878004757308613,
  0.015949138829356474,
  0.022528995358868674,
  0.029437189416651032,
  0.03646981347830108,
  0.043408617569560215,
  0.05002019278859201,
  0.056074803246222084,
  0.0613626131782984,
  0.06569933524235021,
  0.06890829428260341,
  0.0708886648345609,
  0.07155504314816491,
  0.0708886648345609,
  0.06890829428260341,
  0.06569933524235021,
  0.0613626131782984,
  0.056074803246222084,
  0.05002019278859201,
  0.043408617569560215,
  0.03646981347830108,
  0.029437189416651032,
  0.022528995358868674,
  0.015949138829356474,
  0.009878004757308613,
  0.004465176427337767,
  -0.00017752028054812837,
  -0.003978756799881306,
  -0.006908206606065885,
  -0.008972301507848375,
  -0.010212195481655601,
  -0.010700129731590024,
  -0.010533079500107777,
  -0.009825638163982166,
  -0.008702538167082092,
  -0.0072922903687947654,
  -0.005719829138895196,
  -0.004099334447717108,
  -0.002528887223962684,
  -0.0010918469689543153,
  0.00014917056818735704,
  0.0011539203938814766,
  0.001902619610688507,
  0.002390657256751146,
  0.002637072379443213,
  0.0026659760771963964,
  0.0025167970755835215,
  0.0022311024026411435,
  0.0051507710019452835
};
/**
 * @brief SampleFilter_init inicializa el Filtro figital.
 * 
 * @param f Puntero a la variable tipo SampleFilter para inicializar el filtro .
 */
void SampleFilter_init(SampleFilter* f) {
  int i;
  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}
/**
 * @brief SampleFilter_put pasamos a la funcion la variable a filtrar.
 * 
 * @param f Puntero a la variable tipo SampleFilter para inicializar el filtro.
 * @param input Variable a filtrar.
 */
void SampleFilter_put(SampleFilter* f, double input) {
  f->history[f->last_index++] = input;
  if(f->last_index == SAMPLEFILTER_TAP_NUM)
    f->last_index = 0;
}
/**
 * @brief SampleFilter_put Devuelve la variable filtrada.
 * 
 * @param f Puntero a la variable tipo SampleFilter para inicializar el filtro.
 * @return double Devuelve el valor filtrado.
 */
double SampleFilter_get(SampleFilter* f) {
  double acc = 0;
  int index = f->last_index, i;
  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += f->history[index] * filter_taps[i];
  };
  return acc;
}