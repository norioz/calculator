#include <string>
#include <vector>
#include "pch.h"
#include "../Calculator/Parser.h"
#include "../Calculator/ParseTreeNode.h"
#include "../Calculator/Tokenizer.h"

//ParseTreeNode & parse (Tokenizer & tokenizer);

using namespace std;

// left first
void checkTreeDepthFirst (const char * expr, vector<string> expectedStrs, vector<Token::Type> expectedTypes)
{
    // Parser parser, const ParseTreeNode & root
    Tokenizer tokenizer;
    tokenizer.init(expr);
    Parser parser;
    ParseTreeNode root = parser.parse(tokenizer);
    vector<Token> actualTokens;
    vector<ParseTreeNode> todo;
    todo.push_back(root);
    while (!todo.empty()) {
        ParseTreeNode node = todo.back();
        todo.pop_back();
        actualTokens.push_back(node.data);
        if (node.leftId >= 0) {
            ParseTreeNode n = parser.getNodeById(node.leftId);
            todo.push_back(n);
        }
        if (node.rightId >= 0) {
            ParseTreeNode n = parser.getNodeById(node.rightId);
            todo.push_back(n);
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
    checkTreeDepthFirst("1", { "1" }, { Token::NUM_INT });
    checkTreeDepthFirst("1 + 2", { "+", "1", "2" }, { Token::OPER_ADD, Token::NUM_INT, Token::NUM_INT });
}
