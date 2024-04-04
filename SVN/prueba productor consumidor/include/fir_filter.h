#ifndef SAMPLEFILTER_H_
#define SAMPLEFILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 1000 Hz

* 0 Hz - 40 Hz
  gain = 1
  desired ripple = 0.1 dB
  actual ripple = 0.0716428239879214 dB

* 50 Hz - 500 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = -40.24970605560597 dB

*/

#define SAMPLEFILTER_TAP_NUM 223

typedef struct {
  double history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
} SampleFilter;

void SampleFilter_init(SampleFilter* f);
void SampleFilter_put(SampleFilter* f, double input);
double SampleFilter_get(SampleFilter* f);

#endif