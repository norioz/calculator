#pragma once
#include "Token.h"

// TokenCache is temporary store for sequences of Tokens (chains).
//
// A TokenCache must be initialized with the maximum capacity
// of Tokens that can be held.
//
// Once initialized, Token chains can be copied into the cache
// with the `add` method. If the cache is asked to add more
// tokens than its maxToken size, it throws a `size_limit`
// exception. After being added, a chain is assigned an
// integer chain id that the `add` method returns.
// 
// Storage of Token chains within a TokenCache are sequential
// and chains are never broken. Eg. The second chain stored will
// exist within the cache immediately after the first. However,
// when add is called with a chain that will not fit within the
// remaining cache space, chains at the beginning of the cache
// are overwritten.

class TokenCache {
    int m_size = -1;
    int * m_chainIds = nullptr;
    int * m_chainLengths = nullptr;
    Token * m_tokens = nullptr;

public:
    ~TokenCache ();

    // Initialize the cache to hold a fixed max number of Tokens.
    //
    // @param maxTokens - determines the size of the cache
    void init (int maxTokens);

    // Copies Tokens into the cache.
    //
    // @param tokens - a pointer to the beginning of the Tokens
    // @param num - the number of Tokens to copy
    //
    // @return the integer ID of the resulting Token chain
    int add (const Token * tokens, int num);

    // Get a pointer to a Token chain within the cache.
    //
    // @param id - the integer id assigned to the Token chain
    //
    // @return a pointer to the first Token in the requested
    //         chain, or nullptr if the chain is not available
    Token * getById (int id);

    // Find the length of a chain by its chain id.
    //
    // @param id - the integer id of the Token chain
    //
    // @return the number of Tokens in the chain, or -1 if
    //         the chain specified is not available
    int chainLength (int id);
};