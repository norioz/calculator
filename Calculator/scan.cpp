#define _CRT_SECURE_NO_WARNINGS

#include <exception>
#include <string.h>
#include <ctype.h>
#include "scan.h"

using namespace std;

bool assignTypeOper (Token & token)
{
    if (token.valLength != 1) {
        return false;
    }
    switch (token.val[0]) {
    case '+':
        token.type = Token::OPER_ADD;
        return true;
    case '-':
        token.type = Token::OPER_SUB;
        return true;
    case '*':
        token.type = Token::OPER_MUL;
        return true;
    case '/':
        token.type = Token::OPER_DIV;
        return true;
    case '=':
        token.type = Token::OPER_ASSN;
        return true;
    default:
        return false;
    }
}

bool assignTypeInt (Token & token)
{
    for (int i = 0; i < token.valLength; ++i) {
        if (!isdigit(token.val[i])) {
            return false;
        }
    }
    token.type = Token::NUM_INT;
    return true;
}

bool assignTypeFloat (Token & token)
{
    int dotIdx = -1;
    for (int i = 0; i < token.valLength; ++i) {
        if (token.val[i] == '.') {
            if (dotIdx != -1) {
                return false;
            }
            else {
                dotIdx = i;
            }
        }
        else if (!isdigit(token.val[i])) {
            return false;
        }
    }
    token.type = Token::NUM_FLOAT;
    return true;
}

bool assignTypeName (Token & token)
{
    for (int i = 0; i < token.valLength; ++i) {
        char t = token.val[i];
        if (!(t == '_' || isdigit(t) || isalpha(t))) {
            return false;
        }
    }
    token.type = Token::NAME;
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
    char * tok;
    tok = strtok(input, " ");
    while (tok != nullptr) {

        // Build a Token from the input text.
        Token token;
        strcpy(token.val, in);
        token.valLength = strlen(tok);

        // Assign the Token a type.
        if (!(assignTypeOper(token) || assignTypeInt(token) ||
            assignTypeFloat(token) || assignTypeName(token))) {
            throw UnrecognizedTokenTypeException(tok);
        }

        // Add the completed Token to the output holder.
        tokens[tokenCounter++] = token;

        // Get the next input.
        tok = strtok(nullptr, " ");
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
