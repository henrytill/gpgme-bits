#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <gpgme.h>

#include "config.h"
#include "util.h"

int
main(int argc, char *argv[])
{
	gpgme_error_t         err;
	gpgme_ctx_t           ctx;
	gpgme_key_t           keys[KEYS_LEN];
	gpgme_data_t          in;
	gpgme_data_t          out;
	gpgme_encrypt_flags_t flags;

	(void)argc;
	executable_name = argv[0];

	/* Initialize */
	if ((err = init_gpgme(GPGME_PROTOCOL_OPENPGP)) != 0) {
		gpgme_failure(NULL, err, FAILURE_MSG_INIT);
	}

	/* Create new context */
	if ((err = gpgme_new(&ctx)) != 0) {
		gpgme_failure(ctx, err, FAILURE_MSG_NEW);
	}

	/* Fetch key and print its information */
	if ((err = gpgme_get_key(ctx, FINGERPRINT, &keys[KEY], true)) != 0) {
		gpgme_failure(ctx, err, FAILURE_MSG_GET_KEY);
	}
	keys[END] = NULL;

#ifdef NDEBUG
	print_key_info(keys[0]);
#endif

	/* Turn on ASCII-armored output */
	gpgme_set_armor(ctx, true);

	/* Create input */
	if ((err = gpgme_data_new_from_mem(&in, INPUT, INPUT_LEN, true)) != 0) {
		gpgme_data_release(in);
		gpgme_failure(ctx, err, FAILURE_MSG_NEW_INPUT);
	}

	/* Create empty cipher */
	if ((err = gpgme_data_new(&out)) != 0) {
		gpgme_data_release(in);
		gpgme_data_release(out);
		gpgme_failure(ctx, err, FAILURE_MSG_NEW_OUTPUT);
	}

	/* Encrypt */
	flags = GPGME_ENCRYPT_ALWAYS_TRUST;
	if ((err = gpgme_op_encrypt(ctx, keys, flags, in, out)) != 0) {
		gpgme_data_release(in);
		gpgme_data_release(out);
		gpgme_failure(ctx, err, FAILURE_MSG_ENCRYPT);
	}
	print_data(ctx, out);

	gpgme_data_release(in);
	gpgme_data_release(out);
	gpgme_release(ctx);

	return 0;
}
