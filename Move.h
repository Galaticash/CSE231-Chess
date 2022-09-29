/***********************************************************************
 * Header File:
 *    Move: 
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "RC.h"

class Move {
public:
	Move(){};
	Move(Piece* mover, RC from, RC to) 
	{
		this->movingPiece = mover;
		this->positionFrom = from;
		this->positionTo = to;
	};
	Move(string smithNotation)
	{
		translateFromSmith(smithNotation);
	};
	Piece* getPiece() { return this->movingPiece; };
	RC getPositionFrom() { return this->positionFrom; };




	// Translate the Move into Smith's notation
	string translateToSmith()
	{
		string smithNotation = "";
		string posFrom = "" + static_cast<char>('a' - 1 + this->positionFrom.getRow()) + this->positionFrom.getCol();
		string posTo = "" + static_cast<char>('a' - 1 + this->positionTo.getRow()) + this->positionTo.getCol();

		// If there was a capture/special type of move

		smithNotation += posFrom + posTo;
		return smithNotation;
	};
	// Given a move in Smith's notation, get the relevant attributes
	void translateFromSmith(string smithNotation)
	{

	};


private:
	Piece* movingPiece;
	RC positionTo;
	RC positionFrom;

};