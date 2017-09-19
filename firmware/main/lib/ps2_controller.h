/*led_controller.h*/
#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/adc.h"
#include "esp_log.h"

int read_x_y(void);

#endif
