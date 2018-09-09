#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Calculator/Token.h"

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {

            template<>
            static std::wstring ToString<enum TokenType>(const enum TokenType & tokenType) {
                return L"Some string representing TokenType.";
            }

        }
    }
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TokenType001)
		{
            // TODO this is not a complete test case.
            // It is only here to test the unit testing mechanism.
            Token t;
            t.type = UNASSIGNED;
            Assert::AreEqual(t.type, UNASSIGNED);
		}

	};
}