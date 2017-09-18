#ifndef _HMAC_SHA1_H_
#define _HMAC_SHA1_H_

#include <stdint.h>
#define HMAC_BLOCK_SIZE 64
void HMAC_SHA1(uint8_t *key, unsigned int key_len, uint8_t *message, unsigned int msg_len, uint8_t *digest);

#endif