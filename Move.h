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

using namespace std;

class Move {
public:
	Move()
	{
		//this->movingPiece = Space();
		this->positionFrom = RC(-1, -1);
		this->positionTo = RC(-1, -1);
	};
	/*Move(string smithNotation)
{
	this->smithNotation = smithNotation;
	translateFromSmith(smithNotation);
};*/
	Move(RC from, RC to)
	{
		this->positionFrom = from;
		this->positionTo = to;
	};

	// TODO: Fix to consistently use a pointer to a Piece or a string type
	// OR rely on board to get pieceType (board[RC from].getType() or .isSpace())
	Move(string movedPiece, RC from, RC to)
	{
		this->pieceType = movedPiece;
		this->positionFrom = from;
		this->positionTo = to;
	};
	/*
	Move(Piece* mover, RC from, RC to)
	{
		this->movingPiece = *mover;
		this->positionFrom = from;
		this->positionTo = to;
		//this->smithNotation = translateToSmith();

	};*/

	// Get all the attributes of Piece
	//Piece getPiece() { return this->movingPiece; };
	RC getPositionFrom() { return this->positionFrom; };
	RC getPositionTo() { return this->positionTo; };
	//RC getDelta() { return RC(this->positionFrom.getRow() - this->positionTo.getRow(), this-> };

	void setCapture(char piece) { this->capture = piece; };
	void setIsCastlingQ() { this->castlingQSide = true; };
	void setIsCastlingK() { this->castlingQSide = true; };
	void setIsEnPassant() { this->enpassant = true; };
	void setIsPromotion() { this->promotion = true; };

	// Translate the Move into Smith's notation
	//string translateToSmith()
	//{
	//	string smithNotation = "";
	//	string posFrom = "" + static_cast<char>('a' - 1 + this->positionFrom.getRow()) + this->positionFrom.getCol();
	//	string posTo = "" + static_cast<char>('a' - 1 + this->positionTo.getRow()) + this->positionTo.getCol();

	//	// If there was a capture/special type of move

	//	smithNotation += posFrom + posTo;
	//	return smithNotation;
	//};
	//// Given a move in Smith's notation, get the relevant attributes
	//void translateFromSmith(string smithNotation)
	//{
	//	// Insert code to translate smith notation into Move Attributes

	//};

	//bool operator== (Move& other) { return (this->getPositionFrom() == other.getPositionFrom() && this->getPositionTo() == other.getPositionTo()); };
	bool operator== (Move const& other) const { return (this->positionFrom == other.positionFrom && this->positionTo == other.positionTo); };
	bool _equals(Move const& other) const { return (this->positionFrom == other.positionFrom && this->positionTo == other.positionTo); };
	bool operator< (Move const& other) const { return (this->positionFrom < other.positionFrom && this->positionTo < other.positionTo); };


private:
	//Piece* movingPiece;
	string pieceType;
	RC positionTo;
	RC positionFrom;
	//string smithNotation;

	bool enpassant = false;
	bool castlingQSide = false;
	bool castlingKSide = false;

	bool promotion = false;
	char capture = ' ';
};