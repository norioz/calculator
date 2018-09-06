#include "TokenCache.h"

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

}

int TokenCache::add (const Token * tokens, int num)
{

}

Token * TokenCache::getById (int id)
{

}

int TokenCache::chainLength (int id)
{

}