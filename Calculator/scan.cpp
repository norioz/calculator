#define _CRT_SECURE_NO_WARNINGS

#include <exception>
#include <string.h>
#include <ctype.h>
#include "scan.h"

using namespace std;

// Checks the val and valLength in the given token and assigns 
// an operator Token::Type to it if the val matches a supported
// operator.
//
// @param token - a partially completed Token that must have a
//         val and valLength
// @return an indicator of whether an opperator type was
//         assigned
bool assignTypeOper (Token & token)
{
    if (token.getStrLength() != 1) {
        return false;
    }
    switch (token.getStr()[0]) {
    case '+':
        token.setType(Token::OPER_ADD);
        return true;
    case '-':
        token.setType(Token::OPER_SUB);
        return true;
    case '*':
        token.setType(Token::OPER_MUL);
        return true;
    case '/':
        token.setType(Token::OPER_DIV);
        return true;
    case '=':
        token.setType(Token::OPER_ASSN);
        return true;
    default:
        return false;
    }
}

// Checks the val and valLength in the given token and assigns 
// the NUM_INT Token::Type to it if the val represents a whole
// number.
//
// @param token - a partially completed Token that must have a
//         val and valLength
// @return an indicator of whether NUM_INT was assigned
bool assignTypeInt (Token & token)
{
    const char * tokStr = token.getStr();
    for (int i = 0; i < token.getStrLength(); ++i) {
        if (!isdigit(tokStr[i])) {
            return false;
        }
    }
    Number * val = token.getVal();
    val->isInt = true;
    val->iVal = atoi(tokStr);
    token.setType(Token::NUM_INT);
    return true;
}

// Checks the val and valLength in the given token and assigns 
// the NUM_FLOAT Token::Type to it if the val represents 
// floating point number.
//
// @param token - a partially completed Token that must have a
//         val and valLength
// @return an indicator of whether NUM_FLOAT was assigned
bool assignTypeFloat (Token & token)
{
    const char * tokStr = token.getStr();
    int dotIdx = -1;
    for (int i = 0; i < token.getStrLength(); ++i) {
        if (tokStr[i] == '.') {
            if (dotIdx != -1) {
                return false;
            }
            else {
                dotIdx = i;
            }
        }
        else if (!isdigit(tokStr[i])) {
            return false;
        }
    }
    Number * val = token.getVal();
    val->isFloat = true;
    val->fVal = atof(tokStr);
    token.setType(Token::NUM_FLOAT);
    return true;
}

// Checks the val and valLength in the given token and assigns
// the NAME Token::Type to it if the val matches the rules for
// a supported name.
//
// @param token - a partially completed Token that must have a
//         val and valLength
// @return an indicator of whether the NAME type was assigned
bool assignTypeName (Token & token)
{
    for (int i = 0; i < token.getStrLength(); ++i) {
        const char * tokStr = token.getStr();
        char t = tokStr[i];
        if (!(t == '_' || isdigit(t) || isalpha(t))) {
            return false;
        }
    }
    token.setType(Token::NAME);
    return true;
}

int scan (const char * in, TokenCache & tc)
{
    int inputLength = strlen(in);
    int maxTokens = tc.getMaxTokensPerChain();

    // Copy the input so it can be tokenized in place.
    char input[200];
    strcpy(input, in);

    int tokenCounter = 0;
    Token tokens[200];

    // Split the input and convert it into Tokens.
    char * tokStr;
    tokStr = strtok(input, " ");
    while (tokStr != nullptr) {

        // Build a Token from the input text.
        Token token;
        token.setStr(tokStr);

        // Assign the Token a type.
        if (!(assignTypeOper(token) || assignTypeInt(token) ||
            assignTypeFloat(token) || assignTypeName(token))) {
            throw UnrecognizedTokenTypeException(tokStr);
        }

        // Add the completed Token to the output holder.
        tokens[tokenCounter++] = token;

        // Get the next input.
        tokStr = strtok(nullptr, " ");
    }

    return tc.add(tokens,tokenCounter);
}

// UnrecognizedTokenTypeException IMPL
UnrecognizedTokenTypeException::UnrecognizedTokenTypeException(const char * text) : m_text(text) {}

const char * UnrecognizedTokenTypeException::getText ()
{
    return m_text;
}

const char * UnrecognizedTokenTypeException::what () const throw()
{
    char result[100];
    strcpy(result, m_text);
    strcat(result, " does not match a TokenType");
    return result;
}
