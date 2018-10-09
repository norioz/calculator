#include <string>
#include <vector>
#include "pch.h"
#include "../Calculator/Parser.h"
#include "../Calculator/ParseTreeNode.h"
#include "../Calculator/Tokenizer.h"

using namespace std;

// Helper method that determines correctness of a parse tree
// by linearizing it in a breadth-first, left to right order.
// EXPECTS that the Tokens in the linearized parse tree match
// the expected strings and expected types, in the order that
// they are passed in.
// 
// @param expr - an expression to parse.
// @param expectedStrs - a vector of strings that represent
//     what the Token values should be after linearization.
// @param expectedTypes - a vector of Token types that
//     represent what the Token types should be after
//     linearization.
void checkTreeBreadthFirst (const char * expr, vector<string> expectedStrs, vector<Token::Type> expectedTypes)
{
    // Parser parser, const ParseTreeNode & root
    Tokenizer tokenizer;
    tokenizer.init(expr);
    Parser parser;
    ParseTreeNode root = parser.parse(tokenizer);
    vector<Token> actualTokens;
    const ParseTreeNode * todoPtrs[200];
    int todoPtrIdx = 0;
    todoPtrs[todoPtrIdx++] = &root;
    while (todoPtrIdx > 0) {
        const ParseTreeNode * node = todoPtrs[todoPtrIdx - 1];
        --todoPtrIdx;
        actualTokens.push_back(node->data);
        if (node->leftId >= 0) {
            const ParseTreeNode & n = parser.getNodeById(node->leftId);
            todoPtrs[todoPtrIdx++] = &n;
        }
        if (node->rightId >= 0) {
            const ParseTreeNode & n = parser.getNodeById(node->rightId);
            todoPtrs[todoPtrIdx++] = &n;
        }
    }

    ASSERT_EQ(expectedStrs.size(), actualTokens.size());

    for (int i = 0; i < expectedStrs.size(); ++i) {
        Token actualToken = actualTokens[i];
        EXPECT_STREQ(expectedStrs[i].c_str(), actualToken.getStr());
        EXPECT_EQ(expectedTypes[i], actualToken.getType());
    }
}


TEST(ParserTest, BinOps) {
    checkTreeBreadthFirst("1", { "1" }, { Token::NUM_INT });
    checkTreeBreadthFirst("1 + 2", { "+", "2", "1" }, { Token::OPER_ADD, Token::NUM_INT, Token::NUM_INT });
    checkTreeBreadthFirst("1 - 2 - 3", { "-", "3", "-", "2", "1" }, { Token::OPER_SUB, Token::NUM_INT, Token::OPER_SUB, Token::NUM_INT, Token::NUM_INT });
    checkTreeBreadthFirst("2 * 3 + 4", { "+", "4", "*", "3", "2" }, { Token::OPER_ADD, Token::NUM_INT, Token::OPER_MUL, Token::NUM_INT, Token::NUM_INT });
    checkTreeBreadthFirst("2 + 3 * 4", { "+", "*", "4", "3", "2" }, { Token::OPER_ADD, Token::OPER_MUL, Token::NUM_INT, Token::NUM_INT, Token::NUM_INT });
}

TEST(ParserTest, BinOpsWithParens) {
    checkTreeBreadthFirst("1 - (2 - 3)", { "-", "-", "3", "2", "1" }, { Token::OPER_SUB, Token::OPER_SUB, Token::NUM_INT, Token::NUM_INT, Token::NUM_INT });
    checkTreeBreadthFirst("(1 - 2) - 3", { "-", "3", "-", "2", "1" }, { Token::OPER_SUB, Token::NUM_INT, Token::OPER_SUB, Token::NUM_INT, Token::NUM_INT });
}

// TODO Add tests for ParseExpcetions.
