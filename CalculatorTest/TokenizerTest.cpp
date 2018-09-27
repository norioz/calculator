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
    while(tok.next()) {
        Token token = tok.getCurrent();
        EXPECT_STREQ(vals[idx], token.getStr());
        EXPECT_EQ(types[idx], token.getType());
        ++idx;
    }
    EXPECT_EQ(numVals, idx);
}

TEST(TokenizerTest, GetValueBeforeNext) {
    Tokenizer t;
    t.init("1");
    
    // Expect that a call to init does not load the first token.
    EXPECT_EQ(Token::UNASSIGNED, t.getCurrent().getType());
}

TEST(TokenizerTest, ThrowsBeforeInit) {
    Tokenizer t;
    
    // Expect that getCurret throws if init hasn't been called.
    EXPECT_THROW(t.getCurrent(), UninitializedTokenizerException);

    // Expect that next throws if init hasn't been called.
    EXPECT_THROW(t.next(), UninitializedTokenizerException);
}

TEST(TokenizerTest, NextAfterInputEnds) {
    Tokenizer t;
    t.init("1");

    // Expect that the first call to next is true for the 1.
    EXPECT_TRUE(t.next());

    // The input has run out. Expect that next returns false.
    EXPECT_FALSE(t.next());
    EXPECT_EQ(Token::UNASSIGNED, t.getCurrent().getType());

    // All subsequent calls to next return false.
    EXPECT_FALSE(t.next());
    EXPECT_EQ(Token::UNASSIGNED, t.getCurrent().getType());
}

TEST(TokenizerTest, Reinit) {
    Tokenizer t;
    t.init("1");
    t.next();
    
    // Expect that the Tokenizer can be reinitialized at the end of input.
    EXPECT_FALSE(t.next());
    t.init("2 + 1");
    EXPECT_EQ(Token::UNASSIGNED, t.getCurrent().getType());
    t.next();
    EXPECT_STREQ("2", t.getCurrent().getStr());
    
    // Expect that the Tokenizer can be reinitialized before the end of input.
    EXPECT_TRUE(t.next());
    t.init("3");
    EXPECT_EQ(Token::UNASSIGNED, t.getCurrent().getType());
    t.next();
    EXPECT_STREQ("3", t.getCurrent().getStr());
    EXPECT_FALSE(t.next());
}

TEST(TokenizerTest, PeekNext) {
    Tokenizer tok;
    tok.init("1 +");
    
    // Expect that peekNext is valid after init without next call.
    Token t = tok.peekNext();
    EXPECT_STREQ("1", t.getStr());

    // Expect that getCurrent is now what next was, after update.
    tok.next();
    EXPECT_STREQ("1", tok.getCurrent().getStr());
    
    // Expect that next has updated to '+'.
    t = tok.peekNext();
    EXPECT_STREQ("+", t.getStr());

    // Expect that getCurrent is '+', after update.
    tok.next();
    EXPECT_STREQ("+", tok.getCurrent().getStr());

    // Expect that next has updated and is now type UNASSIGNED
    // because there is no next Token.
    t = tok.peekNext();
    EXPECT_EQ(Token::UNASSIGNED, t.getType());

    // Expect that a call to next returns false.
    EXPECT_FALSE(tok.next());

    // Expect that both current and next are UNASSIGNED.
    t = tok.peekNext();
    EXPECT_EQ(Token::UNASSIGNED, t.getType());
    EXPECT_EQ(Token::UNASSIGNED, tok.getCurrent().getType());
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
