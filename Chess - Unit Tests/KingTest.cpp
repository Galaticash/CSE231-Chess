#include "pch.h"
#include "CppUnitTest.h"

#include "../King.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	TEST_CLASS(KingTests)
	{
	public:
		TEST_METHOD(test1)
		{
			King kingTest = King(RC(1, 1), 1);

			kingTest.getPossibleMoves();

			// Check that it's all 8 squares, only 1
			// (see test cases and write them into code)


		}
	};
}