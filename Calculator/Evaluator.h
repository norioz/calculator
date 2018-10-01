#pragma once

#include "Number.h"
#include "Token.h"

class Evaluator {
public:
    Number eval (Token * root);
};
