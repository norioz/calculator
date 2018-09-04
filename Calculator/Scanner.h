#pragma once
#include "Token.h"

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

class Scanner {
public:

    // Initialize the Scanner such that it has space for at most
    // `maxTokens` Tokens. 
    // 
    // @param maxTokens -- the maximum number of tokens that the
    //        scanner can store.
    void init (int maxTokens);

    // Scans the text represented by cstring `in` creating sequential
    // `Tokens` in its store until `maxTokens` is reached.
    //
    // @param in -- cstring representing typed calculation input
    // @return the number of Tokens scanned
    // @thows uninitialized -- if `Scanner.init` hasn't been called
    int scan (const char * in);

    // Returns a pointer to a `Token` that represents the start of
    // a scan result.
    Token * getTokens ();

};
