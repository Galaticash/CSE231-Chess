/***********************************************************************
 * Header File:
 *    Piece: A piece in chess
 * Author: 
 *		Ashley DeMott, Logan Huston
 * Summary:	
 *    
 ************************************************************************/

#pragma once
#include "Move.h"	// For the possible Moves of a given Piece
#include <set>		// Moves are stored in a set
#include <vector>

using namespace std;

// The size of the board
#ifndef BOARD_CONST
#define BOARD_CONST
const int NUM_ROW = 8;
const int NUM_COL = 8;
#endif
class Board;

class Piece {
public:
	Piece() {
		// If no parameters are given with the constructor
		this->currentPosition = RC();
		this->isWhite = false;
		this->hasMoved = false;
		this->rectangles = {};
	};
	Piece(RC position, bool isWhite)
	{
		// Use the given parameters to create the Piece
		this->currentPosition = position;
		this->isWhite = isWhite;
		this->hasMoved = false;
		this->rectangles = {};
	};

	// Public, used by ogstream
	struct Rect
	{
		int x0;
		int y0;
		int x1;
		int y1;
		int x2;
		int y2;
		int x3;
		int y3;
	};
	// GETTERS AND SETTERS FOR ATTRIBUTES //

	// Returns the possible moves this Piece can do, given the current Board and the previous Move
	set <Move> virtual getPossibleMoves(Board* board, Move lastMove) { return set <Move> {}; };
	//set <Move> virtual getPossibleMoves(Piece* board[], Move lastMove) = 0; <- pure virutal, cannot make Piece* 2D array

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

	char getType() { return this->type; };
	bool isSpace() { return this->type == 's'; };
	bool getIsWhite() { return this->isWhite; };
	vector <Rect> getRectangles() { return this->rectangles; };

	// To tell if a Piece is the same as another Piece (currently unused)
	
	//Piece& operator= (Piece& other) { return *this; };
	//bool operator== (Piece& other) { return (this->getType() == other.getType() && this->currentPosition.getRow() == other.getCurrentPosition().getRow() && this->currentPosition.getCol() == other.getCurrentPosition().getCol()); };
	//bool operator!= (Piece& other) { return !(this == other); };

protected:
	enum pieceType { k = 'k', q = 'q', r = 'r', n = 'n', p = 'p', b = 'b', s = 's' };

	// Type of Piece (PAWN, KNIGHT, KING, ect)
	char type = ' ';
	//pieceType type = s;

	// Current RC on the Board
	RC currentPosition;

	bool hasMoved;
	bool isWhite;

	vector<Rect> rectangles;
};