/***********************************************************************
 * Header File:
 *    Board:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/
#pragma once

#ifndef PIECE_CLASSES
#define PIECE_CLASSES
#include "Pawn.h"
#include "Queen.h"
#include "Space.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#endif

class Board
{
public:
	// When a board is created, will use the Default 2D array of Piece*
	Board() { this->lastMove = Move(); };
	// Use a custom board, for testing
	Board(Piece* copiedBoard[NUM_ROW][NUM_COL]) : Board()
	{ copyBoard(copiedBoard); };
	//~Board() { delete[] & this->piecesBoard; delete& this->lastMove;  delete this; };

	// Get a pointer to the Piece at the given position on the Board
	// Also override []
	Piece* getPieceAtPosition(RC position) const
	{
		return piecesBoard[position.getRow()][position.getCol()];
	}

	void copyBoard(Piece* copiedBoard[NUM_ROW][NUM_COL])
	{
		for (int r = 0; r < NUM_ROW; r++)
		{
			for (int c = 0; c < NUM_COL; c++)
			{
				this->piecesBoard[r][c] = copiedBoard[r][c];
			}
		}
	};

	// Put a Piece onto the Board, replacing any Piece currently there
	void insertPiece(Piece* insertPiece);

	Move getLastMove() { return this->lastMove; };

	// Perform a give Move
	Move move(Move currentMove);

	/// <summary>
	/// Determines if the given RC is a valid position on the Board
	/// </summary>
	/// <param name="position">The Row and Column position</param>
	/// <returns>If the given RC is a valid position on the Board</returns>
	bool isValidPosition(RC position)
	{
		int row = position.getRow();
		int col = position.getCol();

		// If the RC is on the board (row: 0 - 7, col: 0 - 7)
		return (row >= 0 && row < NUM_ROW&& col >= 0 && col < NUM_COL);
	};

	Piece* operator[](const int row) const { return *(piecesBoard[row]); };

private:
	Piece* piecesBoard[NUM_ROW][NUM_COL] = {};
	Move lastMove;
};