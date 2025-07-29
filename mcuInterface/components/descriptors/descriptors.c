#include "descriptors.h"
#include <string.h>

#define CONFIG_TOTAL_LEN     (9 + 9 + 9 + 7)
#define HID_ITF_NUM          0
#define EPNUM_HID_IN         0x81
static const uint8_t hid_report_descriptor[] = {
    0x06, 0x00, 0xFF,  // Usage Page (Vendor)
    0x09, 0x01,
    0xA1, 0x01,
    // OUT (4 bytes)
    0x09, 0x02,
    0x15, 0x00,
    0x26, 0xFF, 0x00,
    0x75, 0x08,
    0x95, 0x04,
    0x91, 0x02,
    // IN (variable size, override at runtime)
    0x09, 0x03,
    0x15, 0x00,
    0x26, 0xFF, 0x00,
    0x75, 0x08,
    0x95, 0xC0,
    0x81, 0x02,
    0xC0,
};

uint8_t const* tud_hid_descriptor_report_cb(uint8_t instance) {
    (void) instance;
    return hid_report_descriptor;
}

const uint8_t* get_hid_report_descriptor(void) {
    return hid_report_descriptor;
}

static const uint8_t hid_configuration_descriptor[] = {
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, CONFIG_TOTAL_LEN, 0x80, 100),
    TUD_HID_DESCRIPTOR(HID_ITF_NUM, 0, false,
                       sizeof(hid_report_descriptor),
                       EPNUM_HID_IN,  64,  1)
};

const uint8_t* get_hid_configuration_descriptor(void) {
    return hid_configuration_descriptor;
}

// String descriptors
static const char* strings[] = {
    (const char[]){0x09, 0x04}, 
    "ENSTA",
    "mekaHandTouchInterface",
};

const char** get_hid_string_descriptor(void) {
    return strings;
}

uint16_t tud_hid_get_report_cb(uint8_t instance,
                               uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t* buffer,
                               uint16_t reqlen)
{
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    // return zero bytes (no report)
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance,
                           uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const* buffer,
                           uint16_t bufsize)
{
    (void)instance; (void)report_id; (void)report_type;
    (void)buffer;   (void)bufsize;
}
