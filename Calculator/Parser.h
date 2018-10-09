#pragma once
#include <exception>
#include "ParseTreeNode.h"
#include "Tokenizer.h"
#define MAX_TREE_SIZE 200

// A precedence climbing parser that stores nodes internally.
// Parser uses a passed in Tokenizer to form a parse tree based
// on operator precedence and associativity.
// The Parser stores all ParseTreeNodes for the tree in an
// internal store and assigns them IDs during tree creation.
// 
// Parse an expression by calling parse with a Tokenizer.
//
// Tokenizer t; t.init("1 + 2");
// Parser p; 
// const ParseTreeNode & root = p.parse(t);
//
// The returned root node can then be used to traverse the parse
// tree.
//
//  const ParseTreeNode left = p.getNodeById(root.leftId);

class Parser {
    ParseTreeNode m_nodes[MAX_TREE_SIZE];
    int m_freeNodeIdx = 0;

    // Wraps the given Token in a ParseTreeNode that
    // is stored in the Parser's node array.
    //
    // @return a pointer to the ParseTreeNode within the Parser's
    //     node array.
    ParseTreeNode * wrapToken (Token token);

    // Parses a "term" that is either a number or an expression
    // surrounded in parenthesis.
    // term := ( expr ) | number
    //
    // @note Calls parseExpression for expression parsing.
    // 
    // @param tokenizer - a Tokenizer (t) such that t.getCurrent() returns
    //     the Token that begins the term.
    //
    // @return a pointer to the root node of the term
    ParseTreeNode * parseTerm (Tokenizer & tokenizer);

    // Parse an "expression" into a tree of ParseTreeNodes using a precedence
    // climbing algorithm.
    //
    // @param tokenizer - a Tokenizer (t) such that t.getCurrent() returns
    //     the Token that begins the expression.
    // @param minPrecidence - a compounded precidence value that should begin 
    //     as 1 on the first call and is incremented in recursion.
    ParseTreeNode * parseExpression (Tokenizer & tokenizer, int minPrecidence);

public:

    // Get the fixed precedence value of the passed in operator.
    // 
    // @param op - a Token Type that represents an operator.
    //
    // @return 1, 2, or 3 such that higher indicates greater precedence.
    static int getPrecedence (Token::Type op);

    // Indicates if the given operator is LEFT associative.
    // 
    // @param op - a Token Type that represents an operator.
    //
    // @return a boolean indication of whether the op is LEFT associative.
    static bool isLeftAssociative (Token::Type op);

    // Get a reference to a ParseTreeNode within the Parser's node store
    // given its ID.
    // 
    // @param id - the ID of an allocated ParseTreeNode.
    // 
    // @return a ref to a ParseTreeNode.
    const ParseTreeNode & getNodeById (int id);

    // Parses the expression represented by the given Tokenizer into a
    // parse tree. The parse tree is stored within the Parser's node store
    // and the tree can be traversed, from the root, via IDs.
    //
    // @param tokenizer - a tokenizer that has been initialized but has
    //     not had next called.
    //
    // @return a ref to a ParseTreeNode that represents the root of the
    //     parse tree.
    const ParseTreeNode & parse (Tokenizer & tokenizer);
};

class ParseException : public std::exception {
    const char * m_msg;
public:
    ParseException (const char * msg);
    virtual const char * what () const throw();
};

class ParseTreeException : public std::exception {
    const char * m_msg;
public:
    ParseTreeException (const char * msg);
    virtual const char * what () const throw();
};
