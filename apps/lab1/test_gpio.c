#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/ece453.h"

#define GPIO_BUTTON0_MASK (1 << (GPIO_IN_BUTTONS_BIT_NUM + 0))
#define GPIO_BUTTON1_MASK (1 << (GPIO_IN_BUTTONS_BIT_NUM + 1))
#define GPIO_BUTTON2_MASK (1 << (GPIO_IN_BUTTONS_BIT_NUM + 2))
#define GPIO_BUTTON3_MASK (1 << (GPIO_IN_BUTTONS_BIT_NUM + 3))

#define LED0_MASK 1

int main(int argc, char * argv[]) {
    int button_vals = 0;
    int curr_led = 0;
    int status = 0;
    bool changed = false;

    // Read the device ID register
    status = ece453_reg_read(DEVICE_ID_REG);
    if (status == -1) {
        printf("Error Reading DEV_ID\n\r");
        return -1;
    }

    printf("DEV_ID: 0x%08X\n\r", status);

    // Turn on LED 0
    status = ece453_reg_write(GPIO_OUT_REG, LED0_MASK);
    if (status == -1) {
        printf("Error Writing GPIO OUT\n\r");
        return -1;
    }

    printf("Press KEY[0] to move right or KEY[1] to move left.\n\r");
    printf("Press KEY[2] to exit.\n\r");

    // check button values every second
    while(true) {
        // wait one second (don't care if interrupted, so don't check status)
        sleep(1);
        button_vals = ece453_reg_read(GPIO_IN_REG);
        if (button_vals == -1) {
            printf("Error Reading GPIO IN\n\r");
            status = -1;
            break;
        }
        if ((button_vals & GPIO_BUTTON2_MASK) == 0) {
            // button 2 pressed, exit
            status = 0;
            break;
        }
        if ((button_vals & GPIO_BUTTON1_MASK) == 0) {
            // move to next highest led (or rotate to zero)
            curr_led = (curr_led == 9) ? 0 : curr_led + 1;
            changed = true;
        } else if ((button_vals & GPIO_BUTTON0_MASK) == 0) {
            // move to next lowest led (or rotate to nine)
            curr_led = (curr_led == 0) ? 9 : curr_led - 1;
            changed = true;
        }
        
        if (changed) {
            changed = false;
            status = ece453_reg_write(GPIO_OUT_REG, LED0_MASK << curr_led);
            if (status == -1) {
                printf("Error Writing GPIO OUT\n\r");
                break;
            }
        }
    }
    
    // exit program (by error or by button 2 press)
    if (ece453_reg_write(GPIO_OUT_REG, 0) == -1) {
        printf("Error Writing GPIO OUT\n\r");
        status = -1;
    }
    return status;
}
