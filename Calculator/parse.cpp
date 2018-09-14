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

bool isOperator (Token::Type type)
{
    return type == Token::OPER_ADD ||
        type == Token::OPER_ASSN || 
        type == Token::OPER_DIV ||
        type == Token::OPER_MUL ||
        type == Token::OPER_SUB;
}

Token * parseNumber (Token * tc, int idx)
{
    Token::Type type = tc[idx].type;
    if (type != Token::NUM_FLOAT && type != Token::NUM_INT) {
        throw 1;
    }
    return tc + idx;
}

Token * parseOperator (Token * tc, int idx)
{
    if (!isOperator(tc[idx].type)) {
        throw 2;
    }
    return tc + idx;
}

// return the root
Token * parseExpression (Token * tc, int idx)
{
    // TODO Need termination condition at end of chain
    Token * result = parseNumber(tc, idx);
    if (isOperator(tc[idx + 1].type)) {
        Token * op = parseOperator(tc, idx + 1);
        op->childL = result;
        op->childR = parseExpression(tc, idx + 2);
        result = op;
    }
    return result;
}

Token * parse (TokenCache & tc, int chainId)
{
    Token * chain = tc.getChain(chainId);
    int chainLength = tc.getChainLength(chainId);
    
    return parseExpression(chain, 0);
}
