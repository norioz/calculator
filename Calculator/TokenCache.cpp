#define _CRT_SECURE_NO_WARNINGS

#include <exception>
#include <string.h>
#include "TokenCache.h"

// Exception to be thrown when methods are
// called before initialization has been completed.
class UninitializedException : public std::exception
{
    virtual const char * what () const throw()
    {
        return "TokenCache not initialized";
    }
};

class ChainSizeLimitException : public std::exception
{
    virtual const char * what () const throw()
    {
        return "chain is too large to be stored";
    }
};

class CacheFullException : public std::exception
{
    virtual const char * what () const throw()
    {
        return "cache full";
    }
};

TokenCache::~TokenCache ()
{
    delete[] m_chainLengths;
    m_chainLengths = nullptr;
    for (int i = 0; i < m_maxChains; ++i) {
        delete[] m_chains[i];
    }
    delete[] m_chains;
    m_chains = nullptr;
    m_maxTokensPerChain = 0;
    m_maxChains = 0;
}

void TokenCache::init (int maxChains, int maxTokensPerChain)
{
    m_maxChains = maxChains;
    m_maxTokensPerChain = maxTokensPerChain;
    m_chainLengths = new int[maxChains];
    for (int i = 0; i < maxChains; ++i) {
        m_chainLengths[i] = -1;
    }
    m_chains = new Token*[maxChains];
    for (int i = 0; i < maxChains; ++i) {
        m_chains[i] = new Token[maxTokensPerChain];
    }
}

bool TokenCache::isInitialized ()
{
    return m_chains != nullptr;
}

int TokenCache::add (const Token * tokens, int num)
{
    if (!isInitialized()) throw UninitializedException();

    if (num > m_maxTokensPerChain) throw ChainSizeLimitException();

    if (m_chainCounter == m_maxChains) throw CacheFullException();

    // Find an open chain slot.
    int idx = 0;
    while (idx < m_maxChains) {
        if (m_chainLengths[idx] == -1) {
            break;
        }
        ++idx;
    }

    // Transcibe the Tokens.
    Token * chain = m_chains[idx];
    for (int i = 0; i < num; ++i) {
        Token source = tokens[i];
        Token target = chain[i];
        target.valLength = source.valLength;
        strcpy(target.val, source.val);
        target.type = source.type;
        target.lChildChianIdx = source.lChildChianIdx;
        target.rChildChianIdx = source.rChildChianIdx;
    }
    m_chainLengths[idx] = num;

    return idx;
}

void TokenCache::remove (int id)
{
    --m_chainCounter;
    m_chainLengths[id] = -1;
}

Token * TokenCache::getChain (int id)
{
    if (m_chainLengths[id] == -1) {
        return nullptr;
    }
    return m_chains[id];
}

int TokenCache::getChainLength (int id)
{
    return m_chainLengths[id];
}

int TokenCache::getMaxTokensPerChain ()
{
    return m_maxTokensPerChain;
}

int TokenCache::getMaxChains ()
{
    return m_maxChains;
}
