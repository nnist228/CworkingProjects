#include "inttypes.h"
#include "readBits.h"

 uint32_t read32Bits(const uint8_t** p)
{
    *p += 4;    // переходим на 4 байта вперед 
    return *(const uint32_t*) (*p - 4); //Возвращаем значение для предыдущих 4 байт
}

 uint16_t read16Bits(const uint8_t**p)
{
   *p += 2;     // переходим на 2 байта вперед 
   return *(const uint16_t*) (*p - 2);  // возвращаем значение для предыдущих 2 байт
}