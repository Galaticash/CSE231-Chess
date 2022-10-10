/***********************************************************************
 * Header File:
 *    Piece: 
 * Author: Ashley DeMott, Logan Huston
 *    
 * Summary:	
 *    
 ************************************************************************/

#pragma once
#include "Move.h"	// For the possible Moves of a given Piece
#include <set>		// Moves are stored in a set

using namespace std;

// The size of the board
#ifndef BOARD_CONST
#define BOARD_CONST
const int NUM_ROW = 8;
const int NUM_COL = 8;
#endif

class Piece {
public:
	Piece() {
		// If no parameters are given with the constructor
		this->currentPosition = RC();
		this->isWhite = false;
		this->hasMoved = false;
	};
	Piece(RC position, bool isWhite)
	{
		// Use the given parameters to create the Piece
		this->currentPosition = position;
		this->isWhite = isWhite;
		this->hasMoved = false;
	};

	// Returns the possible moves this Piece can do, given the current Board and the previous Move
	set <Move> virtual getPossibleMoves(Piece* board[][8][8], Move lastMove) { return set <Move> {}; };
	//set <Move> virtual getPossibleMoves(Piece* board[], Move lastMove) = 0; <- pure virutal, cannot make Piece* 2D array

	// GETTERS AND SETTERS FOR ATTRIBUTES //

	void setPosition(RC positionTo)
	{
		// Assert that the given position is on the board
		// assert()
		
		// Update the Piece's position
		currentPosition = positionTo;

		// Update hasMoved --> Or change to use nMoves, nMoves++
		if (!this->hasMoved)
		{
			this->hasMoved = true;
		}
	}	
	RC getCurrentPosition() { return this->currentPosition; };
	
	void setHasMoved(bool moved) { this->hasMoved = moved; }; // For Testing
	bool getHasMoved() { return this->hasMoved; };	

	// ERROR CATCHING: Fix type to be SPACE if not defined (somehow) <- fixed?
	char getType() { if (this->type == ' ') { this->type = 's'; } return this->type; };
	bool isSpace() { return this->type == 's'; };
	bool getIsWhite() { return this->isWhite; };

	// To tell if a Piece is the same as another Piece (currently unused)
	
	//Piece& operator= (Piece& other) { return *this; };
	//bool operator== (Piece& other) { return (this->getType() == other.getType() && this->currentPosition.getRow() == other.getCurrentPosition().getRow() && this->currentPosition.getCol() == other.getCurrentPosition().getCol()); };
	//bool operator!= (Piece& other) { return !(this == other); };

private:
protected:
	// Type of Piece (PAWN, KNIGHT, KING, ect)
	char type = ' '; // ERROR: Some Pieces/Spaces exist with empty string?

	// Current RC on the Board
	RC currentPosition;

	bool hasMoved;
	bool isWhite;


	/// <summary>
	/// Determines if the given RC is a valid position on the Board
	/// TODO: Move this functionality to Board, since Board should know the size of itself, not each Piece
	/// </summary>
	/// <param name="position">The Row and Column position</param>
	/// <returns>If the given RC is a valid position on the Board</returns>
	bool isValidPosition(RC position)
	{
		int row = position.getRow();
		int col = position.getCol();

		// If the RC is on the board (row: 0 - 7, col: 0 - 7)
		return (row >= 0 && row < NUM_ROW && col >= 0 && col < NUM_COL);
	};  
};