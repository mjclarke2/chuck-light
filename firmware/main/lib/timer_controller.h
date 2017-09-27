/*timer_controller.h*/
#ifndef TIMER_CONTROLLER_H
#define TIMER_CONTROLLER_H

#include <stdio.h>
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"

extern uint8_t DEBOUNCE_TICK;

void init_timer_controller(void);
void IRAM_ATTR timer_group0_isr(void *para);

#endif
