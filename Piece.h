/***********************************************************************
 * Header File:
 *    Piece: 
 * Author:
 *    
 * Summary:
 *    
 ************************************************************************/

#pragma once
#include "Move.h"
#include <set>            // for STD::SET

using namespace std;

class Piece {
public:
	Piece() {
		// If no parameters are given with the constructor
		this->currentPosition = RC(-1, -1);
		this->isWhite = false;
		this->hasMoved = false;
	};
	Piece(RC position, bool isWhite)
	{
		// Use the given parameters to create the Piece
		this->isWhite = isWhite;
		this->currentPosition = position;
		this->hasMoved = false;
	};
	set <Move> virtual getPossibleMoves(Piece** board, Move lastMove) { return set <Move> {}; };
	//set <Move> virtual getPossibleMoves(Piece* board[], Move lastMove) = 0; <- pure virutal, cannot make Piece* 2S array
	
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
	bool getHasMoved() { return this->hasMoved; };
	bool getIsWhite() { return this->isWhite; };
	// ERROR CATCHING: Fix type to be SPACE if not defined (somehow)
	string getType() { if (this->type == "" || this->type == "INVALID") { this->type = "SPACE"; } return this->type; };
	bool isSpace() { return this->type == "SPACE"; };

	// To tell if a Piece is the same as another Piece
	
	//Piece& operator= (Piece& other) { return *this; };
	//bool operator== (Piece& other) { return (this->getType() == other.getType() && this->currentPosition.getRow() == other.getCurrentPosition().getRow() && this->currentPosition.getCol() == other.getCurrentPosition().getCol()); };
	//bool operator!= (Piece& other) { return !(this == other); };

protected:
	// Type of Piece (PAWN, KNIGHT, KING, ect)
	string type = "INVALID"; // ERROR: Some Pieces/Spaces exist with empty string?

	// Current RC on the Board
	RC currentPosition;

	bool hasMoved;
	bool isWhite;

	bool isValidPosition(RC position)
	{
		int row = position.getRow();
		int col = position.getCol();

		// If the RC is on the board (row: 0 - 7, col: 0 - 7)
		return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
	};  
};