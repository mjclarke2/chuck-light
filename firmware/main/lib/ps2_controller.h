/*ps2_controller.h*/
#ifndef PS2_CONTROLLER_H
#define PS2_CONTROLLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "driver/adc.h"
#include "esp_log.h"

#define X_PIN 34
#define Y_PIN 35
#define Z_PIN 32 //for refrence only - PS2 button controlled in button_controllers

void init_ps2_controller(void);

void read_xy(int *ret_val);
void read_rgb(uint8_t *ret_val);

#endif
