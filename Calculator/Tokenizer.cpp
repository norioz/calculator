#include <string.h>
#include <ctype.h>
#include "Tokenizer.h"

bool isOperator (char c)
{
    return c == '+' || c == '-' || c == '*' ||
        c == '/' || c == '=';
}

// No zero length tokStr.
void Tokenizer::tokenize (const char * tokStr)
{
    // Set the Token string.
    m_current.setStr(tokStr);

    Token::Type type = Token::typeForString(tokStr);
    if (type == Token::UNKNOWN) {
        // cannot assign type
        throw 4;
    }
    m_current.setType(type);
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
    // Throw exception if init hasn't been called.
    if (m_inputLength = -1) {
        UninitializedTokenizerException e;
        throw e;
    }

    return m_current;
}

bool Tokenizer::next ()
{
    // Throw exception if init hasn't been called.
    if (m_inputLength = -1) {
        UninitializedTokenizerException e;
        throw e;
    }

    // Clear out the current Token.
    m_current.clear();

    // Build up the next token string.
    char tokStr[MAX_INPUT_LENGTH];
    int tokStrIdx = 0;

    while (m_current.getType() == Token::UNASSIGNED) {
        char c = m_input[m_inputIdx];
        if (c == '\0') {
            if (tokStrIdx > 0) {
                tokStr[tokStrIdx] = '\0';
                tokenize(tokStr);
            }
            else {
                return false;
            }
        }
        else if (isspace(c)) {
            if (tokStrIdx > 0) {
                tokStr[tokStrIdx] = '\0';
                tokenize(tokStr);
            }
            ++m_inputIdx;
            continue;
        }
        else if (c == '+' || c == '-') {
            if (tokStrIdx == 0) {
                tokStr[tokStrIdx++] = c;
                ++m_inputIdx;
            }
        }
        else if (c == '(' || c == ')' || isOperator(c)) {
            if (tokStrIdx > 0) {
                tokStr[tokStrIdx] = '\0';
                tokenize(tokStr);
            }
            else {
                tokStr[0] = c;
                tokStr[1] = '\0';
                tokenize(tokStr);
                ++m_inputIdx;
            }
        }
        else {
            tokStr[tokStrIdx++] = c;
            ++m_inputIdx;
        }
    }
    return true;
}

const char * UninitializedTokenizerException::what () const throw()
{
    return "Tokenizer method called before init";
}
