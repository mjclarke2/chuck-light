/*ps2_controller.c*/
#include "lib/ps2_controller.h"

#define TAG "PS2 Controller"

//TODO map color wheel
//TODO set movement flags
//TODO set gesture flags

int read_x_y()
{
  int x,y;
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_11db);
  adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_11db);

  while (1) {
    x = adc1_get_raw(ADC1_CHANNEL_6)-1773;
    y = adc1_get_raw(ADC1_CHANNEL_7)-1934;
    ESP_LOGI(TAG, "%d,%d", x, y);
    vTaskDelay(10);
    /* code */
  }
}
