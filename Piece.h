/***********************************************************************
 * Header File:
 *		Piece 
 * Authors: 
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		The base class for all types of Pieces in a chess game.  
 ************************************************************************/

#pragma once
#include "Move.h"	// For the possible Moves of a given Piece
#include <set>		// Moves are stored in a set
#include "Rect.h"	// For the Rectangles used to draw the Piece
#include <vector>	// To hold the Rectangles
#include <cassert>	// To use asserts

using namespace std;

#ifndef GAME_CONST
	#define GAME_CONST
	// The size of the board
	const int NUM_ROW = 8;
	const int NUM_COL = 8;
#endif

// Forward Declaration for Board
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

	RC getCurrentPosition() const { return this->currentPosition; };	// Return the RC for this Piece
	
	vector<Rect>* getRectangles() { return &(this->rectangles); };		// Return a pointer to this Piece's rectangles

	void setHasMoved(bool moved) { this->hasMoved = moved; };	// For Testing, set hasMoved
	bool getHasMoved() const { return this->hasMoved; };			// Return if this Piece has moved

	bool getIsWhite() const { return this->isWhite; };		// Return if this Piece is white (TODO: TEAM_ONE/TEAM_WHITE?)
	char getType() const { return this->type; };				// Return the char type of this Piece
	bool isSpace() const { return this->type == 's'; };	// Return if this Piece's char type is a Space

protected:
	char type = ' ';				// The type of this Piece
	RC currentPosition; 			// Current Row Column position on the Board
	vector <Rect> rectangles;	// The rectangles used to draw this Piece

	bool hasMoved;		// If this Piece has moved yet
	bool isWhite;		// If this Piece is on Team White
	
	// Allows children Pieces to get their sliding or non-sliding Moves
	set <Move> getSlidingMoves(const Board* board, RC start, RC deltas[]);
	set <Move> getNonSlidingMoves(const Board* board, RC start, RC deltas[]);
};

// Leave this down here to let the program work.
#include "board.h"		// Inlcude the Board class

