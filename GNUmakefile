.SUFFIXES:
.SUFFIXES: .c .o

CFLAGS  = -std=c11 -Wall -Wextra -Wconversion -Wsign-conversion -g
LDFLAGS =

VPATH = src:test

BIN =\
	decrypt \
	encrypt \
	roundtrip

OBJ =\
	cipher.o

LIB =\
	libcipher.so \
	_cipher_cffi.so

.PHONY: all
all: $(LIB) $(BIN)

cipher.o: CFLAGS += -fPIC -DPRINT_KEY
cipher.o: cipher.c cipher.h

libcipher.so: LDFLAGS += -Wl,-soname,libcipher.so
libcipher.so: cipher.o -lgpgme

encrypt: encrypt.c -lcipher

decrypt: decrypt.c -lcipher

roundtrip: CFLAGS += -Isrc
roundtrip: roundtrip.c -lcipher

lib%.so: %.o
	$(CC) -fPIC -shared $(LDFLAGS) -o $@ $^

_cipher_cffi.so: libcipher.so
	python3 test/cipher_build.py $@

.PHONY: check test
check test: roundtrip _cipher_cffi.so
	env -i LD_LIBRARY_PATH=$(CURDIR) ./roundtrip
	env -i LD_LIBRARY_PATH=$(CURDIR) PYTHONPATH=$(CURDIR) python3 test/roundtrip.py

.PHONY: clean
clean:
	rm -f $(BIN) $(OBJ) $(LIB)