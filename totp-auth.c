#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "hotp.h"
#include "base32.h"
#include <time.h>
#include "qrcodegen.h"

// Prints the given QR Code to the console.
static void printQr(const uint8_t qrcode[]) {
	int size = qrcodegen_getSize(qrcode);
	int border = 2;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "\033[40m  \033[0m" : "\033[47m  \033[0m"), stdout);
		}
		fputs("\n", stdout);
	}
}

int main()
{
	time_t now;
	uint8_t *key = "12345678901234567890";

	uint8_t *base32 = base32_encoding(key, strlen(key));

	char text[200];
	sprintf(text, "otpauth://totp/KUANG%%20Qi?secret=%s&issuer=Cheeselabs.org", base32);
	free(base32);
	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, qrcodegen_Ecc_LOW,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);

	if (ok) printQr(qrcode);

	while (1) {
		getchar();
		time(&now);
		uint64_t counter = now / 30;
		uint32_t code = HOTP(key, strlen(key), counter, 6);
		printf("Code = %u", code);
	}

    return 0;
}

