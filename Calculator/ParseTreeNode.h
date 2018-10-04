#pragma once
#include "Token.h"

struct ParseTreeNode {
    Token data;
    int id = -1;
    int leftId = -1;
    int rightId = -1;
};
