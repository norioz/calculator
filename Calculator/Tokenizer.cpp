#include <string.h>
#include <ctype.h>
#include "Tokenizer.h"

//char * m_input;
//int m_inputIdx;
//Token m_current;

bool isOperator (char c) {
    return c == '+' || c == '-' || c == '*' ||
        c == '/' || c == '=';
}

void Tokenizer::tokenize (const char * tokStr)
{
    m_current.clear();
    m_current.setStr(tokStr);
    
}

void Tokenizer::init (const char * input)
{
    m_inputLength = strlen(input);
    if (m_inputLength > MAX_INPUT_LENGTH) {
        throw 1;
    }
    strcpy(m_input, input);
    m_inputIdx = 0;
    next();
}

Token Tokenizer::getCurrent ()
{
    return m_current;
}

bool Tokenizer::next ()
{
    // Build up the next token string.

    char tokStr[MAX_INPUT_LENGTH];
    int tokStrIdx = 0;

    while (m_inputIdx < m_inputLength) {
        char c = m_input[m_inputIdx];

        if (isspace(c)) {
            if (tokStrIdx > 0) {
                tokStr[tokStrIdx] = '\0';
                break;
            }
            continue;
        }
        else if (c == '(' || c == ')') {

            if (tokStrIdx > 0) {
                tokStr[tokStrIdx] = '\0';
            }
            else {
                tokStr[0] = c;
                tokStr[1] = '\0';
                ++m_inputIdx;
            }
            break;
        }
        else if (isOperator(c)) {
            if (tokStrIdx > 0) {
                tokStr[tokStrIdx] = '\0';
                tokStrIdx
            }
        }

        else if (isdigit(c) || isalpha(c) || isOperator(c)) {
            tokStr[tokStrIdx++] = c;
        }

        else {
            // TODO need exception for unsupported character
            throw 5;
        }
    }
    tokenize(tokStr);
}
