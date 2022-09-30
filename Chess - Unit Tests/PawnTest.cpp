# pragma once
#include "pch.h"
#include "CppUnitTest.h"

#include "../Pawn.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	TEST_CLASS(PawnTests)
	{
	public:
		TEST_METHOD(test1)
		{
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
			Assert::AreEqual('p', board[0][0]);

			Piece dummy = Piece();

			//Assert::AreEqual(dummy, board[0][0])

		}
	
		TEST_METHOD(TranslateMove) 
		{
			string smithNotation = "a1b1Q";
			//RC positionTo = smithNotation[];
			//RC positionFrom = smithNotation[];
			int stringSize = smithNotation.length();
			if (stringSize > 4)
			{
				// Capture or Castling
				char specialCase = smithNotation[4];
				if (stringSize > 5)
				{
					if (stringSize == 6)
					{
						// Capture AND Promotion
						char promotion = smithNotation[5];
					}
					else
					{
						// Broke
						Assert::IsFalse(true);
					}
				}
			}
		
		}
	
	};

}