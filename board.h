/***********************************************************************
 * Header File:
 *      Board
 * Author:
 *      Ashley DeMott
 * Summary:
 *      Stores a collection of Piece pointers and moves Pieces to
 *      new positions on the Board. Also keeps track of the state of
 *      the Chess game (lastMove and currentTeam)
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
	// Sets the last Move to an empty Move, and the first team as white
	Board() { this->lastMove = Move(); this->currentTeam = 1; };
	
	// Copy from a custom board
	Board(Piece* copiedBoard[NUM_ROW][NUM_COL]) : Board() { copyBoard(copiedBoard); };
	
	// Copies a given 2D array of Piece pointers
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
	
	// Get a pointer to the Piece at the given position on the Board
	// In place of [] override
	Piece* getPieceAtPosition(RC position) const { return piecesBoard[position.getRow()][position.getCol()]; }

	// Get the last Move of the game
	Move getLastMove() const { return this->lastMove; };

	// Perform a given Move
	Move move(Move currentMove);

	//void setCurrentTeam(bool white) { this->currentTeam = white; };		// For testing: set the current team
	bool getCurrentTeam() const { return this->currentTeam; };				// Return if it is White's turn

	// Checks if a given RC position is on the Board
	bool isValidPosition(RC position) const
	{
		int row = position.getRow();
		int col = position.getCol();

		// If the RC is on the board (row: 0 - 7, col: 0 - 7)
		return (row >= 0 && row < NUM_ROW && col >= 0 && col < NUM_COL);
	};

	// Return a pointer to the given row of Piece*
	Piece** operator[](const int row) { return piecesBoard[row]; };
	//Piece** operator[](const int row) const { return piecesBoard[row]; };	// Currenlty iffy

private:
	Piece* piecesBoard[NUM_ROW][NUM_COL] = {};	// The 2D array of Piece pointers
	Move lastMove;			// The last performed Move
	bool currentTeam;		// The current Team
};

