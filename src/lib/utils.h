/* SPDX-License-Identifier: BSD-2-Clause */

#ifndef SRC_PKCS11_UTILS_H_
#define SRC_PKCS11_UTILS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "pkcs11.h"
#include "twist.h"

#define SALT_HEX_STR_SIZE 64
#define AUTH_HEX_STR_SIZE 32

#define xstr(s) str(s)
#define str(s) #s

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))
#define ARRAY_BYTES(l, t) (l * sizeof(t[0]))

#define UNUSED(x) (void)x

#define SAFE_CAST(m, r) \
    do { \
        if (!m->pParameter || m->ulParameterLen != sizeof(typeof(*r))) { \
            return CKR_MECHANISM_PARAM_INVALID; \
        } \
        \
        r = (typeof(r))m->pParameter; \
    } while (0)

#define goto_error_false(r) if(!r) { goto error; }

int str_to_ul(const char *val, size_t *res);

static inline void str_padded_copy(CK_UTF8CHAR_PTR dst, const CK_UTF8CHAR_PTR src, size_t dst_len) {
    memset(dst, ' ', dst_len);
    memcpy(dst, src, strnlen((char *)(src), dst_len));
}

twist utils_hash_pass(const twist pin, const twist salt);

twist aes256_gcm_decrypt(const twist key, const twist objauth);

twist aes256_gcm_encrypt(twist keybin, twist plaintextbin);

/**
 * Retrieves the size in bytes of a hash algorithm
 * @param mttype
 *  The mechanism type.
 * @return
 *  The size in bytes or 0 if unknown.
 */
size_t utils_get_halg_size(CK_MECHANISM_TYPE mttype);

/**
 *
 * @param size
 * @return
 */
twist utils_get_rand_hex_str(size_t size);

CK_RV utils_setup_new_object_auth(twist newpin, twist *newauthhex, twist *newsalthex);

static inline CK_RV utils_new_random_object_auth(twist *newauthhex) {
    return utils_setup_new_object_auth(NULL, newauthhex, NULL);
}

typedef struct tpm_ctx tpm_ctx;
typedef struct token token;
CK_RV utils_ctx_unwrap_objauth(token *tok, twist objauth, twist *unwrapped_auth);
CK_RV utils_ctx_wrap_objauth(token *tok, twist objauth, twist *wrapped_auth);

/**
 * Given an attribute of CKA_EC_PARAMS returns the nid value.
 * @param ecparams
 *  The DER X9.62 parameters value
 * @param nid
 *  The nid to set
 * @return
 *  CKR_OK on success.
 */
CK_RV ec_params_to_nid(CK_ATTRIBUTE_PTR ecparams, int *nid);

#endif /* SRC_PKCS11_UTILS_H_ */
