#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/at42qt2120.h"

uint8_t KEYPAD_LOOKUP[] = {
  5,
  10,
  11,
  9,
  0,
  3,
  8,
  1,
  4,
  7,
  2,
  6
};

int
main(int argc, char * argv[]) {

  int i = 0;
  int pressed = 0;
  uint8_t keys_lo = 0x00;
  uint8_t keys_hi = 0x00;
  uint16_t keys;
  uint16_t mask;

  // Open the Touch Controller
  at42qt2120_open();
  sleep(1);

  for( i = 0; i < 12; i++)
  {
    printf("Press key %x\n",i);
    pressed = 0;

    while( pressed == 0)
    {
      keys_hi = 0x0F & at42qt2120_read(AT42QT2120_KEY_STATUS_HI_REG);
      keys_lo = at42qt2120_read(AT42QT2120_KEY_STATUS_LO_REG);

      keys = (uint16_t)(keys_hi << 8) | keys_lo;
      
      mask = 1 << KEYPAD_LOOKUP[i];
      
      if ( (keys & mask) != 0)
      {
          printf("Key %X was pressed\n",i);
          pressed = 1;
      }
    }
  }

  // Close the Touch Controler
  at42qt2120_close();

  return 0;
}
