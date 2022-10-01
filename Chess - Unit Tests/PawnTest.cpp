# pragma once
#include "pch.h"
#include "CppUnitTest.h"

#ifndef PIECE_CLASSES
#define PIECE_CLASSES
#include "../Pawn.h"
#include "../Space.h"

// For a normal board
#include "../Bishop.h"
#include "../Rook.h"
#include "../King.h"
#include "../Knight.h"
#include "../Queen.h"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	const int NUM_ROW = 8;
	const int NUM_COL = 8;
	TEST_CLASS(PawnTests)
	{
	public:
		
		Piece* DEFAULT_BOARD[NUM_ROW][NUM_COL] = {
					{&Rook(RC(0, 0), 0), &Bishop(RC(0, 1), 0), &Knight(RC(0, 2), 0), &Queen(RC(0, 3), 0), &King(RC(0, 4), 0), &Knight(RC(0, 5), 0), &Bishop(RC(0, 6), 0), &Rook(RC(0, 7), 0)},
					{&Pawn(RC(1, 0), 0), &Pawn(RC(1, 1), 0), &Pawn(RC(1, 2), 0), &Pawn(RC(1, 3), 0), &Pawn(RC(1, 4), 0), &Pawn(RC(1, 5), 0), &Pawn(RC(1, 6), 0), &Pawn(RC(1, 7), 0)},
					{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
					{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
					{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
					{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
					{&Pawn(RC(6, 0), 1), &Pawn(RC(6, 1), 1), &Pawn(RC(6, 2), 1), &Pawn(RC(6, 3), 1), &Pawn(RC(6, 4), 1), &Pawn(RC(6, 5), 1), &Pawn(RC(6, 6), 1), &Pawn(RC(6, 7), 1)},
					{&Rook(RC(7, 0), 1), &Bishop(RC(7, 1), 1), &Knight(RC(7, 2), 1), &Queen(RC(7, 3), 1), &King(RC(7, 4), 1), &Knight(RC(7, 5), 1), &Bishop(RC(7, 6), 1), &Rook(RC(7, 7), 1)} };

		Piece* EMPTY_BOARD[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

		/* Helper function that inserts a Piece into the board */
		void insertPiece (Piece* board[], Piece insert) {
			board[insert.getCurrentPosition().getRow()][insert.getCurrentPosition().getCol()] = insert;
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn can move forward one (or two, if hasMoved == false).
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(emptyBoard)
		{
			// SETUP - setup the board with a single White Pawn
			Piece* testBoard[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };
			
			int row = 1;
			int col = 1;
			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(*testBoard, testPawn);

			// EXERCISE - Pawn::getPossibleMoves()
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Can move forward one (row +/- based on Pawn color)
			// or move forward two (first move only)
			set<Move> expectedMoves = { Move(RC(row, col), RC(row + 1, col)), Move(RC(row, col), RC(row + 2, col)) };
			Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
			delete[] &testBoard;
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn can only move forward one after it has already moved.
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . p . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(hasMoved)
		{
			// SETUP - setup the board with one White Pawn
			Piece* testBoard[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			int row = 1;
			int col = 1;
			insertPiece(*testBoard, Pawn(RC(row, col), 1));

			// EXERCISE - Move Pawn and call Pawn::getHasMoved()
			// TODO: move the Pawn, with hasMoved being updated

			// VERIFY
			Assert::IsTrue(testBoard[row][col]->getHasMoved());

			delete[] &testBoard;
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn cannot move if blocked.
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . P . . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(pawnBlocked)
		{
			// SETUP - Place an enemy Piece in the way of the testPawn's forward movement
			Piece* testBoard[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			int row = 1;
			int col = 1;
			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(*testBoard, testPawn);

			Piece enemyPiece = Piece(RC(row - 1, col), 0);
			insertPiece(*testBoard, enemyPiece);

			// EXERCISE - Pawn::getPossibleMoves()
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Assert that the Pawn cannot move
			set<Move> expectedMoves = {};
			Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
			delete[] &testBoard;
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn can attack a Pawn of the opposite color (right).
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . P . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(diagAttackRight)
		{
			// SETUP - Place an enemy Pawn to the right diagonally from the testPawn
			Piece* testBoard[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			int row = 6;
			int col = 1;
			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(*testBoard, testPawn);

			// TODO: Check that secondary Pawn is placed in front of first Pawn (direction travelling)
			Pawn enemyPawn = Pawn(RC(row - 1, col + 1), 0);
			insertPiece(*testBoard, enemyPawn);

			// EXERCISE - Pawn::getPossibleMoves
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Assert that the Pawn can attack move forward or attack enemyPawn
			set<Move> expected = { Move(RC(row, col), RC(row - 1, col)),  Move(RC(row, col), enemyPawn.getCurrentPosition()) };
			Assert::AreEqual(expected, possibleMoves);

			// TEARDOWN
			delete[] &testBoard;
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn can attack a Pawn of the opposite color (left).
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 P . . . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(diagAttackLeft)
		{
			// SETUP - Place an enemy Pawn diagonally to the left of the testPawn
			Piece* testBoard[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			// RC placement of the testPawn
			int row = 6;
			int col = 1;

			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(*testBoard, testPawn);

			Pawn enemyPawn = Pawn(RC(row - 1, col - 1), 0);
			insertPiece(*testBoard, enemyPawn);

			// EXERCISE - Pawn::getPossibleMoves
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Assert that the Pawn can attack move forward or attack the enemyPawn
			set<Move> expected = { Move(RC(row, col), RC(row -1, col)), Move(RC(row, col), enemyPawn.getCurrentPosition()) };
			Assert::AreEqual(expected, possibleMoves);

			// TEARDOWN
			delete[] &testBoard;
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn can attack a Pawn of the opposite color even when blocked.
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 P P P . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(diagAttackAll)
		{
			// Setup - Put three enemy Pawns in front of the testPawn
			Piece* testBoard[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			int row = 1;
			int col = 1;
			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(*testBoard, testPawn);

			// TODO: Check that secondary Pawn is placed in front of first Pawn (direction travelling)
			Pawn enemyPawnOne = Pawn(RC(row + 1, col - 1), 0);
			insertPiece(*testBoard, enemyPawnOne);
			Pawn enemyPawnTwo = Pawn(RC(row + 1, col), 0);
			insertPiece(*testBoard, enemyPawnTwo);
			Pawn enemyPawnThree = Pawn(RC(row + 1, col + 1), 0);
			insertPiece(*testBoard, enemyPawnThree);

			// EXERCISE - Pawn::getPossibleMoves			
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Assert that the Pawn can attack move diagonally and attack Pawns of the opposite color, but not forward (blocked)
			set<Move> expected = { Move(RC(row, col), enemyPawnOne.getCurrentPosition()), Move(RC(row, col), enemyPawnThree.getCurrentPosition())};
			Assert::AreEqual(expected, possibleMoves);
		
			// TEARDOWN
			delete[] &testBoard;
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn can perform an en-passant capture (right).
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . p P . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(enPassantRight)
		{
			// SETUP - Place an enemy Pawn to the right of the testPawn, having just moved two spaces
			Piece* testBoard[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			// RC of the testPawn
			int row = 3;
			int col = 1;
			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(*testBoard, testPawn);

			// Enemy Pawn to the right
			Pawn enemyPawn = Pawn(RC(row, col + 1), 0);
			insertPiece(*testBoard, enemyPawn);

			Move lastMove = Move(testBoard[enemyPawn.getCurrentPosition().getRow()][enemyPawn.getCurrentPosition().getCol()]->getType(), RC(row - 2, col + 1), enemyPawn.getCurrentPosition());

			// EXERCISE - Pawn::getPossibleMoves			
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Assert that the Pawn can attack a Pawn in the same row BUT will move to the space behind it
			set<Move> expected = { Move(RC(row, col), RC(row - 1, col)), Move(RC(row, col), RC(row - 1, col + 1)) };
			Assert::AreEqual(expected, possibleMoves);

			// TEARDOWN
			delete[] &testBoard;
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn can perform an en-passant capture (left).
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 P p . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(enPassantLeft)
		{
			// SETUP - Place an enemy Pawn to the left of the testPawn, having just moved two spaces
			Piece* testBoard[NUM_ROW][NUM_COL] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &Space(RC(1, 1)), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			// RC of the testPawn
			int row = 1;
			int col = 1;
			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(*testBoard, testPawn);

			// Enemy Pawn to the left
			Pawn enemyPawn = Pawn(RC(row, col - 1), 0);
			insertPiece(*testBoard, enemyPawn);

			Move lastMove = Move(testBoard[enemyPawn.getCurrentPosition().getRow()][enemyPawn.getCurrentPosition().getCol()]->getType(), RC(row - 2, col - 1), enemyPawn.getCurrentPosition());

			// EXERCISE - Pawn::getPossibleMoves			
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Assert that the Pawn can attack a Pawn in the same row BUT will move to the space behind it
			set<Move> expected = { Move(RC(row, col), RC(row - 1, col)), Move(RC(row, col), RC(row - 1, col - 1)) };
			Assert::AreEqual(expected, possibleMoves);

			// TEARDOWN
			delete[] & testBoard;
		}
	};
}