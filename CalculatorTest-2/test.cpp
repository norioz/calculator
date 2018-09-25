#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include "pch.h"
#include "../Calculator/Tokenizer.h"

TEST(TokenizeTest, init) {
    Tokenizer t;
    t.init("1");
    EXPECT_STREQ("1", t.getCurrent().getStr());
}
