#pragma once
#include "Token.h"

class TokenStore {

    void init (int maxTokens, int valLength);

    // copies the tokens into the store
    int push (const Token * tokens, int num);

    Token * getById (int id);

    int chainLength (int id);
};