#ifndef __CRC_H__
#define __CRC_H__

#include <PT32Y003x.h>
#include <stdint.h>

uint16_t crc16(const uint8_t *data, size_t length);

#endif //__CRC_H__
