#pragma once
#include "Token.h"
#include "ParseTree.h"

// Creats syntax trees from sequential lists of Tokens,
// intended for use in numeric calculations.

Token * parse (const Token * tokens, int length);