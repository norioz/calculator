#include <exception>
#include "TokenCache.h"

// Exception to be thrown when methods are
// called before initialization has been completed.
class UninitializedException : public std::exception
{
    virtual const char * what () const throw()
    {
        return "TokenCache not initialized";
    }
} uninitalized;

class SizeLimit : public std::exception
{
    virtual const char * what () const throw()
    {
        return "Cache maxToken size too small for requested add";
    }
} sizeLimit;

TokenCache::~TokenCache ()
{
    delete[] m_chainIds;
    m_chainIds = nullptr;
    delete[] m_chainLengths;
    m_chainLengths = nullptr;
    delete[] m_tokens;
    m_tokens = nullptr;
}

void TokenCache::init (int maxTokens)
{
    m_maxTokens = maxTokens;
    m_chainIds = new int[maxTokens];
    for (int i = 0; i < maxTokens; ++i) { m_chainIds[i] = -1; }
    m_chainLengths = new int[maxTokens];
    for (int i = 0; i < maxTokens; ++i) { m_chainLengths[i] = -1; }
    m_tokens = new Token[maxTokens];
}

bool TokenCache::isInitialized ()
{
    return m_tokens != nullptr;
}

int TokenCache::add (const Token * tokens, int num)
{
    if (!isInitialized()) throw uninitalized;
    
    if (num > m_maxTokens) throw sizeLimit;

    // If there isn't enough room left to store the Tokens
    // reset the current id to the start.
    if (m_startIdxCounter + num >= m_maxTokens) {
        m_startIdxCounter = 0;
    }

    // Wipe out all IDs and lengths for chains that will
    // be overwritten.


    // Transcibe the Tokens.
    for (int i = 0; i < num; ++i) {
        Token source = tokens[i];
        Token target = m_tokens[i];
        target.fVal = source.fVal;
        target.iVal = source.iVal;
        target.type = source.type;
        // child pointers are not copied
    }

    // Update the start index counter.
    m_startIdxCounter += num;

    // Assign the chain an ID.
    

    return 
}

Token * TokenCache::getById (int id)
{
}

int TokenCache::chainLength (int id)
{
}