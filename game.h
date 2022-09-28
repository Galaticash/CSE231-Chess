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
Piece DEFAULT_BOARD[8][8] = {
			{Rook(RC(0, 0), 1), Bishop(RC(0, 0), 1), Knight(RC(0, 0), 1), Queen(RC(0, 0), 1), King(RC(0, 0), 1), Knight(RC(0, 0), 1), Bishop(RC(0, 0), 1), Rook(RC(0, 0), 1)},
			{Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(), 1), Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(), 1), Pawn(RC(), 1)},
			{Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0))},
			{Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0))},
			{Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0))},
			{Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0)), Space(RC(0, 0))},
			{Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(0, 0), 1), Pawn(RC(), 1)},
			{Rook(RC(0, 0), 1), Bishop(RC(0, 0), 1), Knight(RC(0, 0), 1), Queen(RC(0, 0), 1), King(RC(0, 0), 1), Knight(RC(0, 0), 1), Bishop(RC(0, 0), 1), Rook(RC(0, 0), 1)} };

/*   board[2][3]
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
*/

class Game
{
public:
	Game()
	{
		currentIsWhite = true;
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
	Piece board[NUM_ROW][NUM_COL];
	Move lastMove;
	bool currentIsWhite;
	// ogstream

	bool start() { return true; };

};