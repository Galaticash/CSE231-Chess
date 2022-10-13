/***********************************************************************
 * Header File:
 *    Board: Represents the board in chess
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *
 ************************************************************************/
#pragma once

#ifndef PIECE_CLASSES
#define PIECE_CLASSES
#include "Space.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#endif

class Board
{
public:
	// When a board is created, will use the Default 2D array of Piece*
	Board() { this->lastMove = Move(); };
	// Use a custom board, for testing
	Board(Piece* copiedBoard[NUM_ROW][NUM_COL])	{ 
		copyBoard(copiedBoard);
		this->lastMove = Move();
	};
	//~Board() { delete[] & this->piecesBoard; delete& this->lastMove;  delete this; };

	// Get a pointer to the Piece at the given position on the Board
	// Also override []
	Piece* getPieceAtPosition(RC position)
	{
		return piecesBoard[position.getRow()][position.getCol()];
	}
	Move getLastMove() { return this->lastMove; };

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
	// const Piece operator =

	Piece** operator[] (int row) { return (piecesBoard[row]); }; // TODO: update to match const version, 
	Piece* operator[] (const int row) const { return *(piecesBoard[row]); };

private:
	Piece* piecesBoard[NUM_ROW][NUM_COL] = {}; // The 2D array of chess piece pointers
	Move lastMove;
};