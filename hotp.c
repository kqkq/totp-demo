#include <stdint.h>
#include "sha1.h"
#include "hmac-sha1.h"
#include "hotp.h"
#include <math.h>

uint32_t dynamicTruncateSHA1(uint8_t *digest)
{
	uint32_t offset = digest[SHA1HashSize - 1] & 0x0f;
	uint32_t ret = (digest[offset    ] & 0x7f) << 24
				 | (digest[offset + 1] & 0xff) << 16
				 | (digest[offset + 2] & 0xff) << 8
				 | (digest[offset + 3] & 0xff);
	return ret;
}

uint32_t HOTP(uint8_t *key, unsigned int key_len, uint64_t counter, unsigned int digits)
{
	uint8_t digest[20];
	uint8_t message[8];
	for (int i = 0; i < 8; i++)
	{
		uint8_t lbyte = (counter >> (8 * i)) & 0xff;
		message[7 - i] = lbyte;
	}
	HMAC_SHA1(key, key_len, message, 8, digest);
	uint32_t dt = dynamicTruncateSHA1(digest);
	return dt % (int)pow(10.0, digits);
}
