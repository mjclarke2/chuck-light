#! /bin/bash

sudo chmod 777 /dev/ttyUSB0
cp main/drivers/* $IDF_PATH/components/driver/
make flash && make monitor
