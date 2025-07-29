#pragma once

typedef struct {
    float sample_rate_hz;
    float cutoff_freq_hz;
} app_config_t;

// get pointer to the live config
const app_config_t* config_get(void);

// overwrite the live config
void config_set(const app_config_t* new_cfg);
