/*main.c*/
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "lib/button_controllers.h"
#include "lib/connection_controller.h"
#include "lib/data_controller.h"
#include "lib/led_controller.h"
#include "lib/motion_controllers.h"
#include "lib/ps2_controller.h"
#include "lib/serial_controller.h"

void app_main()
{
    char buf[32];
    ESP_ERROR_CHECK( nvs_flash_init() );

    /* ------------- Init Functions --------------*/
    initialise_wifi();

    xTaskCreatePinnedToCore(&read_x_y, "PS2", 2048, NULL, tskIDLE_PRIORITY + 6, NULL, 0); //pinned to core 0

    /* ------------- Main Loop -------------------*/
    while(1)
    {
      //TODO add a serial terminal
      printConnectionInfo();
      vTaskDelay(3000);
    }
}
