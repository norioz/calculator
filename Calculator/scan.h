#pragma once
#include "Token.h"
#include "TokenStore.h"

// Scanner is a utility for processing sequential character input
// into numeric calculation Tokens.
//
// A Scanner instance keeps an internal store of Tokens, whose size
// is dictated by calling its init method. The init method must 
// complete before the scan method may be used.
// 
// After being initialized, calls to `scan` produce Tokens in the
// Scanner's token store that can be accessed with the `getTokens`
// method.
//
// Subsequent calls to scan abut tokens in the token store 
// until the current scan requires more Token locations than are
// left in the store. At the point of overflow, the Scanner begins
// overwriting the beginning of the store.

// Scans the text represented by cstring `in` creating sequential
// `Tokens` in its store until `maxTokens` is reached.
//
// @param in -- cstring representing typed calculation input
// @return the number of Tokens scanned
// @thows uninitialized -- if `Scanner.init` hasn't been called
int scan (const char * in, TokenStore & store);
