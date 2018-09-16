#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include "Token.h"

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
