#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <ctype.h>
#include "Tokenizer.h"

bool isOperator (char c)
{
    return c == '+' || c == '-' || c == '*' ||
        c == '/' || c == '=';
}

void Tokenizer::tokenizeIntoNext (const char * tokStr)
{
    // Set the Token string.
    m_next.setStr(tokStr);

    Token::Type type = Token::typeForString(tokStr);
    if (type == Token::UNKNOWN) {
        // cannot assign type
        throw 4;
    }
    m_next.setType(type);
}

void Tokenizer::setNext ()
{
    // Clear out the next holder.
    m_next.clear();

    // Build up the next token string.
    char tokStr[MAX_INPUT_LENGTH];
    int tokStrIdx = 0;

    while (m_next.getType() == Token::UNASSIGNED) {
        char c = m_input[m_inputIdx];
        // c marks the end of the input
        if (c == '\0') {
            if (tokStrIdx > 0) {
                tokStr[tokStrIdx] = '\0';
                tokenizeIntoNext(tokStr);
            }
            else {
                return;  // leaving next as UNASSIGNED
            }
        }
        // c is a whitespace
        else if (isspace(c)) {
            if (tokStrIdx > 0) {
                tokStr[tokStrIdx] = '\0';
                tokenizeIntoNext(tokStr);
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
                tokenizeIntoNext(tokStr);
            }
            else {
                tokStr[0] = c;
                tokStr[1] = '\0';
                tokenizeIntoNext(tokStr);
                ++m_inputIdx;
            }
        }
        else {
            tokStr[tokStrIdx++] = c;
            ++m_inputIdx;
        }
    }
}

void Tokenizer::init (const char * input)
{
    m_current.clear();
    m_inputLength = strlen(input);
    if (m_inputLength > MAX_INPUT_LENGTH) {
        throw 1;
    }
    strcpy(m_input, input);
    m_inputIdx = 0;
    setNext();
}

Token Tokenizer::getCurrent ()
{
    // Throw exception if init hasn't been called.
    if (m_inputLength == -1) throw UninitializedTokenizerException();

    return m_current;
}

bool Tokenizer::next ()
{
    // Throw exception if init hasn't been called.
    if (m_inputLength == -1) throw UninitializedTokenizerException();

    // Terminate if there isn't anything next.
    if (m_next.getType() == Token::UNASSIGNED) {
        m_current.clear();
        return false;
    }
    
    // Copy next to current
    m_current.copy(m_next);

    // Set up the next Token.
    setNext();

    return true;
}

const char * UninitializedTokenizerException::what () const throw()
{
    return "Tokenizer method called before init";
}
