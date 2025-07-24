#pragma once

#include <stdint.h>

#define NUM_ADC_CH    6    // A0..A5
#define NUM_MUX_CH   16    // 0..15 each

void sensor_array_list(uint8_t out_indices[NUM_ADC_CH*NUM_MUX_CH]);
