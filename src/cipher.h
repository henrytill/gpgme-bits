#ifndef GPGME_BITS_CIPHER_H
#define GPGME_BITS_CIPHER_H

#include <stdio.h>

int cipher_encrypt(const char *fingerprint, const char *input, const size_t input_len, FILE *file_out, const char *home);

int cipher_decrypt(const char *fingerprint, FILE *file_in, FILE *file_out, const char *home);

#endif /* GPGME_BITS_CIPHER_H */
