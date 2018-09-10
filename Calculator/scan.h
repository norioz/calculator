#pragma once
#include "Token.h"
#include "TokenCache.h"

// Scan is a utility for processing sequential character input
// into numeric calculation Tokens.

// Scans the text represented by cstring `in` adding sequential
// `Tokens` in its store until `maxTokens` is reached.
//
// @param in -- cstring representing typed calculation input
// @return the number of Tokens scanned
// @thows uninitialized -- if `Scanner.init` hasn't been called
int scan (const char * in, TokenCache & tc);
