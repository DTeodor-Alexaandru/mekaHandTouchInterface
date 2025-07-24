#pragma once

#include "sensor_array/sensor_array.h"  // for NUM_ADC_CH, NUM_MUX_CH
#include <stdint.h>

#define DAQ_TOTAL_SENSORS  (NUM_ADC_CH * NUM_MUX_CH)

typedef struct {
    float  alpha;                   // IIR coefficient
    float  z1[DAQ_TOTAL_SENSORS];   // state of 1st pole
    float  z2[DAQ_TOTAL_SENSORS];   // state of 2nd pole
} lpf2_t;

// initialize 2nd‑order LPF
void lpf2_init(lpf2_t* f, float fs, float fc);

// apply filter: raw[] -> out[] (both length DAQ_TOTAL_SENSORS)
void lpf2_apply(lpf2_t* f,
                const uint32_t raw[],
                float          out[]);
