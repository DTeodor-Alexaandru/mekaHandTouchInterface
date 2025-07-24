#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "config/config.h"
#include "sensor_array/sensor_array.h"
#include "data_acquisition/daq.h"
#include "filter/lpf.h"
#include "comms/comms.h"

#define N_SENSORS  (NUM_ADC_CH * NUM_MUX_CH)

static float             g_filtered[N_SENSORS];
static SemaphoreHandle_t mutex_filtered;

static void sampling_task(void* _)
{
    // load configuration
    const app_config_t* cfg = config_get();

    // init data aquisition
    daq_init(cfg->sample_rate_hz);

    // init filter
    lpf2_t lpf;
    lpf2_init(&lpf, cfg->sample_rate_hz, cfg->cutoff_freq_hz);

    static daq_frame_t frame;
    static float        filtered[DAQ_TOTAL_SENSORS];

    const TickType_t delay = pdMS_TO_TICKS(1000.0f / cfg->sample_rate_hz);
    
    while (1) {
        daq_read(&frame);
        lpf2_apply(&lpf, frame.raw, filtered);

        if (xSemaphoreTake(mutex_filtered, portMAX_DELAY) == pdTRUE) {
            for (int i = 0; i < N_SENSORS; i++) {
                g_filtered[i] = filtered[i];
            }
            xSemaphoreGive(mutex_filtered);
        }

        vTaskDelay(delay);
    }
}

static void publish_task(void* _){
    const app_config_t* cfg = config_get();

    const TickType_t delay = pdMS_TO_TICKS(1000.0f / cfg->sample_rate_hz);

    while (1) {
        
        if (xSemaphoreTake(mutex_filtered, portMAX_DELAY) == pdTRUE) {
            comms_send(g_filtered);
            xSemaphoreGive(mutex_filtered);
        }

        vTaskDelay(delay);
    }

}


void app_main(void)
{
    // create the mutex
    mutex_filtered = xSemaphoreCreateMutex();
    configASSERT(mutex_filtered);

    // launch tasks
    UBaseType_t prio = tskIDLE_PRIORITY + 2;
    xTaskCreatePinnedToCore(sampling_task,
                            "sampling",
                            8*1024, NULL, prio, NULL, 0);
    xTaskCreatePinnedToCore(publish_task,
                            "publish",
                            8*1024, NULL, prio, NULL, 1);
}
