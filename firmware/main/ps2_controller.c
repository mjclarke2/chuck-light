/*ps2_controller.c*/
#include "lib/ps2_controller.h"

#define TAG "PS2 Controller"

//TODO map color wheel
//TODO set movement flags
//TODO set gesture flags

void init_ps2_controller()
{
  //configure ADC - X,Y joystick
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_11db);
  adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_11db);
}

void read_xy(int *ret_val)
{

  ret_val[0] = adc1_get_raw(ADC1_CHANNEL_6)-1773;
  ret_val[1] = adc1_get_raw(ADC1_CHANNEL_7)-1934;

}

void read_rgb(uint8_t *ret_val)
{
  ret_val[0] = 255;
  ret_val[1] = 0;
  ret_val[2] = 0;
}
