#pragma once
#include "Token.h"
#include "ParseTree.h"

// Creats syntax trees from sequential lists of Tokens,
// intended for use in numeric calculations.

class Parser {
public:

    void init(int maxSize);

    void parse (Token * tokens);

    ParseTree getParseTree ();
};
