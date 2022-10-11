/***********************************************************************
 * Header File:
 *    Board:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/
#pragma once


/*
Piece* DEFAULT_BOARD[NUM_ROW][NUM_COL] = {
			{&Rook(RC(0, 0), 0), &Bishop(RC(0, 1), 0), &Knight(RC(0, 2), 0), &Queen(RC(0, 3), 0), &King(RC(0, 4), 0), &Knight(RC(0, 5), 0), &Bishop(RC(0, 6), 0), &Rook(RC(0, 7), 0)},
			{&Pawn(RC(1, 0), 0), &Pawn(RC(1, 1), 0), &Pawn(RC(1, 2), 0), &Pawn(RC(1, 3), 0), &Pawn(RC(1, 4), 0), &Pawn(RC(1, 5), 0), &Pawn(RC(1, 6), 0), &Pawn(RC(1, 7), 0)},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Pawn(RC(6, 0), 1), &Pawn(RC(6, 1), 1), &Pawn(RC(6, 2), 1), &Pawn(RC(6, 3), 1), &Pawn(RC(6, 4), 1), &Pawn(RC(6, 5), 1), &Pawn(RC(6, 6), 1), &Pawn(RC(6, 7), 1)},
			{&Rook(RC(7, 0), 1), &Bishop(RC(7, 1), 1), &Knight(RC(7, 2), 1), &Queen(RC(7, 3), 1), &King(RC(7, 4), 1), &Knight(RC(7, 5), 1), &Bishop(RC(7, 6), 1), &Rook(RC(7, 7), 1)} };
*/

//#include "Piece.h"
#include "Queen.h"
#include "Space.h"

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
	Piece* getPieceAtPosition(RC position)
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

	Piece** operator[] (int row) { return piecesBoard[row]; };

private:
	Piece* piecesBoard[NUM_ROW][NUM_COL] = {};
	Move lastMove;
};