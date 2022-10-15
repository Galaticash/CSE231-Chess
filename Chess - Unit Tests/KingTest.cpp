/***********************************************************************
 * King Test Cases
 * Author: Logan Huston
 *
 * Summary: Tests different variations of King's movements,
 *	asserting that the set of Moves from King::getPossibleMoves
 * match what is expected. Includes Castling.
 ************************************************************************/

#pragma once
#include "pch.h"
#include "CppUnitTest.h"

#include <set>            // for STD::SET

#include "../board.h"

#include "../King.cpp"
#include "../Rook.cpp"
#include "../Space.h"
#include "../Pawn.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	TEST_CLASS(KingTests)
	{
		Piece* EMPTY_BOARD[NUM_ROW][NUM_COL] =
		{
			{ new Space(RC(0, 0)), new Space(RC(0, 1)), new Space(RC(0, 2)), new Space(RC(0, 3)), new Space(RC(0, 4)), new Space(RC(0, 5)), new Space(RC(0, 6)), new Space(RC(0, 7))},
			{ new Space(RC(1, 0)), new Space(RC(1, 1)), new Space(RC(1, 2)), new Space(RC(1, 3)), new Space(RC(1, 4)), new Space(RC(1, 5)), new Space(RC(1, 6)), new Space(RC(1, 7)) },
			{ new Space(RC(2, 0)), new Space(RC(2, 1)), new Space(RC(2, 2)), new Space(RC(2, 3)), new Space(RC(2, 4)), new Space(RC(2, 5)), new Space(RC(2, 6)), new Space(RC(2, 7)) },
			{ new Space(RC(3, 0)), new Space(RC(3, 1)), new Space(RC(3, 2)), new Space(RC(3, 3)), new Space(RC(3, 4)), new Space(RC(3, 5)), new Space(RC(3, 6)), new Space(RC(3, 7)) },
			{ new Space(RC(4, 0)), new Space(RC(4, 1)), new Space(RC(4, 2)), new Space(RC(4, 3)), new Space(RC(4, 4)), new Space(RC(4, 5)), new Space(RC(4, 6)), new Space(RC(4, 7)) },
			{ new Space(RC(5, 0)), new Space(RC(5, 1)), new Space(RC(5, 2)), new Space(RC(5, 3)), new Space(RC(5, 4)), new Space(RC(5, 5)), new Space(RC(5, 6)), new Space(RC(5, 7)) },
			{ new Space(RC(6, 0)), new Space(RC(6, 1)), new Space(RC(6, 2)), new Space(RC(6, 3)), new Space(RC(6, 4)), new Space(RC(6, 5)), new Space(RC(6, 6)), new Space(RC(6, 7)) },
			{ new Space(RC(7, 0)), new Space(RC(7, 1)), new Space(RC(7, 2)), new Space(RC(7, 3)), new Space(RC(7, 4)), new Space(RC(7, 5)), new Space(RC(7, 6)), new Space(RC(7, 7)) } };

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
			TestKingAttacking();
		}

		/**********************************
		* TEST KING MOVEMENT
		* Test all basic movement options for the king.
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
		******************************************/
		TEST_METHOD(TestKingMovement)
		{
			// SETUP
			Board testBoard(EMPTY_BOARD);
			King kingTest = King(RC(1, 1), 1);
			testBoard.insertPiece(&kingTest);

			// EXERCISE
			set <Move> possibleMoves = kingTest.getPossibleMoves(&testBoard, Move());

			// VERIFY   possible.insert(Move(RC(row, col), RC(r, c)));
			set <Move> expectedMoves = set<Move> { 
				{Move(RC(1, 1), RC(0, 0))}, {Move(RC(1, 1), RC(0, 1))}, 
				{Move(RC(1, 1), RC(0, 2))}, {Move(RC(1, 1), RC(1, 0))},
				{Move(RC(1, 1), RC(1, 2))}, {Move(RC(1, 1), RC(2, 0))}, 
				{Move(RC(1, 1), RC(2, 1))}, {Move(RC(1, 1), RC(2, 2))} };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
		}

		/*******************************
		* TEST CASTLING QUEEN
		* Test that queen side castling works. 
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
		***********************************/
		TEST_METHOD(TestCastlingQueen)
		{
			// setup
			Board testBoard(EMPTY_BOARD);

			King kingTest = King(RC(0, 4), 1);
			Rook rookTestLeft = Rook(RC(0, 0), 1);
			Rook rookTestRight = Rook(RC(0, 7), 1);
			Pawn pawnTest1 = Pawn(RC(0, 5), 1);
			Pawn pawnTest2 = Pawn(RC(1, 3), 1);
			Pawn pawnTest3 = Pawn(RC(1, 4), 1);
			Pawn pawnTest4 = Pawn(RC(1, 5), 1);

			testBoard.insertPiece(&kingTest);
			testBoard.insertPiece(&rookTestLeft);
			testBoard.insertPiece(&rookTestRight);
			testBoard.insertPiece(&pawnTest1);
			testBoard.insertPiece(&pawnTest2);
			testBoard.insertPiece(&pawnTest3);
			testBoard.insertPiece(&pawnTest4);

			// exercise
			set <Move> possibleMoves = kingTest.getPossibleMoves(&testBoard, Move());

			// verify
			Move castling = Move(RC(0, 4), RC(0, 3));
			castling.setCastlingQ();
			set <Move> expectedMoves = set<Move> { 
				{ Move(RC(0, 4), RC(0, 2)) }, 
				castling };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
		}

		/*********************************
		* TEST CASTLING KING
		* Test that king side castling works.
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
		**********************************/
		TEST_METHOD(TestCastlingKing)
		{
			// SETUP
			Board testBoard(EMPTY_BOARD);

			King kingTest = King(RC(0, 4), 1);
			Rook rookTestLeft = Rook(RC(0, 0), 1);
			Rook rookTestRight = Rook(RC(0, 7), 1);
			Pawn pawnTest1 = Pawn(RC(0, 3), 1);
			Pawn pawnTest2 = Pawn(RC(1, 3), 1);
			Pawn pawnTest3 = Pawn(RC(1, 4), 1);
			Pawn pawnTest4 = Pawn(RC(1, 5), 1);

			testBoard.insertPiece(&kingTest);
			testBoard.insertPiece(&rookTestLeft);
			testBoard.insertPiece(&rookTestRight);
			testBoard.insertPiece(&pawnTest1);
			testBoard.insertPiece(&pawnTest2);
			testBoard.insertPiece(&pawnTest3);
			testBoard.insertPiece(&pawnTest4);

			// exercise
			set <Move> possibleMoves = kingTest.getPossibleMoves(&testBoard, Move());

			// verify
			Move castlingKing = Move(RC(0, 4), RC(0, 6));
			castlingKing.setCastlingK();
			set <Move> expectedMoves = set<Move> { 
				{ Move(RC(0, 4), RC(0, 5)) }, 
				castlingKing };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
		}

		/************************************
		* TEST KING BLOCKED
		* Test that when all movement options are covered by friendly
		* pieces, the king can't move.
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
		****************************************/
		TEST_METHOD(TestKingBlocked)
		{
			// setup
			Board testBoard(EMPTY_BOARD);

			King kingTest = King(RC(1, 5), 1);
			Pawn pawnTest1 = Pawn(RC(0, 4), 1);
			Pawn pawnTest2 = Pawn(RC(0, 5), 1);
			Pawn pawnTest3 = Pawn(RC(0, 6), 1);
			Pawn pawnTest4 = Pawn(RC(1, 4), 1);
			Pawn pawnTest5 = Pawn(RC(1, 6), 1);
			Pawn pawnTest6 = Pawn(RC(2, 4), 1);
			Pawn pawnTest7 = Pawn(RC(2, 5), 1);
			Pawn pawnTest8 = Pawn(RC(2, 6), 1);

			testBoard.insertPiece(&kingTest);
			testBoard.insertPiece(&pawnTest1);
			testBoard.insertPiece(&pawnTest2);
			testBoard.insertPiece(&pawnTest3);
			testBoard.insertPiece(&pawnTest4);
			testBoard.insertPiece(&pawnTest5);
			testBoard.insertPiece(&pawnTest6);
			testBoard.insertPiece(&pawnTest7);
			testBoard.insertPiece(&pawnTest8);

			// exercise
			set <Move> possibleMoves = kingTest.getPossibleMoves(&testBoard, Move());

			// verify
			Assert::IsTrue(possibleMoves.empty());

			// TEARDOWN
		}

		/*************************************
		* TEST KING ATTACKING
		* Test that all of the kings attacking options work.
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
		***********************************/
		TEST_METHOD(TestKingAttacking)
		{
			// setup
			Board testBoard(EMPTY_BOARD);

			King kingTest = King(RC(5, 4), 1);
			Pawn pawnTest1 = Pawn(RC(4, 3), 0);
			Pawn pawnTest2 = Pawn(RC(4, 4), 0);
			Pawn pawnTest3 = Pawn(RC(4, 5), 0);
			Pawn pawnTest4 = Pawn(RC(5, 3), 0);
			Pawn pawnTest5 = Pawn(RC(5, 5), 0);
			Pawn pawnTest6 = Pawn(RC(6, 3), 0);
			Pawn pawnTest7 = Pawn(RC(6, 4), 0);
			Pawn pawnTest8 = Pawn(RC(6, 5), 0);

			testBoard.insertPiece(&kingTest);
			testBoard.insertPiece(&pawnTest1);
			testBoard.insertPiece(&pawnTest2);
			testBoard.insertPiece(&pawnTest3);
			testBoard.insertPiece(&pawnTest4);
			testBoard.insertPiece(&pawnTest5);
			testBoard.insertPiece(&pawnTest6);
			testBoard.insertPiece(&pawnTest7);
			testBoard.insertPiece(&pawnTest8);

			// exercise
			set <Move> possibleMoves = kingTest.getPossibleMoves(&testBoard, Move());

			// verify
			set <Move> expectedMoves = set<Move> { {Move(RC(5, 4), RC(4, 3))}, {Move(RC(5, 4), RC(4, 4))}, {Move(RC(5, 4), RC(4, 5))}, {Move(RC(5, 4), RC(5, 3))},
				{Move(RC(5, 4), RC(5, 5))}, {Move(RC(5, 4), RC(6, 3))}, {Move(RC(5, 4), RC(6, 4))}, {Move(RC(5, 4), RC(6, 5))} };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
		}
	};
}
