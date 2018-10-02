#pragma once
#include "ParseTreeNode.h"
#include "Tokenizer.h"

class Parser {
    ParseTreeNode m_nodes[200];
    int m_freeNodeIdx = 0;

    ParseTreeNode * wrapToken (Token token);
    ParseTreeNode * parseTerm (Tokenizer & tokenizer);
    ParseTreeNode * parseExpression (Tokenizer & tokenizer, int minPrecidence);
public:
    static int getPrecedence (Token::Type op);
    static bool isLeftAssociative (Token::Type op);

    ParseTreeNode & parse (Tokenizer & tokenizer);
    void reset ();
};
