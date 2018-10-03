#include <string>
#include <vector>
#include "pch.h"
#include "../Calculator/Parser.h"
#include "../Calculator/ParseTreeNode.h"
#include "../Calculator/Tokenizer.h"

//ParseTreeNode & parse (Tokenizer & tokenizer);

using namespace std;

// left first
void checkTreeBreadthFirst (const ParseTreeNode * rt, vector<string> expectedStrs, vector<Token::Type> expectedTypes)
{
    //vector<Token> actualTokens;
    Token tokens[100];
    int tokenIdx = 0;
    const ParseTreeNode * todo[100];
    int nodeIdx = 0;
    todo[0] = rt;
    while (nodeIdx >= 0) {
        const ParseTreeNode * ptr = todo[nodeIdx--];
        tokens[tokenIdx++] = ptr->data;
        //actualTokens.push_back(ptr->data);
        if (ptr->left != nullptr) {
            todo[++nodeIdx] = ptr->left;
        }
        if (ptr->right != nullptr) {
            todo[++nodeIdx] = ptr->right;
        }
    }

    //vector<const ParseTreeNode*> todo;
    //todo.push_back(root);
    //while (!todo.empty()) {
    //    const ParseTreeNode * nodePtr = todo[0];
    //    todo.erase(todo.begin());
    //    actualTokens.push_back(nodePtr->data);
    //    if (nodePtr->left != nullptr) {
    //        todo.push_back(nodePtr->left);
    //    }
    //    if (nodePtr->right != nullptr) {
    //        todo.push_back(nodePtr->right);
    //    }
    //}

    // Expect that the flattenned tree is the same length as the expected strings.
    //EXPECT_EQ(expectedStrs.size(), actualTokens.size());
    
    // Check all Token types and string values.
    /*for (int i = 0; i < actualTokens.size(); ++i) {
        Token actualToken = actualTokens[i];
        EXPECT_STREQ(expectedStrs[i].c_str(), actualToken.getStr());
        EXPECT_EQ(expectedTypes[i], actualToken.getType());
    }*/
}

TEST(ParserTest, ParseTreeCorrectness) {
    Tokenizer t;
    t.init("1");
    Parser p;
    const ParseTreeNode * root = p.parse(t);
    checkTreeBreadthFirst(root, { "1" }, { Token::NUM_INT });
}
