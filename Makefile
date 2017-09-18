IDIR = .
CC = gcc
CFLAGS = -I$(IDIR)
DEPS = base32.h hmac-sha1.h hotp.h qecodegen.h sha1.h
OBJ = base32.o hmac-sha1.o hotp.o qrcodegen.o sha1.o totp-auth.o
LIBS=-lm

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

totp-demo: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o totp-demo
