/***********************************************************************
 * Header File:
 *    Game:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once

#include "Piece.h"

int NUM_ROW = 8;
int NUM_COL = 8;
/*Piece DEFAULT_BOARD[8][8] =
{
			{Rook(), ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}*/
class Game
{
public:
	Game() {
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

		// for move in file
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