idf_component_register(
    SRCS
        "main.c"
        "config/config.c"
        "sensor_array/sensor_array.c"
        "data_acquisition/daq.c"
        "filter/lpf.c"
        "comms/comms.c"
    INCLUDE_DIRS
        "."                      # for main.c
        "config"                 # so #include "config/config.h" works
        "sensor_array"
        "data_acquisition"
        "filter"
        "comms"
    REQUIRES driver esp_adc esp_wifi
)
