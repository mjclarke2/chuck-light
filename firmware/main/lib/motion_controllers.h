/*motion_controllers.h*/
#ifndef MOTION_CONTROLLERS_H
#define MOTION_CONTROLLERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "soc/gpio_struct.h"
#include "driver/gpio.h"

#define MISO_PIN 25
#define MOSI_PIN 23
#define CLK_PIN  19
#define CS_PIN   22 //could just tie high
#define DRDY_PIN 21

void init_motion_controllers(void);
void read_motion(uint8_t *ret_val);
void lcd_spi_pre_transfer_callback(spi_transaction_t *t);

#endif
