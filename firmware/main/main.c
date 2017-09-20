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

#define TAG "Main"

extern uint8_t PS2_PRESSED;
extern uint8_t TOP_PRESSED;
extern uint8_t BOTTOM_PRESSED;

void app_main()
{
    char buf[32];
    int i;
    ESP_ERROR_CHECK( nvs_flash_init() );

    /* ------------- Init Functions --------------*/
    initialise_wifi();
    init_ps2_controller();
    init_button_controllers();

    //TODO UDP Listhener listens to modes

    //xTaskCreatePinnedToCore(&read_x_y, "PS2", 2048, NULL, tskIDLE_PRIORITY, NULL, 0); //pinned to core 0


    ESP_LOGI(TAG, "-... . . .--.")
    /* ------------- Main Loop -------------------*/
    while(1)
    {


      //TODO add a serial terminal
      //printConnectionInfo();
      switch(read_button())
      {
        case 0:
          //do nothing - no button was pressed
          //ESP_LOGI(TAG, "NOTHING");
        break;
        case B1:
          ESP_LOGI(TAG, "B1 Pressed");
        break;
        case B2:
          ESP_LOGI(TAG, "B2 Pressed");
        break;
        case B1 + B2:
          ESP_LOGI(TAG, "B1 + B2 Pressed");
        break;
        case PS2_B:
          ESP_LOGI(TAG, "PS2 Pressed");
        break;
      }
      if(i++ > 300)
      {
        ESP_LOGI(TAG, "HI");
        i = 0;
      }
      //vTaskDelay(1);
    }
}
