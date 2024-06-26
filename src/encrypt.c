#include <stdio.h>
#include <string.h>

#include "cipher.h"
#include "data.h"

int main(void) {
  const size_t input_len = strlen(INPUT);

  return cipher_encrypt(FINGERPRINT, INPUT, input_len, stdout, NULL);
}
