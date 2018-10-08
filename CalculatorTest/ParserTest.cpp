#include <string>
#include <vector>
#include "pch.h"
#include "../Calculator/Parser.h"
#include "../Calculator/ParseTreeNode.h"
#include "../Calculator/Tokenizer.h"

//ParseTreeNode & parse (Tokenizer & tokenizer);

using namespace std;

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

TEST(ParserTest, ParseTreeCorrectness) {
    // TODO reset seems unneeded. The parser should reset on parse.
    checkTreeBreadthFirst("1", { "1" }, { Token::NUM_INT });
    checkTreeBreadthFirst("1 + 2", { "+", "2", "1" }, { Token::OPER_ADD, Token::NUM_INT, Token::NUM_INT });
    checkTreeBreadthFirst("1 - 2 - 3", { "-", "3", "-", "2", "1" }, { Token::OPER_SUB, Token::NUM_INT, Token::OPER_SUB, Token::NUM_INT, Token::NUM_INT });
}
