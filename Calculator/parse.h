#pragma once
#include "TokenCache.h"

// Creats syntax trees from sequential lists of Tokens,
// intended for use in numeric calculations.
//
//Token * parse (const Token * tokens, int length);

Token * parse (TokenCache & tc, int chainId);

Token * parseNumber (Token * tc, int idx);

Token * parseExpression (Token * tc, int idx, int chainLength);