#pragma once
#include "Token.h"

struct ParseTreeNode {
    Token data;
    const ParseTreeNode * left = nullptr;
    const ParseTreeNode * right = nullptr;
};
