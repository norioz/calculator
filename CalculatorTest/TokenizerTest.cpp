#include "pch.h"
#include <array>
#include "../Calculator/Tokenizer.h"

using namespace std;

// Helper function that loops through the tokens produced
// by tokenizing in and checks them against the values and types
// supplied.
void checkTokens (const char * in, int numVals, array<char*, 10> vals, array<Token::Type, 10> types) {
    Tokenizer tok;
    tok.init(in);
    int idx = 0;
    do {
        Token token = tok.getCurrent();
        EXPECT_STREQ(vals[idx], token.getStr());
        EXPECT_EQ(types[idx], token.getType());
        ++idx;
    } while (tok.next());
    EXPECT_EQ(numVals, idx);
}

TEST(TokenizerTest, LoadsCurrentOnInit) {
    Tokenizer t;
    t.init("1");
    
    // Expect that a call to init loads the first token.
    const char * result = t.getCurrent().getStr();
    EXPECT_STREQ("1", result);
}

TEST(TokenizerTest, ThrowsBeforeInit) {
    Tokenizer t;
    
    // Expect that getCurret throws if init hasn't been called.
    EXPECT_THROW(t.getCurrent(), UninitializedTokenizerException);

    // Expect that next throws if init hasn't been called.
    EXPECT_THROW(t.next(), UninitializedTokenizerException);
}

// What happens with empty initial input?

TEST(TokenizerTest, NextIsFalseAtEnd) {
    Tokenizer t;
    t.init("1 +");

    // Expect that the first call to next is true for the +.
    EXPECT_TRUE(t.next());

    // The input has run out. Expect that next returns false.
    EXPECT_FALSE(t.next());

    // All subsequent calls to next return false.
    EXPECT_FALSE(t.next());
}

TEST(TokenizerTest, Reinit) {
    Tokenizer t;
    t.init("1 +");
    t.next();
    
    // Expect that the Tokenizer can be reinitialized at the end of input.
    EXPECT_FALSE(t.next());
    t.init("2 + 1");
    EXPECT_STREQ("2", t.getCurrent().getStr());
    
    // Expect that the Tokenizer can be reinitialized before the end of input.
    EXPECT_TRUE(t.next());
    t.init("3");
    EXPECT_STREQ("3", t.getCurrent().getStr());
    EXPECT_FALSE(t.next());
}

TEST(TokenizerTest, SpecificExpressions) {
    // INT OP INT
    checkTokens("1 + 2", 3, { "1", "+", "2" }, { Token::NUM_INT, Token::OPER_ADD, Token::NUM_INT });
    checkTokens("3 * 4", 3, { "3", "*", "4" }, { Token::NUM_INT, Token::OPER_MUL, Token::NUM_INT });
    checkTokens("10 / 11", 3, { "10", "/", "11" }, { Token::NUM_INT, Token::OPER_DIV, Token::NUM_INT });
    checkTokens("12 - 100", 3, { "12", "-", "100" }, { Token::NUM_INT, Token::OPER_SUB, Token::NUM_INT });
    // INT OP FLOAT
    checkTokens("1 + 2.1", 3, { "1", "+", "2.1" }, { Token::NUM_INT, Token::OPER_ADD, Token::NUM_FLOAT});
    // FLOAT OP FLOAT
    checkTokens("1.1234 + 2.1", 3, { "1.1234", "+", "2.1" }, { Token::NUM_FLOAT, Token::OPER_ADD, Token::NUM_FLOAT });
}
