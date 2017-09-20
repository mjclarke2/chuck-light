/*button_controllers.h*/
#ifndef BUTTON_CONTROLLERS_H
#define BUTTON_CONTROLLERS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG "Button Controllers"

#define PS2_B 2
#define B1 4
#define B2 8

#define DEBOUNCE_COUNT 9

void init_button_controllers(void);

//read_button - if detected debounce
uint8_t read_button(void);

#endif
