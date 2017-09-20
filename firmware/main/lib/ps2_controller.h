/*led_controller.h*/
#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "driver/adc.h"
#include "esp_log.h"

void init_ps2_controller(void);

int read_x_y(void);

//read direction

//read rgb

#endif
