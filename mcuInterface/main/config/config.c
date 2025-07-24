#include "config.h"

// hard‑coded example:
static const app_config_t cfg = {
    .sample_rate_hz = 100.0f,
    .cutoff_freq_hz =   5.0f,
};

const app_config_t* config_get(void) {
    return &cfg;
}
