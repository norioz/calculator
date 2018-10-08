#include "Parser.h"

int Parser::getPrecedence (Token::Type op)
{
    switch (op) {
    case Token::OPER_ADD: return 1;
    case Token::OPER_SUB: return 1;
    case Token::OPER_MUL: return 2;
    case Token::OPER_DIV: return 2;
    default:
        // not a supported operator
        throw 8;
    }
}

bool Parser::isLeftAssociative (Token::Type op)
{
    return true;
}

void Parser::reset ()
{
    m_freeNodeIdx = 0;
}

// TODO copies into data?
ParseTreeNode * Parser::wrapToken (Token token)
{
    ParseTreeNode * node = m_nodes + m_freeNodeIdx;
    node->data = token;
    node->id = m_freeNodeIdx;
    ++m_freeNodeIdx;
    return node;
}

ParseTreeNode * Parser::parseTerm (Tokenizer & tokenizer)
{
    Token tok = tokenizer.getCurrent();
    if (tok.getType() == Token::PAREN_OPEN) {
        tokenizer.next();
        ParseTreeNode  * valTree = parseExpression(tokenizer, 1);
        if (tokenizer.getCurrent().getType() != Token::PAREN_CLOSE) {
            // unmatched (
            throw 5;
        }
        tokenizer.next();
        return valTree;
    }
    else if (tok.getType() == Token::UNASSIGNED) {
        // source ended unexpectedly
        throw 6;
    }
    else if (tok.isOperator()) {
        // expected atom, not operator
        throw 7;
    }
    else {
        if (!tok.isNumber()) {
            // expected number
            throw 8;
        }
        tokenizer.next();
        return wrapToken(tok);
    }
}

ParseTreeNode * Parser::parseExpression (Tokenizer & tokenizer, int minPrecidence)
{
    ParseTreeNode * root = parseTerm(tokenizer);

    while (tokenizer.getCurrent().isOperator() && 
        getPrecedence(tokenizer.getCurrent().getType()) >= minPrecidence) {
        ParseTreeNode * opNode = wrapToken(tokenizer.getCurrent());
        Token::Type opType = opNode->data.getType();
        int nextMinPrecedence = isLeftAssociative(opType) ? getPrecedence(opType) + 1 : getPrecedence(opType);

        tokenizer.next();
        ParseTreeNode * rhs = parseExpression(tokenizer, nextMinPrecedence);

        opNode->leftId = root->id;
        opNode->rightId = rhs->id;
        root = opNode;
    }

    return root;
}

const ParseTreeNode & Parser::getNodeById (int id)
{
    // TODO check for lt 0 and gte m_freeNodeIdx
    return m_nodes[id];
}

// returns a ref to the root
const ParseTreeNode & Parser::parse (Tokenizer & tokenizer)
{
    // Advance to the first Token.
    tokenizer.next();
    return *parseExpression(tokenizer, 0);
}
