#pragma once
#include "Token.h"
#define MAX_INPUT_LENGTH 200

class Tokenizer {
    char m_input[MAX_INPUT_LENGTH];
    int m_inputLength = -1;
    int m_inputIdx = -1;
    Token m_current;

    void tokenize (const char * tokStr);

public:

    void init (const char * input);
    
    Token getCurrent ();

    bool next ();

};
