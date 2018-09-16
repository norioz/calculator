#pragma once
#include "Token.h"

// TokenCache is temporary store for sequences of Tokens (chains).
//
// A TokenCache must be initialized with a capacity, specified
// by a maximum chain length (`maxTokensPerChain`) and a maximum number
// of chains to be stored (`maxChains`).
//
// Once initialized, Token chains can be copied into the cache with
// the `add` method. If `add` is called with more than
// `maxTokensPerChain` Tokens, a `ChainSizeLimitException` is thrown and
// the Tokens are not copied. If `add` is called and the TokenCache
// is full, a `FullCacheException` is thrown and the Tokens are not
// copied. Otherwise, an ID is returned that remains valid until
// it is removed (see `remove`).

class TokenCache {
    int m_chainCounter = 0;
    int m_maxTokensPerChain = 0;
    int m_maxChains = 0;
    int * m_chainLengths = nullptr;
    Token* * m_chains = nullptr;

public:
    ~TokenCache ();

    // Initialize the cache to hold a fixed max number of Tokens.
    //
    // @param maxTokens - determines the size of the cache
    void init (int maxChains, int maxTokensPerChain);

    // Indicates whether the cache has been initialized.
    bool isInitialized ();

    // Copies Tokens into the cache.
    //
    // @param tokens - a pointer to the beginning of the Tokens
    // @param num - the number of Tokens to copy
    //
    // @return the integer ID of the resulting Token chain
    int add (Token * tokens, int num);

    // Removes a chain and allows for the ID to be reused.
    // Added chains/IDs are kept active and accessible until they
    // are explicitly removed.
    // 
    // @param id - the ID to be released.
    void remove (int id);

    // Get a pointer to a Token chain within the cache.
    //
    // @param id - the integer id assigned to the Token chain
    //
    // @return a pointer to the first Token in the requested
    //         chain, or nullptr if the chain is not available
    Token * getChain (int id);

    // Get the length of a chain by its chain id.
    //
    // @param id - the integer id of the Token chain
    //
    // @return the number of Tokens in the chain, or -1 if
    //         the chain specified is not available
    int getChainLength (int id);

    // Get the max number of Tokens that can be added per chain.
    int getMaxTokensPerChain ();

    // Get the maximum number of chains that the cache can hold.
    int getMaxChains ();
};
