#include "pch.h"
#include "../Calculator/Tokenizer.h"

TEST(TokenizeTest, init) {
    Tokenizer t;
    t.init("1");
    const char * result = t.getCurrent().getStr();
    EXPECT_STREQ("1", result);
}
