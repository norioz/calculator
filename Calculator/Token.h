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
        UNKNOWN,
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

    // Gives the appropriate Type for the given input c-string
    // or Type UNKNOWN if an appropriate type was not found.
    //
    // @param tokStr - a c-string to be analyzed
    // @return a Token::Type that matches tokStr or UNKNOWN if
    //     no Type matches.
    static Token::Type typeForString (const char * tokStr);

    // Indicates if this Token is a number.
    bool isNumber ();

    // Indicates if this Token is an operator.
    bool isOperator ();

    // Indicates if this Token is either an open or close paren.
    bool isParen();

    // Setter and getter for the Type of this Token.
    void setType (Type t);
    Token::Type getType ();

    // Setter and getter for the c-string value of this Token.
    void setStr (const char * str);
    char * getStr ();

    // Getter for the length of the c-string value of this Token.
    // The length of the value is set automatically with setStr.
    int getStrLength ();

    // Getters and setters for the numeric values of this Token.
    void setVal (int val);
    void setVal (double val);
    Number * getVal ();

    // Getter and setter for the left child of this Token.
    void setLeftChild (Token * child);
    Token * getLeftChild ();

    // Getter and setter for the right child of this Token.
    void setRightChild (Token * child);
    Token * getRightChild ();

    // Resets this Token to the same state as when it was created.
    // Immediate calls to getters will return the same values
    // as when this Token was instantiated.
    void clear ();

private:
    Type m_type = UNASSIGNED;
    char m_str[20] = "UNASSGINED";
    int m_strLength = -1;
    Number m_val;
    Token * m_childL = nullptr;
    Token * m_childR = nullptr;
};
