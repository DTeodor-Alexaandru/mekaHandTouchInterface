#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "config.h"
#include "daq.h"
#include "lpf.h"
#include "descriptors.h"

static const char *TAG = "main";

#define N_SENSORS      (NUM_ADC_CH * NUM_MUX_CH)
#define REPORT_ID      0x00
#define IN_REPORT_SIZE (N_SENSORS * sizeof(uint16_t))

static float             g_filtered[N_SENSORS];
static SemaphoreHandle_t mutex_filtered;

static void sampling_task(void* _)
{
    app_config_t prev = *config_get();

    daq_init(prev.sample_rate_hz);

    lpf2_t lpf;
    lpf2_init(&lpf, prev.sample_rate_hz, prev.cutoff_freq_hz);

    daq_frame_t frame;
    float filtered[N_SENSORS];

    while (1) {
        app_config_t cur = *config_get();

        // if either sample rate or cutoff changed, re‑init DAQ & LPF:
        if ( cur.sample_rate_hz != prev.sample_rate_hz ||
             cur.cutoff_freq_hz != prev.cutoff_freq_hz )
        {
            daq_init(cur.sample_rate_hz);
            lpf2_init(&lpf, cur.sample_rate_hz, cur.cutoff_freq_hz);
            prev = cur;
        }

        daq_read(&frame);
        lpf2_apply(&lpf, frame.raw, filtered);

        if (xSemaphoreTake(mutex_filtered, portMAX_DELAY)) {
            memcpy(g_filtered, filtered, sizeof(g_filtered));
            xSemaphoreGive(mutex_filtered);
        }

        TickType_t delay = pdMS_TO_TICKS(1000.0f / cur.sample_rate_hz);
        vTaskDelay(delay);
    }
}

static void publish_task(void* _)
{
    TickType_t delay = pdMS_TO_TICKS(1000.0f / config_get()->sample_rate_hz);
    uint8_t report[IN_REPORT_SIZE];

    while (1) {
        if (tud_hid_ready() && xSemaphoreTake(mutex_filtered, portMAX_DELAY)) {
            for (int i = 0; i < N_SENSORS; i++) {
                uint16_t v = (uint16_t)g_filtered[i];
                report[2*i]   = v & 0xFF;
                report[2*i+1] = v >> 8;
            }
            tud_hid_report(REPORT_ID, report, sizeof(report));
            xSemaphoreGive(mutex_filtered);
        }
        vTaskDelay(delay);
    }
}

void app_main(void)
{
    mutex_filtered = xSemaphoreCreateMutex();
    configASSERT(mutex_filtered);

    ESP_LOGI(TAG, "USB init");
    tinyusb_config_t tusb_cfg = {
        .device_descriptor      = NULL,
        .configuration_descriptor = get_hid_configuration_descriptor(),
        .string_descriptor      = get_hid_string_descriptor(),
        .string_descriptor_count = 3,
        .external_phy           = false,
    };
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
    ESP_LOGI(TAG, "USB ready");

    BaseType_t prio = tskIDLE_PRIORITY + 2;
    xTaskCreate(sampling_task, "sampling", 8*1024, NULL, prio, NULL);
    xTaskCreate(publish_task,  "publish",  8*1024, NULL, prio, NULL);
}
