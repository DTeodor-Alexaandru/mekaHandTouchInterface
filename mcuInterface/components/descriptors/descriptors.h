#pragma once

#include <stdint.h>
#include <string.h>
#include "config.h"
#include "tinyusb.h"
#include "class/hid/hid_device.h"
#include "tusb.h"

// standard TinyUSB callbacks
const uint8_t* tud_descriptor_device_cb(void);
uint8_t const* tud_hid_descriptor_report_cb(uint8_t instance);
const uint8_t* get_hid_report_descriptor(void);
const uint8_t* get_hid_configuration_descriptor(void);
const char**   get_hid_string_descriptor(void);
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid);

// HID control‐transfer callbacks (must match hid_device.h!)
uint16_t tud_hid_get_report_cb(uint8_t instance,
                               uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t* buffer,
                               uint16_t reqlen);

void tud_hid_set_report_cb(uint8_t instance,
                           uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const* buffer,
                           uint16_t bufsize);
