#pragma once

#include "Number.h"

// Tokens are the basic output units of scanning.
// Type enumerates the possible types that a token can
// be assigned.
// The `UNASSIGNED` type is reserved for Tokens that have
// not been assigned a value.

class Token {
public:
    enum Type {
        UNASSIGNED,
        OPER_ADD,
        OPER_SUB,
        OPER_MUL,
        OPER_DIV,
        OPER_ASSN,
        NAME,
        NUM_INT,
        NUM_FLOAT,
        PAREN_OPEN,
        PAREN_CLOSE
    };

    bool isNumber ();

    bool isOperator ();

    bool isParen();

    void setType (Type t);
    Token::Type getType ();

    void setStr (const char * str);
    char * getStr ();

    int getStrLength ();

    void setVal (int val);
    void setVal (double val);
    Number * getVal ();

    void setLeftChild (Token * child);
    Token * getLeftChild ();

    void setRightChild (Token * child);
    Token * getRightChild ();

    void clear ();

private:
    Type m_type = UNASSIGNED;
    char m_str[20] = "UNASSGINED";
    int m_strLength = -1;
    Number m_val;
    Token * m_childL = nullptr;
    Token * m_childR = nullptr;
};
