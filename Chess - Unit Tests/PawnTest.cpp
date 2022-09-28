#include "pch.h"
#include "CppUnitTest.h"
#include <string>

//#include "../ChessGame/game.h"

#include "../Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	TEST_CLASS(ChessGame)
	{
	public:
		TEST_METHOD(test1)
		{
			char oldBoard[64] = {
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', 'p', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' 
			};

			char board[8][8] = {
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} };

			//Piece newBoard[8][8] = {};

			//board[9]
			Assert::AreEqual('p', board[9]);

			Piece dummy = Piece();

			Assert::AreEqual(dummy, board[9])


		}


	};

}