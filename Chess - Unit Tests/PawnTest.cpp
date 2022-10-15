/***********************************************************************
 * Pawn Test Cases
 * Author: Ashley DeMott
 *
 * Summary: Tests different variations of Pawn's movements, 
 *	asserting that the set of Moves from Pawn::getPossibleMoves
 *  match what is expected. Includes Promotion and En-Passant.
 *
 ************************************************************************/

# pragma once
#include "pch.h"
#include "CppUnitTest.h"

#include <set>
#include <iostream>

// Includes the Board object
#include "../board.cpp"

//#include "../piece.cpp"
#include "../Pawn.h"
//#include "../Space.h"
#include "../Queen.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessUnitTests
{
	// The size of the Chess board
	const int NUM_ROW = 8;
	const int NUM_COL = 8;

	// An empty board of Space Piece pointers
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


	TEST_CLASS(PawnTests)
	{
	public:

		// Runs all the test methods
		TEST_METHOD(testPawn)
		{
			// Will assume Pawn has not moved
			emptyBoard();

			// All other test will assume the Pawn has already moved
			pawnBlocked();
			diagAttackAll();
			diagAttackForward();
			diagAttackLeft();
			diagAttackRight();			
			enPassantLeft();
			enPassantRight();
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
		 4 . * . . . . . . 4
		 5 . * . . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(emptyBoard)
		{
			// SETUP - setup the board with a single White Pawn
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0); // Pawn is placed on Black's side, assume Black's turn

			// RC coordinates of the testPawn
			int row = 6;
			int col = 1;

			// Place test Pawn
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);

			// EXERCISE - Pawn::getPossibleMoves()
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, Move());
			
			// VERIFY
			set<Move> expectedMoves = { 
				Move(RC(row, col), RC(row - 1, col)),	// Move forward one
				Move(RC(row, col), RC(row - 2, col)) }; // Move forward two

			Assert::AreEqual(expectedMoves.size(), possibleMoves.size());
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves); //<- error since it can't display as has no to_string, requires operator<<
			
			// TEARDOWN
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
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0);

			// RC coordinates of the testPawn
			int row = 6;
			int col = 1;
			
			// Place test Pawn
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);

			// Place enemy Pawn
			Piece enemyPiece = Piece(RC(row - 1, col), 1);
			testBoard.insertPiece(&enemyPiece);

			// EXERCISE - Pawn::getPossibleMoves()
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, Move());

			// VERIFY
			// Assert that the Pawn has no possibleMoves
			Assert::IsTrue(possibleMoves.empty());
			//Assert::AreEqual(size_t(0), possibleMoves.size());

			// TEARDOWN
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
		 5 . * P . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(diagAttackRight)
		{
			// SETUP - Place an enemy Pawn to the right diagonally from the testPawn
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0);
			
			// RC coordinates of the testPawn
			int row = 6;
			int col = 1;
			
			// Place test Pawn, assume hasMoved = true
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);
			testPawn.setHasMoved(true);

			// Place enemy Pawn, (up one, right one)
			Pawn enemyPawn = Pawn(RC(row - 1, col + 1), 1);
			testBoard.insertPiece(&enemyPawn);

			// EXERCISE - Pawn::getPossibleMoves
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, Move());

			// VERIFY
			set<Move> expectedMoves = { 
				Move(RC(row, col), RC(row - 1, col)),					// Move forward
				Move(RC(row, col), enemyPawn.getCurrentPosition(), enemyPawn.getType()) };	// Capture enemy Pawn
			Assert::AreEqual(expectedMoves.size(), possibleMoves.size());
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
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
		 5 P * . . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(diagAttackLeft)
		{
			// SETUP - Place an enemy Pawn diagonally to the left of the testPawn
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0);

			// RC coordinates of the testPawn
			int row = 6;
			int col = 1;

			// Place test Pawn, assume hasMoved = true
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);
			testPawn.setHasMoved(true);

			// Place enemy Pawn (up one, left one)
			Pawn enemyPawn = Pawn(RC(row - 1, col - 1), 1);
			testBoard.insertPiece(&enemyPawn);

			// EXERCISE - Pawn::getPossibleMoves
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, Move());

			// VERIFY
			set<Move> expectedMoves = { 
				Move(RC(row, col), RC(row - 1, col)),					// Move forward
				Move(RC(row, col), enemyPawn.getCurrentPosition(), enemyPawn.getType()) };	// Capture enemy Pawn
			Assert::AreEqual(expectedMoves.size(), possibleMoves.size());
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);

			// TEARDOWN
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
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0);

			// RC coordinates of testPawn
			int row = 6;
			int col = 1;
			
			// Place test Pawn
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);

			Pawn enemyPawnOne = Pawn(RC(row - 1, col - 1), 1);
			testBoard.insertPiece(&enemyPawnOne);
			Pawn enemyPawnTwo = Pawn(RC(row - 1, col), 1);
			testBoard.insertPiece(&enemyPawnTwo);
			Pawn enemyPawnThree = Pawn(RC(row - 1, col + 1), 1);
			testBoard.insertPiece(&enemyPawnThree);

			// EXERCISE - Pawn::getPossibleMoves
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, Move());

			// VERIFY
			set<Move> expectedMoves = { 
				Move(RC(row, col), enemyPawnOne.getCurrentPosition(), enemyPawnOne.getType()),		// Attack left enemy Pawn
				Move(RC(row, col), enemyPawnThree.getCurrentPosition(), enemyPawnThree.getType()) };	// Attack right enemy Pawn

			Assert::AreEqual(expectedMoves.size(), possibleMoves.size());
			Assert::IsTrue(expectedMoves == possibleMoves);

			// TEARDOWN
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn choose to attack Pawns of the opposite color or move forward.
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 P * P . . . . . 5
		 6 . p . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		**********************************/
		TEST_METHOD(diagAttackForward)
		{
			// Setup - Put three enemy Pawns in front of the testPawn
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0);
			
			// RC coordinates of the testPawn
			int row = 6;
			int col = 1;
			
			// Place test Pawn, assume hasMoved = true
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);
			testPawn.setHasMoved(true);

			// Place enemy Pawn, (up one, left one)
			Pawn enemyPawnOne = Pawn(RC(row -1 , col - 1), 1);
			testBoard.insertPiece(&enemyPawnOne);

			// Place enemy Pawn (up one, right one)
			Pawn enemyPawnThree = Pawn(RC(row -1, col + 1), 1);
			testBoard.insertPiece(&enemyPawnThree);

			// EXERCISE - Pawn::getPossibleMoves			
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, Move());

			// VERIFY
			// Assert that the Pawn can attack move diagonally and attack Pawns of the opposite color, or can move forward (1 or 2)
			set<Move> expectedMoves = {
				Move(RC(row, col), enemyPawnOne.getCurrentPosition(), enemyPawnOne.getType()),		// Attack left enemy Pawn
				Move(RC(row, col), RC(row - 1, col)),						// Move forward one
				//Move(RC(row, col), RC(row - 2, col)),						// Move forward two, if hasMoved = false
				Move(RC(row, col), enemyPawnThree.getCurrentPosition(), enemyPawnThree.getType()) };	// Attack right enemy Pawn

			Assert::AreEqual(expectedMoves.size(), possibleMoves.size());
			Assert::IsTrue(expectedMoves == possibleMoves);

			// TEARDOWN
		}

		/*********************************
		* TEST getPossibleMoves
		* Test that the Pawn can perform an en-passant capture (right).
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . * * . . . . . 2
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
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0); // Pawn is on Black's side

			// RC coordinates of the testPawn
			int row = 3;
			int col = 1;

			// Place test Pawn, assumes hasMoved = true
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);
			testPawn.setHasMoved(true);

			// Enemy Pawn to the right
			Pawn enemyPawn = Pawn(RC(row, col + 1), 1);
			testBoard.insertPiece(&enemyPawn);

			// The last move was an enemy Pawn moving 2 spaces
			Move lastMove = Move(RC(row - 2, col + 1), enemyPawn.getCurrentPosition());

			// EXERCISE - Pawn::getPossibleMoves			
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, lastMove);

			// VERIFY
			// Assert that the Pawn can attack a Pawn in the same row BUT will move to the space behind it
			Move enPassant = Move(RC(row, col), RC(row - 1, col + 1), enemyPawn.getType());
			enPassant.setEnPassant();

			set<Move> expectedMoves = { 
				Move(RC(row, col), RC(row - 1, col)),		// Move forward one
				enPassant }; // En-passant

			Assert::AreEqual(expectedMoves.size(), possibleMoves.size());
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);


			// Don't include, tests Board instead of Pawn //

			// EXERCISE - Board.move(enPassant)
			// testBoard.move(enPassant);

			// VERIFY
			// Assert that the enemy Pawn was captured, and removed from the board
			//Assert::IsTrue(testBoard.getPieceAtPosition(RC(row, col + 1))->isSpace());

			// TEARDOWN
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
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0);

			// RC coordinates of the testPawn
			int row = 3;
			int col = 1;

			// Place test Pawn, assume hasMoved = true
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);
			testPawn.setHasMoved(true);

			// Place enemy Pawn to the left
			Pawn enemyPawn = Pawn(RC(row, col - 1), 1);
			testBoard.insertPiece(&enemyPawn);

			// The last move was an enemy Pawn moving 2 spaces
			Move lastMove = Move(RC(row - 2, col - 1), enemyPawn.getCurrentPosition());

			// EXERCISE - Pawn::getPossibleMoves			
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, lastMove);

			// VERIFY
			// Assert that the Pawn can attack a Pawn in the same row BUT will move to the space behind it
			Move enPassant = Move(RC(row, col), RC(row - 1, col - 1), enemyPawn.getType());
			enPassant.setEnPassant();

			set<Move> expectedMoves = { 
				Move(RC(row, col), RC(row - 1, col)),	// Move forward one
				enPassant };							// En-Passant

			Assert::AreEqual(expectedMoves.size(), possibleMoves.size());
			Assert::IsTrue(possibleMoves == expectedMoves);
			//Assert::AreEqual(expectedMoves, possibleMoves);
			

			// Don't include, tests Board instead of Pawn //

			// EXERCISE - Board.move(enPassant)
			//testBoard.move(enPassant);

			// VERIFY
			// Assert that the enemy Pawn was captured, and removed from the board
			//Assert::IsTrue(testBoard.getPieceAtPosition(RC(row, col - 1))->isSpace());

			// TEARDOWN
		}

		/*********************************
		* TEST move
		* Test that the Pawn will know to promote to Queen (after moving to last row 0 or 8).
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
			// SETUP
			Board testBoard = Board(EMPTY_BOARD);
			testBoard.setCurrentTeam(0);

			// RC coordinates of the testPawn
			int row = 1;
			int col = 1;

			// Place test Pawn
			Pawn testPawn = Pawn(RC(row, col), 0);
			testBoard.insertPiece(&testPawn);

			// Check that the Pawn was placed properly
			char pawnType = 'p';
			//Assert::AreEqual(pawnType, testBoard[row][col]->getType());

			// EXERCISE - Pawn::getPossibleMoves()
			set<Move> possibleMoves = testPawn.getPossibleMoves(&testBoard, Move());

			// VERIFY
			// Pawn can Move forward one and will be promoted to a Queen
			Move promotePawn = Move(RC(row, col), RC(row -1 , col));
			promotePawn.setPromotion();
			set<Move> expectedMoves = { promotePawn }; // Move forward and promote to Queen

			Assert::AreEqual(expectedMoves.size(), possibleMoves.size());
			Assert::IsTrue(possibleMoves == expectedMoves);


			// Don't include, tests Board instead of Pawn //
			
			// EXERCISE
			//testBoard.move(Move(RC(row, col), RC(row - 1, col)));

			// VERIFY
			// Assert that the Piece moved from its previous spot
			//string spaceType = "SPACE";
			//Assert::AreEqual(spaceType, testBoard.getPieceAtPosition(RC(row, col))->getType());
			
			// Assert that the Pawn was replaced with a Queen Piece - false, currently Space?
			//string queenType = "QUEEN";
			//Assert::AreEqual(queenType, testBoard.getPieceAtPosition(RC(row -1, col))->getType());

			// TEARDOWN
		};

	};
}