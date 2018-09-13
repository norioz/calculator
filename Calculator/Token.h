#pragma once

// Tokens are the basic output units of scanning.
// Type enumerates the possible types that a token can
// be assigned.
// The `UNASSIGNED` type is reserved for Tokens that have
// not been assigned a value.

struct Token {
    enum Type {
        UNASSIGNED,
        OPER_ADD,
        OPER_SUB,
        OPER_MUL,
        OPER_DIV,
        OPER_ASSN,
        NAME,
        NUM_INT,
        NUM_FLOAT
    } type = UNASSIGNED;
    char val[20] = "UNASSGINED";
    int valLength = -1;
    Token * lchild = nullptr;
    Token * rchild = nullptr;
};
