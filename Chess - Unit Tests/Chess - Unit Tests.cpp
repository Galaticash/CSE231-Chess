#include "pch.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	TEST_CLASS(ChessUnitTests)
	{
	public:
		
		/*TEST_METHOD(TestMethod1)
		{
			// Should return false
			int i = 12;
			int j = 1;
			int actual = i + j;
			Assert::AreEqual(13, actual);
		}

		TEST_METHOD(TestMethod2)
		{
			string one = "Hello";
			string two = "World";
			string both = one + " " + two;
			Assert::IsTrue("Hello World" == both);
			//Assert::AreEqual("Hello World", both);
		}*/

		// Function created for testing - NOT from another file
		// Figure out how to test without crashing (Maybe can't test Chess.cpp, but only Classes by including the .h file?)
		bool move(char* board, int indexFrom, int indexTo) 
		{
			if (board[indexTo] == ' ' && board[indexFrom] != ' ')
			{
				board[indexTo] = board[indexFrom];
				board[indexFrom] = ' ';
				return true;
			}
			return false;
		}

		TEST_METHOD(TestMethod3)
		{
			char board[64] = {
				'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P'
			};
			
			// Blank Board
			/*	    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
			};*/
			
			// Normal board
			/*
				'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
				'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				// ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
				'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
			};*/

			//Assert::IsTrue(board[63] == 'p');
			Assert::AreEqual('p', board[0]);
			Assert::AreEqual(' ', board[1]);
			Assert::AreEqual('P', board[63]);

			// Move piece to an empty square
			Assert::IsTrue(move(board, 63, 1));
			
			//lastMove = Move();
			//nextMove = user clicks

			returnValue = move(nextMove)
				if bool true:
					lastMove <- nextMove
				else:
					



			lastMove <- move(nextMove)

			
			//Assert::IsNotNull(move())

			Assert::AreEqual('P', board[1]);
			Assert::AreEqual(' ', board[63]);

			// Move piece ontop of another piece
			Assert::IsFalse(move(board, 1, 0));
			Assert::AreEqual('p', board[0]);
			Assert::AreEqual('P', board[1]);
			Assert::AreEqual(' ', board[63]);

			// Move 'nothing' to a space with 'nothing'
			Assert::IsFalse(move(board, 63, 2));
			Assert::AreEqual('p', board[0]);
			Assert::AreEqual('P', board[1]);
			Assert::AreEqual(' ', board[63]);

			//Assert::AreEqual(board[])
			//Assert::IsTrue(isNotWhite(board, 7, 7));
		}
	
		/*TEST_METHOD(TestMethod4) 
		{
			Assert::IsTrue(true);
		}*/

	
	};
}
