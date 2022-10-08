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
		translateToSmith();
	};
	Move(RC from, RC to)
	{
		this->positionFrom = from;
		this->positionTo = to;
		translateToSmith();
	};

	// TODO: Fix to consistently use a pointer to a Piece or a string type
	// OR rely on board to get pieceType (board[RC from].getType() or .isSpace())
	Move(string movedPiece, RC from, RC to)
	{
		this->pieceType = movedPiece;
		this->positionFrom = from;
		this->positionTo = to;
		translateToSmith();
	};

	/*Move(string smithNotation)
{
	this->smithNotation = smithNotation;
	translateFromSmith(smithNotation);
};*/

	// Translate the Move into Smith's notation
	string translateToSmith()
	{
		string createdNotation = "";
		string posFrom = this->positionFrom.getString(); // TODO: Translate into an alphabet letter (0 - A, 1 - B, ...)
		string posTo = this->positionTo.getString();

		// If there was a capture/special type of move, [TODO]
		

		createdNotation += posFrom + posTo;
		this->smithNotation = createdNotation;
		return createdNotation;
	};

	//// Given a move in Smith's notation, get the relevant attributes
	//void translateFromSmith(string smithNotation)
	//{
	//	// Insert code to translate smith notation into Move Attributes

	//};


	// Get all the attributes of Piece
	//Piece getPiece() { return this->movingPiece; };
	RC getPositionFrom() { return this->positionFrom; };
	RC getPositionTo() { return this->positionTo; };
	string getPieceType() { return this->pieceType; };
	RC getDelta() { return RC(this->positionFrom.getRow() - this->positionTo.getRow(), this->positionFrom.getCol() - this->positionTo.getCol()); };
	string getSmithNotation() { return this->translateToSmith(); };

	void setCapture(char piece) { this->capture = piece; };
	void setIsCastlingQ() { this->castlingQSide = true; };
	void setIsCastlingK() { this->castlingQSide = true; };
	void setIsEnPassant() { this->enpassant = true; };
	void setIsPromotion() { this->promotion = true; };


	/*Move& operator= (const Move& m) { return *this; };*/
	void operator= (const Move& m) {
		this->pieceType = m.pieceType;
		this->positionTo = m.positionTo;
		this->positionFrom = m.positionFrom;		
		this->enpassant = m.enpassant;
		this->castlingKSide = m.castlingKSide;
		this->castlingQSide = m.castlingQSide;
		this->promotion = m.promotion;
		this->capture = m.capture;

		this->translateToSmith();
	};
	
	bool operator== (Move const& other) const { return (this->positionFrom == other.positionFrom && this->positionTo == other.positionTo); };
	//bool _equals(Move const& other) const { return (this->positionFrom == other.positionFrom && this->positionTo == other.positionTo); };

	bool operator< (Move const& other) const { return this->smithNotation < other.smithNotation; };
	//bool operator< (Move const& other) const { return (this->positionFrom < other.positionFrom || this->positionTo < other.positionTo); };

	/*friend std::ostream& operator<<(std::ostream& os, const Move& m)
	{
		os << m.smithNotation;	
	};*/

private:
	string pieceType = "SPACE";
	string smithNotation = "";
	RC positionTo;
	RC positionFrom;

	bool enpassant = false;
	bool castlingQSide = false;
	bool castlingKSide = false;

	bool promotion = false;
	char capture = ' ';
};