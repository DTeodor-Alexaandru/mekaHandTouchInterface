#pragma once

typedef struct {
    float sample_rate_hz;    
    float cutoff_freq_hz;    
} app_config_t;

const app_config_t* config_get(void);
