#pragma once

// TokenType enumerates the possible types that a token can
// be assigned.
// The `UNASSIGNED` type is reserved for Tokens that have
// not been assigned a value.
enum TokenType {
    UNASSIGNED, OPER_ADD, OPER_SUB, OPER_MUL, OPER_DIV,
    OPER_ASSN, NAME, INT_NUM, FIXED_NUM,
};

// Tokens are the basic output units of scanning.
struct Token {
    TokenType type = UNASSIGNED;
    long long iVal = -1;
    double fVal = -1.0;
    Token * lchild = nullptr;
    Token * rchild = nullptr;
};
