#include "config.h"

// make this non‐const so we can modify it at runtime
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
