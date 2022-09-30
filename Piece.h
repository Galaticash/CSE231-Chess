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
	set <Move> virtual getPossibleMoves(Piece* board[], Move lastMove) {} ;
	//set <Move> virtual getPossibleMoves(Piece* board[], Move lastMove) = 0;
	RC getCurrentPosition() { return this->currentPosition; };
	bool getHasMoved() { return this->hasMoved; };
	bool getIsWhite() { return this->isWhite; };
	string getType() { return type; };
	bool isSpace() { return type == "SPACE"; };

	// To tell if a Piece is the same as another Piece
	//bool operator== (Piece& other) { return (this->getType() == other.getType() && this->currentPosition.getRow() == other.getCurrentPosition().getRow() && this->currentPosition.getCol() == other.getCurrentPosition().getCol()); };
	//bool operator!= (Piece& other) { return !(this == other); };

protected:
	// Type of Piece (PAWN, KNIGHT, KING, ect)
	string type = "";

	// Current RC on the Board
	RC currentPosition;

	bool hasMoved;
	bool isWhite;

	bool isValidPosition(RC position)
	{
		int row = position.getRow();
		int col = position.getCol();

		// If the RC is on the board (row: 0 - 7, col: 0 - 7)
		return (row >= 0 && row <= 7 && col >= 0 && col >= 7);
	};  
};