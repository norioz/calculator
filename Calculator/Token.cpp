#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <ctype.h>
#include "Token.h"

Token::Type Token::typeForString (const char * tokStr)
{
    int strLength = strlen(tokStr);

    // Check for operator types.
    if (strLength == 1) {
        char c = tokStr[0];
        switch (c) {
        case '+':
            return Token::OPER_ADD;
        case '-':
            return Token::OPER_SUB;
        case '*':
            return Token::OPER_MUL;
        case '/':
            return Token::OPER_DIV;
        case '(':
            return Token::PAREN_OPEN;
        case ')':
            return Token::PAREN_CLOSE;
        case '=':
            return Token::OPER_ASSN;
        }
    }

    // Check for number types.
    bool isNumber = tokStr[0] == '+' || tokStr[0] == '-' || isdigit(tokStr[0]);
    int numDots = 0;
    for (int i = 1; i < strLength; ++i) {
        char c = tokStr[i];
        if (c == '.') {
            ++numDots;
        }
        else if (!isdigit(c)) {
            isNumber = false;
            break;
        }
    }
    if (isNumber) {
        if (numDots = 0) {
            return Token::NUM_INT;
        }
        else if (numDots = 1) {
            return Token::NUM_FLOAT;
        }
        else {
            return Token::UNKNOWN;
        }
    }
    
    // Check for Name type.
    bool isName = true;
    for (int i = 0; i < strLength; ++i) {
        char c = tokStr[i];
        if (!(c == '_' || isalnum(c))) {
            isName = false;
            break;
        }
    }
    if (isName) {
        return Type::NAME;
    }
    
    // Type not found.
    return Token::UNKNOWN;
}

bool Token::isNumber ()
{
    return m_type == Token::NUM_FLOAT || m_type == Token::NUM_INT;
}

bool Token::isOperator ()
{
    return m_type == Token::OPER_ADD || m_type == Token::OPER_ASSN ||
        m_type == Token::OPER_DIV || m_type == Token::OPER_MUL ||
        m_type == Token::OPER_SUB;
}

bool Token::isParen ()
{
    return m_type == Token::PAREN_CLOSE || m_type == Token::PAREN_OPEN;
}

Token::Type Token::getType () { return m_type; }
void Token::setType (Token::Type t) { m_type = t; }

char * Token::getStr () { return m_str; }
void Token::setStr (const char * str)
{
    strcpy(m_str, str);
    m_strLength = strlen(m_str);
}

int Token::getStrLength () { return m_strLength; }

Number * Token::getVal ()
{
    return &m_val;
}
void Token::setVal (int val)
{
    m_val.isInt = true;
    m_val.iVal = val;
}
void Token::setVal (double val)
{
    m_val.isFloat = true;
    m_val.fVal = val;
}

Token * Token::getLeftChild () { return m_childL; }
void Token::setLeftChild (Token * child) { m_childL = child; }

Token * Token::getRightChild () { return m_childR; }
void Token::setRightChild (Token * child) { m_childR = child; }

void Token::clear ()
{
    m_type = Token::UNASSIGNED;
    m_val.isFloat = false;
    m_val.isInt = false;
    m_strLength = -1;
    m_childL = nullptr;
    m_childR = nullptr;
}