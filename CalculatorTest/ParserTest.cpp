#include <string>
#include <vector>
#include "pch.h"
#include "../Calculator/Parser.h"
#include "../Calculator/ParseTreeNode.h"
#include "../Calculator/Tokenizer.h"

//ParseTreeNode & parse (Tokenizer & tokenizer);

using namespace std;

// left first
void checkTreeDepthFirst (Parser parser, const ParseTreeNode & root, vector<string> expectedStrs, vector<Token::Type> expectedTypes)
{
    vector<Token> actualTokens;
    vector<ParseTreeNode> todo;
    todo.push_back(root);
    while (!todo.empty()) {
        ParseTreeNode & node = todo[0];
        actualTokens.push_back(node.data);
        if (node.leftId >= 0) {
            todo.push_back(parser.getNodeById(node.leftId));
        }
        if (node.rightId >= 0) {
            todo.push_back(parser.getNodeById(node.rightId));
        }
        todo.erase(todo.begin());
    }

    ASSERT_EQ(expectedStrs.size(), actualTokens.size());

    for (int i = 0; i < expectedStrs.size(); ++i) {
        Token actualToken = actualTokens[i];
        EXPECT_STREQ(expectedStrs[i].c_str(), actualToken.getStr());
        EXPECT_EQ(expectedTypes[i], actualToken.getType());
    }
}

TEST(ParserTest, ParseTreeCorrectness) {
    Tokenizer t;
    t.init("1");
    Parser p;
    checkTreeDepthFirst(p, p.parse(t), { "1" }, { Token::NUM_INT });
    t.init("1 + 2");
    // TODO reset seems unneeded. The parser should reset on parse.
    p.reset();
    checkTreeDepthFirst(p, p.parse(t), { "+", "1", "2" }, { Token::OPER_ADD, Token::NUM_INT, Token::NUM_INT });
}
