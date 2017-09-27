/*led_controller.c*/
#include "lib/led_controller.h"

#define TAG "LED Controller"

void init_led_controller()
{
    gpio_config_t io_conf;

    //LED gpio setup
    if(!GPIO_IS_VALID_GPIO(RED_PIN) ||
        !GPIO_IS_VALID_GPIO(GREEN_PIN) ||
        !GPIO_IS_VALID_GPIO(BLUE_PIN))
        ESP_LOGI(TAG, "Invalid GPIO");

    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

}

void set_red(uint8_t level)
{
  gpio_set_level(RED_PIN, level);
}

void set_green(uint8_t level)
{
  gpio_set_level(GREEN_PIN, level);
}

void set_blue(uint8_t level)
{
  gpio_set_level(BLUE_PIN, level);
}
