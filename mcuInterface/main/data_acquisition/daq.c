#include "daq.h"
#include "sensor_array.h"
#include "filter/lpf.h"
#include "config/config.h"
#include "driver/adc.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const gpio_num_t mux_pins[4] = {
    GPIO_NUM_9, GPIO_NUM_10, GPIO_NUM_11, GPIO_NUM_12
};
static const bool is_adc2[NUM_ADC_CH] = {1,1,1,1,1,0};
static const adc2_channel_t adc2_ch[5] = {
    ADC2_CHANNEL_7, ADC2_CHANNEL_6,
    ADC2_CHANNEL_5, ADC2_CHANNEL_4,
    ADC2_CHANNEL_3
};
static const adc1_channel_t adc1_ch = ADC1_CHANNEL_7;

// switch MUX
static void mux_select(int idx){
    for(int b=0;b<4;b++){
        gpio_set_level(mux_pins[b], (idx>>b)&1);
    }
}

void daq_init(float sample_rate_hz){
    // configure MUX GPIOs
    for(int i=0;i<4;i++){
        gpio_reset_pin(mux_pins[i]);
        gpio_set_direction(mux_pins[i], GPIO_MODE_OUTPUT);
    }
}

void daq_read(daq_frame_t* frame){
    const int SAMPLES = 64;
    for(int adc=0; adc<NUM_ADC_CH; adc++){
        for(int mux=0; mux<NUM_MUX_CH; mux++){
            mux_select(mux);
            vTaskDelay(pdMS_TO_TICKS(1)); // settle
            uint32_t sum=0;
            for(int s=0; s<SAMPLES; s++){
                if(is_adc2[adc]){
                    int r;
                    adc2_get_raw(adc2_ch[adc], ADC_WIDTH_BIT_12, &r);
                    sum += r;
                } else {
                    sum += adc1_get_raw(adc1_ch);
                }
            }
            frame->raw[adc*NUM_MUX_CH + mux] = sum/SAMPLES;
        }
    }
}
