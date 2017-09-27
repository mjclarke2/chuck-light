/*motion_controllers.c*/
#include "lib/motion_controllers.h"

spi_device_handle_t spi;

void init_motion_controllers()
{
  esp_err_t ret;
  spi_bus_config_t buscfg = {
      .miso_io_num = MISO_PIN,
      .mosi_io_num = MOSI_PIN,
      .sclk_io_num = CLK_PIN,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1
  };
  spi_device_interface_config_t devcfg={
      .clock_speed_hz = 10*1000*1000,           //Clock out at 10 MHz
      .mode = 0,                                //SPI mode 0
      .spics_io_num = CS_PIN,               //CS pin
      .queue_size = 7,                          //We want to be able to queue 7 transactions at a time
      .pre_cb = lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
  };
  //Initialize the SPI bus
  ret=spi_bus_initialize(HSPI_HOST, &buscfg, 1);
  assert(ret==ESP_OK);
  //Attach the LCD to the SPI bus
  ret=spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
  assert(ret==ESP_OK);

}

void read_motion(uint8_t *ret_val)
{
  esp_err_t ret;
  spi_transaction_t t;
  uint8_t cmd[4];

  cmd[0] = 0xFF;
  cmd[1] = 0;
  cmd[2] = 0;
  cmd[3] = 0;

  memset(&t, 0, sizeof(t));       //Zero out the transaction
  t.length=8;                     //Command is 8 bits
  t.tx_buffer=&cmd;               //The data is the cmd itself
  t.user=(void*)0;                //D/C needs to be set to 0
  ret=spi_device_transmit(spi, &t);  //Transmit!
  assert(ret==ESP_OK);            //Should have had no issues.
  if(t.rx_buffer != NULL)
  {
    ret_val[0] = ((uint8_t*) t.rx_buffer)[0];
    /*ret_val[1] = t.rx_buffer[1];
    ret_val[2] = t.rx_buffer[2];
    ret_val[3] = t.rx_buffer[3];*/
  }
  else
  {
    ret_val[0] = 69;
    /*ret_val[1] = 0;
    ret_val[2] = 0;
    ret_val[3] = 0;*/
  }

}

void lcd_spi_pre_transfer_callback(spi_transaction_t *t)
{
    int dc=(int)t->user;
    //gpio_set_level(PIN_NUM_DC, dc);
}
