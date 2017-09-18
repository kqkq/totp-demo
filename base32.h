#ifndef _BASE_32_H_
#define _BASE_32_H_

#include <stdint.h>

uint8_t *base32_encoding(uint8_t *message, unsigned int msg_len);

#endif