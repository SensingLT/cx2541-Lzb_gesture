#include "crc.h"

// CRC-16
uint16_t crc16(const uint8_t* buf, uint32_t len) {
    uint16_t crc = 0xFFFF;
    for (uint32_t pos = 0; pos < len; pos++) {
        crc ^= buf[pos];
        for (int i = 8; i != 0; i--) {
            if (crc & 1) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}
