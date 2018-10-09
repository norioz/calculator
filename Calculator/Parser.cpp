#include "Parser.h"

// ----------------
// IMPL Parser

int Parser::getPrecedence (Token::Type op)
{
    switch (op) {
    case Token::OPER_ADD: return 1;
    case Token::OPER_SUB: return 1;
    case Token::OPER_MUL: return 2;
    case Token::OPER_DIV: return 2;
    default:
        throw ParseException("unexpected operator");
    }
}

bool Parser::isLeftAssociative (Token::Type op)
{
    return true;
}

ParseTreeNode * Parser::wrapToken (Token token)
{
    if (m_freeNodeIdx == MAX_TREE_SIZE) {
        throw ParseException("max parse tree size reached");
    }
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
            throw ParseException("unmatched open paren");
        }
        tokenizer.next();
        return valTree;
    }
    else if (tok.getType() == Token::UNASSIGNED) {
        throw ParseException("source ended unexpectedly");
    }
    else if (tok.isOperator()) {
        throw ParseException("atom expected, not operator");
    }
    else {
        if (!tok.isNumber()) {
            throw ParseException("expected number");
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
    if (id < 0 || id >= m_freeNodeIdx) {
        throw ParseTreeException("node index out of bounds");
    }
    return m_nodes[id];
}

const ParseTreeNode & Parser::parse (Tokenizer & tokenizer)
{
    // Rest the node store.
    m_freeNodeIdx = 0;

    // Advance to the first Token.
    tokenizer.next();
    return *parseExpression(tokenizer, 0);
}

// ----------------
// IMPL ParseException

ParseException::ParseException (const char * msg)
{
    m_msg = msg;
}

const char * ParseException::what () const throw()
{
    return m_msg;
}

// ----------------
// IMPL ParseException

ParseTreeException::ParseTreeException (const char * msg)
{
    m_msg = msg;
}

const char * ParseTreeException::what () const throw()
{
    return m_msg;
}
