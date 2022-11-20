/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "./logger.h"
#include "./touch.h"

void app_main(void)
{
    lprintf(LOG_INFO, "Starting up\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    lprintf(LOG_INFO, "This is %s chip with %d CPU core(s), WiFi%s%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
            (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    lprintf(LOG_INFO, "silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    lprintf(LOG_INFO, "%uMB %s flash\n", flash_size / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    lprintf(LOG_INFO, "Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    // Start wifi thread and, controller thread
    lprintf(LOG_INFO, "Setting hardware up...\n");

    touch_pads_t output;
    memset(&output, 0, sizeof(output));

    init_pads(&output);

    for (;; usleep(20)) print_pads(&output);
}
