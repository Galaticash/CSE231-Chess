/***********************************************************************
 * Header File:
 *		Move
 * Author: 
 *		Ashley DeMott
 *
 * Decription:
 *		A Move from one RC position to another RC position, 
 *		can be represented in Smith's notation (incomplete)
 ************************************************************************/

#pragma once
#include "RC.h"

using namespace std;

class Move {
public:
	Move()
	{
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
	// Pass captured piece to constructor - add to rest of code?
	Move(RC from, RC to, char capture) : Move(from, to)
	{
		this->setCapture(capture);
	};

	// Create a Move from a given smithNotation - for reading list of Moves
	/*Move(string smithNotation)
{
	this->smithNotation = smithNotation;
	translateFromSmith(smithNotation);
};*/

	// Translates the Move into Smith's notation
	// Note: Is this long enough for Move to require a .cpp?
	string translateToSmith()
	{
		string createdNotation = "";

		// Get the string version of the RC (using alphabet letters for column) (incomplete)
		string posFrom = this->positionFrom.getString();
		string posTo = this->positionTo.getString();

		// Add special cases to the end of the string
		string specialCases = "";

		// If a piece is captured by this move
		if(this->capture != ' ')
		{
			specialCases += capture;
		}

		// If there was a special type of move performed
		if (this->enpassant)
		{
			specialCases += "E";
		}
		else if (this->promotion)
		{
			// In a regular chess game, would have player decide what
			//  piece to promote to, but here will always assume Queen
			specialCases += "Q";
		}
		else if (this->castlingKSide)
		{
			specialCases += "c";
		}
		else if (this->castlingQSide)
		{
			specialCases += "C";
		}

		// Combine the From, To, and special case strings
		createdNotation += posFrom + posTo + specialCases;

		// Update this Move's Smith notation
		this->smithNotation = createdNotation;
		return createdNotation;
	};

	//// Given a move in Smith's notation, get the relevant attributes
	//void translateFromSmith(string smithNotation)
	//{
	//	// Insert code to translate smith notation into Move Attributes
	//  // Split smith's notation into variables
		// string from = smithNotation[0, 1]
		// string to = smithNotation[2, 3]
		// string specialCases = smithNotation[3, -1]
		
		// Translate into RCs and chars
		// this->positionFrom = RC(from[0], from[1])
		// this->positionTo = RC(to[0], to[1])
		
		// if specialCases length > 1
			// if specialCases[0] == a capture
				// this->capture = specialCases[0]
			// elif specialCases[0] == a special Case || (specialCases length == 2 && specialCases[1] == a special Case)
				// switch case for each special case (if, elif - only one special case possible)
	//};

	// - - - GETTERS AND SETTERS - - - //
	
	// Positions To and From (as RCs)
	RC getPositionFrom() { return this->positionFrom; };
	RC getPositionTo() { return this->positionTo; };
	
	// How far the Piece moved, currently used for En-Passant
	RC getDelta() { return RC(this->positionFrom.getRow() - this->positionTo.getRow(), this->positionFrom.getCol() - this->positionTo.getCol()); };
	
	// The string Smith notation of the move
	string getSmithNotation() { return this->translateToSmith(); };

	// Get/set special cases
	void setCapture(char pieceType)	{this->capture = pieceType; };
	char getCapture() { return this->capture; };

	void setCastlingQ() { this->castlingQSide = true; };
	void setCastlingK() { this->castlingKSide = true; };
	bool getCastlingQ() { return this->castlingQSide; };
	bool getCastlingK() { return this->castlingKSide; };

	void setEnPassant() { this->enpassant = true; this->capture = 'p'; };
	bool getEnPassant() { return this->enpassant; };

	void setPromotion() { this->promotion = true; };
	char getPromotion() { return this->promotion; };

	// - - -  OPERATORS - - - //

	// Not sure if this is the correct usage
	/*Move& operator= (const Move& m) { return *this; };*/
	void operator= (const Move& m) {
		// Information about Piece and how it moved
		this->positionTo = m.positionTo;
		this->positionFrom = m.positionFrom;

		// Special conditions
		this->capture = m.capture;

		this->enpassant = m.enpassant;
		this->castlingKSide = m.castlingKSide;
		this->castlingQSide = m.castlingQSide;
		this->promotion = m.promotion;
		
		// Retranslate into Smith's notation
		this->translateToSmith();
	};
	
	bool operator== (Move const& other) const { return (this->positionFrom == other.positionFrom && this->positionTo == other.positionTo); };
	//bool _equals(Move const& other) const { return (this->positionFrom == other.positionFrom && this->positionTo == other.positionTo); };
	bool operator!= (Move const& other) const { return !(*this == other); };

	// Updated to use Smith notation to compare moves
	bool operator< (Move const& other) const { return this->smithNotation < other.smithNotation; };
	//bool operator< (Move const& other) const { return (this->positionFrom < other.positionFrom || this->positionTo < other.positionTo); };
	inline friend ostream& operator<<(ostream& out, Move& m) {	return out << m.smithNotation; };

private:
	string smithNotation = "";	// The Smith's Notation of this Move
	RC positionFrom;	// Where the Move starts
	RC positionTo;		// Where the Move ends

	// Special Cases, default to false
	bool enpassant = false;
	bool castlingQSide = false;
	bool castlingKSide = false;

	bool promotion = false;
	char capture = ' ';
};