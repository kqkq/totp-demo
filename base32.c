#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "base32.h"

static uint8_t LUT[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	                    'Y', 'Z', '2', '3', '4', '5', '6', '7'};

uint8_t *base32_encoding(uint8_t *message, unsigned int msg_len)
{
	int GROUPS = ceil(msg_len / 5.0);
	uint8_t *ret = malloc(GROUPS * 8 + 1);
	uint8_t *p_ret = ret;
	uint8_t *p = message;
	while (p != message + msg_len)
	{
		int i;
		uint64_t quantum = 0;
		int padding = 0;
		for (i = 0; i < 5; i++)
		{
			quantum <<= 8;
			if (p != message + msg_len) quantum |= *p++;
			else padding++;
		}
		for (int j = 0, remain = 40 - 8 * padding; j < 8; j++, remain -= 5, p_ret++)
		{
			if (remain > 0) *p_ret = LUT[quantum >> ((7 - j) * 5) & 0x1f];
			else *p_ret = '=';
		}
	}
	ret[GROUPS * 8] = 0;
	return ret;
}
