#pragma once

#include "Number.h"
#include "Parser.h"

class Evaluator {
public:
    Number eval (Parser & parser, const ParseTreeNode & root);
};
