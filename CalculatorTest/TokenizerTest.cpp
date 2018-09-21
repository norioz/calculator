#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Calculator/Tokenizer.h"

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {
            template<>
            static std::wstring ToString<enum Token::Type>(const enum Token::Type & tokenType) {
                return L"Some string representing TokenType.";
            }

        }
    }
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTest
{		
	TEST_CLASS(TokenizerUnitTests)
	{
	public:
        TEST_METHOD(UninitializedTests)
        {
            Tokenizer tok;

            // Ensure exception when calling `getCurrent()` without init.
            Assert::ExpectException<UninitializedTokenizerException>([&]
            {
                tok.getCurrent();
            });

            // Ensure exception when calling `next()` without init.
            Assert::ExpectException<UninitializedTokenizerException>([&]
            {
                tok.next();
            });
        }
        TEST_METHOD(InitTests)
        {
            Tokenizer tok;
            tok.init("1 + 1");
            
            // Ensure that current is something after init.
            Token t = tok.getCurrent();
            Assert::AreEqual(t.getStr, "1");

            // TODO What should happen if a Tokenizer is initialized with
            // an empty string?
        }
        TEST_METHOD(NextTest)
        {
            Tokenizer tok;
            tok.init("1 +");

            // Ensure that calling next returns true.
            bool wasUpdated = tok.next();
            Assert::IsTrue(wasUpdated);

            // Ensure that calling next without using getCurrent returns the second val.
            Token t = tok.getCurrent();
            Assert::AreEqual(t.getStr, "+");

            // TODO Ensure that calling next after the last token returns false.
            wasUpdated = tok.next();
            Assert::IsFalse(wasUpdated);
            
        }
		//TEST_METHOD(BinOperatorTests)
		//{
  //          Tokenizer tok;
  //          
		//}
  //      TEST_METHOD(IntegerTests)
  //      {

  //      }
  //      TEST_METHOD(FloatTests)
  //      {

  //      }
  //      TEST_METHOD(NameTests)
  //      {

  //      }
	};
}