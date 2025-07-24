#include "sensor_array.h"

void sensor_array_list(uint8_t out_indices[NUM_ADC_CH*NUM_MUX_CH]) {
    for (int adc = 0; adc < NUM_ADC_CH; adc++) {
        for (int mux = 0; mux < NUM_MUX_CH; mux++) {
            out_indices[adc*NUM_MUX_CH + mux] = adc*NUM_MUX_CH + mux;
        }
    }
}
