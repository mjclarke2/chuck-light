/*led_controller.h*/
#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define HIGH 1
#define LOW 0

#define RED_PIN   14
#define GREEN_PIN 12
#define BLUE_PIN  13
#define GPIO_OUTPUT_PIN_SEL (GPIO_SEL_14 | GPIO_SEL_12 | GPIO_SEL_13)

void init_led_controller(void);

void set_red(uint8_t level);
void set_green(uint8_t level);
void set_blue(uint8_t level);

#endif
