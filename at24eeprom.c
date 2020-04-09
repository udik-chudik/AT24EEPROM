#include "at24eeprom.h"
#ifdef USE_HAL_DRIVER

uint8_t at24read(I2C_HandleTypeDef * eeprom, uint8_t * buf, uint16_t len, uint16_t offset)
{
    return HAL_I2C_Mem_Read(eeprom, 0xa0 | ((offset >> 8) << 1), offset&0xff, I2C_MEMADD_SIZE_8BIT, buf, len , 1000);
}
uint8_t at24write(I2C_HandleTypeDef * eeprom, uint8_t * buf, uint16_t len, uint16_t offset)
{
    uint16_t current_offset = offset;
    uint16_t remain = len;
    do {
        uint16_t length = 0;
        if ( (current_offset & 0b00001111) + remain <= 0x10 )
        {
            length = remain;
        } else {
            length = 0x10 - (current_offset & 0b00001111);
        }
        HAL_I2C_Mem_Write(eeprom, 0xa0 | ((current_offset >> 8) << 1), current_offset&0xff, I2C_MEMADD_SIZE_8BIT, &buf[len-remain], length , 1000);
        HAL_Delay(5);
        current_offset += length;
        remain -= length;
    } while (remain);
    return HAL_OK;
}
#endif