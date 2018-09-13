#pragma once
#include <exception>
#include "Token.h"
#include "TokenCache.h"

// Scans the text represented by cstring `in` adding sequential
// `Tokens` to a chain in the provided TokenCache. Each Token
// produced is assigned a TokenType by matching regular
// expressions that embody the form of the types. If a piece of
// the input doesn't match any TokenType an 
// `UnrecognizedTokenTypeException` is thrown, scanning is halted,
// and no Tokens are added to the TokenCache.
//
// @param in -- cstring representing typed calculation input
// @param tc -- TokenCache where the resulting chain is stored
// @return the integer ID for the chain in the given TokenCache
// @thows UnrecognizedTokenTypeException if a portion of the input
//        cannot be assigned a valid TokenType.
int scan (const char * in, TokenCache & tc);

// UnrecognizedTokenException is thrown by `scan` when text in the
// input doesn't match any of the regexes that define the existing
// TokenTypes.
class UnrecognizedTokenTypeException : public std::exception {
    const char * m_text;
public:
    // Constructor takes in a the text that could not be tokenized.
    UnrecognizedTokenTypeException (const char * text);

    // Get the text that could not be tokenized.
    const char * getText ();

    virtual const char * what() const throw();
};
