#include "../include/at42qt2120.h"

// File handle for I2C /dev entry
static int i2c_fh;

//*****************************************************************************
// Use the GPIO_OUT_REG pins connected to the AT23QT2120 reset line to hold the 
// AT23QT2120 in reset by setting the pin low 
//*****************************************************************************
static void at42qt2120_assert_reset(void)
{  
  // read the current value of the GPIO_OUT_REG
  int reg_val = ece453_reg_read(GPIO_OUT_REG);
  if (reg_val == -1)
    pabort("at42qt2120.c::at42qt2120_assert_reset: Unable to read GPIO_OUT_REG");
    
  // Clear RST to be 0
  reg_val &= ~GPIO_OUT_CAP_SEN_RST_MASK;
  
  // Write the value back out
  if (ece453_reg_write(GPIO_OUT_REG, reg_val) == -1)
    pabort("at42qt2120.c::at42qt2120_assert_reset: Unable to write GPIO_OUT_REG");
}

//*****************************************************************************
// Use the GPIO port connected to the AT23QT2120 reset line to bring the 
// AT23QT2120 out of reset by setting the pin high
//*****************************************************************************
static void at42qt2120_deassert_reset(void)
{
  // read the current value of the GPIO_OUT_REG
  int reg_val = ece453_reg_read(GPIO_OUT_REG);
  if (reg_val == -1)
    pabort("at42qt2120.c::at42qt2120_deassert_reset: Unable to read GPIO_OUT_REG");

  // Clear RST to be 1
  reg_val |= GPIO_OUT_CAP_SEN_RST_MASK;

  // Write the value back out
  if (ece453_reg_write(GPIO_OUT_REG, reg_val) == -1)
    pabort("at42qt2120.c::at42qt2120_deassert_reset: Unable to write GPIO_OUT_REG");
}

//*****************************************************************************
//*****************************************************************************
static void at42qt2120_set_slave_address(void)
{
  if (ioctl(i2c_fh, I2C_SLAVE, AT42QT2120_SLAVE_ADDR) < 0) {
    perror("Error setting slave address");
    exit(1);
  }
}


//*****************************************************************************
//*****************************************************************************
void at42qt2120_open(void)
{
  i2c_fh = open(I2C_DEV, O_RDWR);
  if (i2c_fh < 0) {
    perror("i2c_open failed");
    exit(1);
  }

  // bring the at42qt2120 out of reset
  at42qt2120_deassert_reset();

  // Set the slave address for the at42qt2120
  at42qt2120_set_slave_address();

}

//*****************************************************************************
//*****************************************************************************
void at42qt2120_close(void)
{
  close(i2c_fh);

  // hold the at42qt2120 in reset
  at42qt2120_assert_reset();
}

//*****************************************************************************
// Writes one byte of data to the I2C bus.
//
// Note:  The slave address is already set using the at42qt2120_open() function.
//*****************************************************************************
void at42qt2120_write(uint8_t reg, uint8_t value)
{
  int status = -1;
  uint8_t data[2];

  data[0] = reg;
  data[1] = value;
  
  status = write(i2c_fh, data, 2);
  if (status != 2)
    pabort("at42qt2120.c::at42qt2120_write: unable to write i2c");
}

//*****************************************************************************
// Reads one byte of data from the I2C bus.
//
// Note:  The slave address is already set using the at42qt2120_open() function.
//*****************************************************************************
uint8_t at42qt2120_read(uint8_t reg)
{
  int status = -1;
  uint8_t data;

  // write register address
  status = write(i2c_fh, &reg, 1);
  if (status != 1)
    pabort("at42qt2120.c::at42qt2120_read: unable to write i2c");

  // read from register
  status = read(i2c_fh, &data, 1);
  if (status != 1)
    pabort("at42qt2120.c::at42qt2120_read: unable to read i2c");

  return data;
}
