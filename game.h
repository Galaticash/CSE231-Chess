/***********************************************************************
 * Header File:
 *    Game:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once

#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Pawn.h"
#include "Space.h"

#include <string>

const int NUM_ROW = 8;
const int NUM_COL = 8;

Piece* DEFAULT_BOARD[NUM_ROW][NUM_COL] = {
			{&Rook(RC(0, 0), 0), &Bishop(RC(0, 1), 0), &Knight(RC(0, 2), 0), &Queen(RC(0, 3), 0), &King(RC(0, 4), 0), &Knight(RC(0, 5), 0), &Bishop(RC(0, 6), 0), &Rook(RC(0, 7), 0)},
			{&Pawn(RC(1, 0), 0), &Pawn(RC(1, 1), 0), &Pawn(RC(1, 2), 0), &Pawn(RC(1, 3), 0), &Pawn(RC(1, 4), 0), &Pawn(RC(1, 5), 0), &Pawn(RC(1, 6), 0), &Pawn(RC(1, 7), 0)},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Pawn(RC(6, 0), 1), &Pawn(RC(6, 1), 1), &Pawn(RC(6, 2), 1), &Pawn(RC(6, 3), 1), &Pawn(RC(6, 4), 1), &Pawn(RC(6, 5), 1), &Pawn(RC(6, 6), 1), &Pawn(RC(6, 7), 1)},
			{&Rook(RC(7, 0), 1), &Bishop(RC(7, 1), 1), &Knight(RC(7, 2), 1), &Queen(RC(7, 3), 1), &King(RC(7, 4), 1), &Knight(RC(7, 5), 1), &Bishop(RC(7, 6), 1), &Rook(RC(7, 7), 1)} };

/*   board[2][3]
			a b c d e f g h
	      0 1 2 3 4 5 6 7 
       0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . p . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
		   0 1 2 3 4 5 6 7
			a b c d e f g h
*/

class Game
{
public:
	Game()
	{
		currentIsWhite = true;
		for (int r = 0; r < NUM_ROW; r++)
		{
			for (int c = 0; c < NUM_COL; c++)
			{
				this->board[r][c] = DEFAULT_BOARD[r][c];
			}
		}
	};

	void createBoard(string filename = "")
	{
		// setup the default board
		int i = 0;
		for(int row = 0; row++; row >= NUM_ROW)
			//int row in this->board)
		{
			for (int col = 0; col++; col >= NUM_COL)
			{
				i++;
				//board[row][col] = DEFAULT_BOARD[row][col];
 			}
		}

		// for each move in file
		// translate it from the string --> Moves
		// do the move
	}

	void play() {
		while (true)
		{
			
		
		}
	};

	// 
	// lastMove = chessGame.move(nextMove)
	Move move(Move nextMove)
	{
		if (false)
		{
			return nextMove;
		}

		// If nextMove.getTo == nextMove.getFrom()
		// No Move happened
		return this->lastMove;
	};


private:
	Piece* board[NUM_ROW][NUM_COL];
	Move lastMove;
	bool currentIsWhite;
	// ogstream

	bool start() { return true; };

};