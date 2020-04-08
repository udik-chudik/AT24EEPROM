#include <stdint.h>
#ifndef __at24eeprom
#define __at24eeprom

#ifdef USE_HAL_DRIVER
    #include "i2c.h"
    uint8_t at24read(I2C_HandleTypeDef *, uint8_t * buf, uint16_t len, uint16_t offset);
    uint8_t at24write(I2C_HandleTypeDef *, uint8_t * buf, uint16_t len, uint16_t offset);
#endif

#endif