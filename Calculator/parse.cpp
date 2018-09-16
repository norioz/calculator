#include "parse.h"

// We only have expressions, numbers, and operators.
// Each parse expression takes in a 

// expression ::= number operator expression | number

// expression ::= expression operator term | term
// term ::= (expression) | number

// expression ::= expression + factor | factor
// factor ::= factor * term | term
// term ::= (expression) | number

// expression ::= factor + expression | factor
// factor ::= term + factor | term
// term ::= (expression) | number

Token * parseNumber (Token * tc, int idx)
{
    Token::Type type = tc[idx].getType();
    if (type != Token::NUM_FLOAT && type != Token::NUM_INT) {
        throw 1;
    }
    return tc + idx;
}

Token * parseOperator (Token * tc, int idx)
{
    if (!tc[idx].isOperator()) {
        throw 2;
    }
    return tc + idx;
}

// return the root
Token * parseExpression (Token * tc, int idx, int chainLength)
{
    // Expect a number in the current position.
    Token * root = parseNumber(tc, idx);

    // Return if there are no more tokens.
    if (idx == chainLength - 1) {
        return root;
    }

    // Error if there aren't at least 2 more tokens.
    if (chainLength - idx < 3) {
        throw 3;
    }

    // Read the operator and recurse.
    if (tc[idx + 1].isOperator()) {
        Token * op = parseOperator(tc, idx + 1);
        op->setLeftChild(root);
        op->setRightChild(parseExpression(tc, idx + 2, chainLength));
        root = op;
    }
    return root;
}

Token * parse (TokenCache & tc, int chainId)
{
    Token * chain = tc.getChain(chainId);
    int chainLength = tc.getChainLength(chainId);
    
    return parseExpression(chain, 0, chainLength);
}
