/*timer_controller.c*/
#include "lib/timer_controller.h"

#define TIMER_DIVIDER 16000
#define TIMER_MAG_MS 1000
#define TIMER_SCALE_SEC    (TIMER_BASE_CLK / TIMER_DIVIDER)  /*!< used to calculate counter value */
#define TIMER_SCALE_MS    (TIMER_BASE_CLK / TIMER_DIVIDER / TIMER_MAG_MS)  /*!< used to calculate counter value */
#define TIMER_FINE_ADJ   (1.4 * (TIMER_BASE_CLK / TIMER_DIVIDER)/1000000) /*!< used to compensate alarm value */
#define DEBOUNCE_TIME 3 //ms

uint8_t DEBOUNCE_TICK;

void init_timer_controller(void)
{
  int timer_group = TIMER_GROUP_0;
  int timer_idx = TIMER_0;
  timer_config_t config;

  DEBOUNCE_TICK = 0;

  config.alarm_en = TIMER_ALARM_EN;
  config.auto_reload = TIMER_AUTORELOAD_EN;
  config.counter_dir = TIMER_COUNT_UP;
  config.divider = TIMER_DIVIDER;
  config.intr_type = TIMER_INTR_LEVEL;
  config.counter_en = TIMER_PAUSE;
  /*Configure timer*/
  timer_init(timer_group, timer_idx, &config);
  /*Stop timer counter*/
  timer_pause(timer_group, timer_idx);
  /*Load counter value */
  timer_set_counter_value(timer_group, timer_idx, 0x00000000ULL);
  /*Set alarm value*/
  timer_set_alarm_value(timer_group, timer_idx, (DEBOUNCE_TIME * TIMER_SCALE_MS - TIMER_FINE_ADJ));
  /*Enable timer interrupt*/
  timer_enable_intr(timer_group, timer_idx);
  /*Set ISR handler*/
  timer_isr_register(timer_group, timer_idx, timer_group0_isr, (void*) timer_idx, ESP_INTR_FLAG_IRAM, NULL);
  /*Start timer counter*/
  timer_start(timer_group, timer_idx);
}

void IRAM_ATTR timer_group0_isr(void *para)
{
    int timer_idx = (int) para;
    uint32_t intr_status = TIMERG0.int_st_timers.val;
    if((intr_status & BIT(timer_idx)) && timer_idx == TIMER_0) {

        TIMERG0.hw_timer[timer_idx].update = 1;

        TIMERG0.int_clr_timers.t0 = 1;

        DEBOUNCE_TICK = 1;

        TIMERG0.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN;
    }
}
