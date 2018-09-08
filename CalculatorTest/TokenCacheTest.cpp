#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Calculator/TokenCache.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TokenCacheInit001)
		{
            // TODO this is not a complete test case.
            // It is only here to test the unit testing mechanism.
            TokenCache tokenCache;
            tokenCache.init(10);
            Assert::IsTrue(tokenCache.isInitialized());
		}

	};
}