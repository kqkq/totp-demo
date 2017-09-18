#ifndef _HOTP_H_
#define _HOTP_H_

#include <stdint.h>
#define HMAC_BLOCK_SIZE 64
uint32_t HOTP(uint8_t *key, unsigned int key_len, uint64_t counter, unsigned int digits);

#endif