/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef SRC_LIB_BACKEND_FAPI_H_
#define SRC_LIB_BACKEND_FAPI_H_

#include "pkcs11.h"
#include "twist.h"
#include "token.h"

CK_RV backend_fapi_init(void);
CK_RV backend_fapi_destroy(void);

CK_RV backend_fapi_ctx_new(token *t);
void backend_fapi_ctx_free(token *t);

CK_RV backend_fapi_create_token_seal(token *t, const twist hexwrappingkey,
                       const twist newauth, const twist newsalthex);

CK_RV backend_fapi_add_tokens(token *tok, size_t *len);

CK_RV backend_fapi_init_user(token *t, const twist sealdata,
                        const twist newauthhex, const twist newsalthex);

CK_RV backend_fapi_add_object(token *t, tobject *tobj);

#endif /* SRC_LIB_BACKEND_FAPI_H_ */
