# pragma once
#include "pch.h"
#include "CppUnitTest.h"

#include <set>            // for STD::SET

#include "../King.h"
#include "../Rook.h"
#include "../Space.h"
#include "../Pawn.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	TEST_CLASS(KingTests)
	{
	public:
		/* Helper method to insert pieces into board */
		void InsertPiece(Piece* board[8][8], Piece piece) 
		{
			RC pos = piece.getCurrentPosition();
			board[pos.getRow()][pos.getCol()] = &piece;
		}


		TEST_METHOD(TestKing)
		{
			TestCastlingKing();
			TestCastlingKing();
			TestKingMovement();
			TestKingBlocked();
			TestKingCapturing();
		}

		/*
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . k . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestKingMovement)
		{
			// SETUP
			Piece* board[8][8] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &King(RC(1, 1), 0), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			King kingTest = King(RC(1, 1), 1);
			InsertPiece(board, kingTest);

			// EXERCISE
			set <Move>possibleMoves = kingTest.getPossibleMoves(*board, Move());

			// VERIFY
			// Check that it's all 8 squares, only 1
			// (see test cases and write them into code)
			Assert::AreEqual(true, true);

			// TEARDOWN
			delete board;
		}

		/*
			0 1 2 3 4 5 6 7
		 0 r . . . k p . r 0
		 1 . . . p p p . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestCastlingQueen)
		{
			// setup
			Piece* board[8][8] = {
			{&Space(RC(0, 0)), & Space(RC(0, 1)), & Space(RC(0, 2)), & Space(RC(0, 3)), & Space(RC(0, 4)), & Space(RC(0, 5)), & Space(RC(0, 6)), & Space(RC(0, 7))},
			{ &Space(RC(1, 0)), &King(RC(1, 1), 0), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7)) },
			{ &Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7)) },
			{ &Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7)) },
			{ &Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7)) },
			{ &Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7)) },
			{ &Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7)) },
			{ &Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7)) }
		};
			// exercise
			// verify
			// takedown
		}

		/*
			0 1 2 3 4 5 6 7
		 0 r . . p k . . r 0
		 1 . . . p p p . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestCastlingKing)
		{
			// setup
			Piece* board[8][8] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &King(RC(1, 1), 0), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };
			// exercise
			// verify
			// takedown
		}

		/*
			0 1 2 3 4 5 6 7
		 0 . . . . p p p . 0
		 1 . . . . p k p . 1
		 2 . . . . p p p . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestKingBlocked)
		{
			// setup
			Piece* board[8][8] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Pawn(RC(0, 4), 1), &Pawn(RC(0, 5), 1), &Pawn(RC(0, 6), 1), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Pawn(RC(1, 4), 1), &King(RC(1, 5), 1), &Pawn(RC(1, 6), 1), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Pawn(RC(2, 4), 1), &Pawn(RC(2, 5), 1), &Pawn(RC(2, 6), 1), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };
			// exercise
			// verify
			// takedown
		}

		/*
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . P P P . . 4
		 5 . . . P k P . . 5
		 6 . . . P P P . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestKingCapturing)
		{
			// setup
			Piece* board[8][8] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Pawn(RC(4, 3), 0), &Pawn(RC(4, 4),0), &Pawn(RC(4, 5), 0), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Pawn(RC(5, 3), 0), &King(RC(5, 4), 1), &Pawn(RC(5, 5), 0), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Pawn(RC(6, 3), 0), &Pawn(RC(6, 4), 0), &Pawn(RC(6, 5), 0), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			// exercise
			// verify
			// takedown
		}
	};
}
