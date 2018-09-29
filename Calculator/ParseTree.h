#pragma once
#include "Token.h"

struct ParseTree {
    const Token * data = nullptr;
    const ParseTree * left = nullptr;
    const ParseTree * right = nullptr;
};
