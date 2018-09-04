#pragma once

// TokenType enumerates the possible types that a token can
// be assigned.
// The `UNASSIGNED` type is reserved for Tokens that have
// not been assigned a value.
enum TokenType {
    UNASSIGNED, OPER_ADD, OPER_SUB, OPER_MUL, OPER_DIV,
    INT_NUM, FIXED_NUM
};

// Lexemes are the basic output units of scanning.
struct Token {
    TokenType type = UNASSIGNED;
    const char * val = nullptr;
};
