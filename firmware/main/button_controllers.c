/*button_controllers.c*/
#include "lib/button_controllers.h"

#define PS2_PIN    32
#define B1_PIN     26
#define B2_PIN     27
#define GPIO_INPUT_PIN_SEL (GPIO_SEL_32 | GPIO_SEL_26 | GPIO_SEL_27)

void init_button_controllers()
{
    gpio_config_t io_conf;

    //LED gpio setup
    if(!GPIO_IS_VALID_GPIO(PS2_PIN) ||
        !GPIO_IS_VALID_GPIO(B1_PIN) ||
        !GPIO_IS_VALID_GPIO(B2_PIN))
        ESP_LOGI(TAG, "Invalid GPIO");

    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

}

uint8_t read_button()
{
  uint8_t i;

  //B1 + B2 pressed
  if(!gpio_get_level(B1_PIN) && !gpio_get_level(B2_PIN))
  {
    for(i = 0; i < DEBOUNCE_COUNT; i++){;;}
    if(gpio_get_level(B1_PIN) && gpio_get_level(B2_PIN))
      return B1 + B2;
    else
      return 0;
  }

  //B1 pressed
  if(!gpio_get_level(B1_PIN))
  {
    for(i = 0; i < DEBOUNCE_COUNT; i++){;;}
    if(gpio_get_level(B1_PIN))
      return B1;
    else
      return 0;
  }

  //B2 pressed
  if(!gpio_get_level(B2_PIN))
  {
    for(i = 0; i < DEBOUNCE_COUNT; i++){;;}
    if(gpio_get_level(B2_PIN))
      return B2;
    else
      return 0;
  }

  //PS2 pressed
  if(!gpio_get_level(PS2_PIN))
  {
    for(i = 0; i < DEBOUNCE_COUNT; i++){;;}
    if(gpio_get_level(PS2_PIN))
      return PS2_B;
    else
      return 0;
  }

  return 0;
}
