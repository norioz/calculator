#include "pch.h"
#include "../Calculator/Tokenizer.h"

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

TEST(TokenizerTest, BinOpsWithInts) {
    Tokenizer t;
    t.init("1 + 1");

}
