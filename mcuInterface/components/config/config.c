#include "config.h"

static app_config_t cfg = {
    .sample_rate_hz = 100.0f,
    .cutoff_freq_hz =   5.0f,
};

const app_config_t* config_get(void) {
    return &cfg;
}

void config_set(const app_config_t* new_cfg) {
    // simply copy over the two floats
    cfg = *new_cfg;
}
