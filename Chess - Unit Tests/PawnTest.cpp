# pragma once
#include "pch.h"
#include "CppUnitTest.h"

#include <set>

#ifndef PIECE_CLASSES
#define PIECE_CLASSES
#include "../Pawn.h"
#include "../Space.h"

// For promotion
#include "../Queen.h"

// For a normal board
//#include "../Bishop.h"
//#include "../Rook.h"
//#include "../King.h"
//#include "../Knight.h"

#endif

// TODO: Change to a Board object, Piece* [][] kept inside

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	TEST_CLASS(PawnTests)
	{
	public:
		
		/* Helper function that inserts a Piece into the board */
		void insertPiece (Piece* board[8][8], Piece insert) {
			int row = insert.getCurrentPosition().getRow();
			int col = insert.getCurrentPosition().getCol();

			// Delete the previous Piece at that position (in most cases, Space)
			delete board[row][col];

			// Insert the new Piece
			board[row][col] = &insert;
		}

		/* A function immitating how Game would perform a move (Piece cannot move itself) */
		Move move(Piece* board[], Move currentMove, Move lastMove)
		{
			// Get the position of the Move
			RC pieceCurrentPos = currentMove.getPositionFrom();
			RC pieceDestination = currentMove.getPositionTo();
			// TODO: Assert RC positions are on the board (return lastMove if this Move cannot be completed)

			if (!(pieceCurrentPos == pieceDestination))
			{
				// Assert RC positions are not the same (no actual movement done)

				Piece movePiece = board[pieceCurrentPos.getRow()][pieceCurrentPos.getCol()];
				Piece destinationPiece = board[pieceDestination.getRow()][pieceDestination.getCol()];

				// Delete the old Piece/Space, and put in the new one
				insertPiece(board, movePiece);

				// Update the Piece's currentPosition, and hasMoved
				movePiece.setPosition(board, pieceDestination);

				// Replace the previous position with an empty space
				board[pieceCurrentPos.getRow()][pieceCurrentPos.getCol()] = Space();

				// If the movedPiece is a Pawn moving into the last row,
				if (movePiece.getType() == "PAWN")
				{
					if (movePiece.getCurrentPosition().getRow() == 8 || movePiece.getCurrentPosition().getRow() == 0)
					{
						// Replace the Pawn with a Queen
						insertPiece(board, Queen(movePiece.getCurrentPosition(), movePiece.getIsWhite()));
					}
				}

				return currentMove;
			}

			// The given Move could not be completed
			return lastMove;
		}

		// Runs all the test methods
		TEST_METHOD(testPawn)
		{
			hasMoved();
			pawnBlocked();
			diagAttackAll();
			diagAttackLeft();
			diagAttackRight();
			emptyBoard();
			enPassantLeft();
			enPassantRight;
			pawnPromotion();
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

			int row = 6;
			int col = 1;
			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(testBoard, testPawn);

			// EXERCISE - Pawn::getPossibleMoves()
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Can move forward one (row +/- based on Pawn color)
			// or move forward two (first move only)
			set<Move> expectedMoves = { Move(RC(row, col), RC(row + 1, col)), Move(RC(row, col), RC(row + 2, col)) };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves); <- There were errors in xutility/cppUnitTest.h (still occurring)

			// TEARDOWN
			//delete[] & testBoard;
			for (int r = 0; r < NUM_ROW; r++)
			{
				delete[] & testBoard[r];
			}
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
		 5 . * . . . . . . 5
		 6 . p . . . . . . 6
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

			int row = 6;
			int col = 1;
			Pawn testPawn = Pawn(RC(row, col), 1);
			insertPiece(*testBoard, testPawn);

			Assert::IsFalse(testPawn.getHasMoved());

			// EXERCISE - Move Pawn and call Pawn::getHasMoved()
			move(*testBoard, Move(RC(row, col), RC(row - 1, col)), Move());
			Assert::IsTrue(testPawn.getHasMoved());
			Assert::IsTrue(testPawn.getCurrentPosition() == RC(row - 1, col));

			// EXERCISE - Pawn::getPossibleMoves()
			set<Move> possibleMoves = testPawn.getPossibleMoves(*testBoard, Move());

			// VERIFY
			// Pawn can only move one space ahead
			set<Move> expectedMoves = { Move(RC(row, col), RC(testPawn.getCurrentPosition().getRow() - 1, col)) };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			//delete[] & testBoard;
			for (int r = 0; r < NUM_ROW; r++)
			{
				delete[] & testBoard[r];
			}
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

			int row = 6;
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
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
			delete[] & testBoard;
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
			set<Move> expectedMoves = { Move(RC(row, col), RC(row - 1, col)),  Move(RC(row, col), enemyPawn.getCurrentPosition()) };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
			//delete[] & testBoard;
			for (int r = 0; r < NUM_ROW; r++)
			{
				delete[] & testBoard[r];
			}
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
			set<Move> expectedMoves = { Move(RC(row, col), RC(row - 1, col)), Move(RC(row, col), enemyPawn.getCurrentPosition()) };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
			//delete[] & testBoard;
			for (int r = 0; r < NUM_ROW; r++)
			{
				delete[] & testBoard[r];
			}
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

			int row = 6;
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
			set<Move> expectedMoves = { Move(RC(row, col), enemyPawnOne.getCurrentPosition()), Move(RC(row, col), enemyPawnThree.getCurrentPosition()) };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
			//delete[] & testBoard;
			for (int r = 0; r < NUM_ROW; r++)
			{
				delete[] & testBoard[r];
			}
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
			set<Move> expectedMoves = { Move(RC(row, col), RC(row - 1, col)), Move(RC(row, col), RC(row - 1, col + 1)) };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
			//delete[] & testBoard;
			for (int r = 0; r < NUM_ROW; r++)
			{
				delete[] & testBoard[r];
			}
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
			int row = 3;
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
			set<Move> expectedMoves = { Move(RC(row, col), RC(row - 1, col)), Move(RC(row, col), RC(row - 1, col - 1)) };
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
			for (int r = 0; r < NUM_ROW; r++)
			{
				delete[] & testBoard[r];
			}
		}

		/*********************************
		* TEST move
		* Test that the Pawn will promote to Queen (after moving to last row 0 or 8).
			0 1 2 3 4 5 6 7
		 0 . * . . . . . . 0
		 1 . p . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(pawnPromotion)
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

			// EXERCISE - move Pawn to the last row (row 0, or 8)
			move(*testBoard, Move(RC(row, col), RC(row - 1, col)), Move());

			// VERIFY
			// Assert that the Pawn was replaced with a Queen Piece
			string queenType = "QUEEN";
			Assert::IsTrue(testBoard[row - 1][col]->getType() == queenType);
			//Assert::AreEqual(queenType, testBoard[row - 1][col]->getType());

			// TEARDOWN
			// delete board
			//delete[] & testBoard;
			for (int r = 0; r < NUM_ROW; r++)
			{
				delete[] & testBoard[r];
			}
		};

	};
}