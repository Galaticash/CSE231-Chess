/***********************************************************************
 * Header File:
 *		Piece 
 * Authors: 
 *		Ashley DeMott, Logan Huston
 *    
 * Summary:
 *		The base class for all types of Pieces in a chess game.  
 ************************************************************************/

#pragma once
#include "Move.h"	// For the possible Moves of a given Piece
#include <set>		// Moves are stored in a set
#include "Rect.h"	// For the Rectangles used to draw the Piece
#include <vector>	// To hold the Rectangles

using namespace std;

#ifndef BOARD_CONST
#define BOARD_CONST
// The size of the board
const int NUM_ROW = 8;
const int NUM_COL = 8;

// TODO: const bool TEAM_ONE and TEAM_TWO from chess.cpp, error if put here
#endif
class Board;

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
	set <Move> virtual getPossibleMoves(Board* board) { return set <Move> {}; };

	// GETTERS AND SETTERS FOR ATTRIBUTES //

	void setPosition(RC positionTo)
	{
		// Update the Piece's position
		currentPosition = positionTo;

		// Update hasMoved
		if (!this->hasMoved)
		{
			this->hasMoved = true;
		}
	}
	RC getCurrentPosition() { return this->currentPosition; };	// Return the RC for this Piece
	
	vector<Rect>* getRectangles() { return &(this->rectangles); };	// Return a pointer to this Piece's rectangles

	void setHasMoved(bool moved) { this->hasMoved = moved; }; // For Testing, set hasMoved
	bool getHasMoved() { return this->hasMoved; };	// Return if this Piece has moved

	char getType() { return this->type; };	// Return the char type of this Piece
	bool isSpace() { return this->type == 's'; };	// Return if this Piece's char type is a Space
	
	bool getIsWhite() { return this->isWhite; };	// Return if this Piece is white (TODO: TEAM_ONE/TEAM_WHITE?)

protected:
	// Currently unused, Piece char types as an enum
	enum pieceTypes { k = 'k', q = 'q', r = 'r', n = 'n', p = 'p', b = 'b', s = 's' };

	char type = ' ';	// The type of this Piece
	vector <Rect> rectangles; // The rectangles used to draw this Piece
	
	RC currentPosition; 	// Current Row Column position on the Board

	bool hasMoved;	// If this Piece has moved yet
	bool isWhite;	// If this Piece is on Team White

	
	//set <Move> getSlidingMoves(Board* board);
};