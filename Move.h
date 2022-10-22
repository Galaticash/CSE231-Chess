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
	Move(string smithNotation)
	{
		this->smithNotation = smithNotation;
		translateFromSmith(smithNotation);
	};

	// Translates the Move into Smith's notation
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
		else if (this->promotion != ' ')
		{
			// In a regular chess game, would have player decide what
			//  piece to promote to, but here will always assume Queen
			specialCases += this->promotion;
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

	// Given a move in Smith's notation, get the relevant attributes
	void translateFromSmith(string smithNotation)
	{
		// Split smith's notation into variables
		this->smithNotation = smithNotation;
		
		// If there are at least 4 characters in the string,
		if (smithNotation.length() >= 4)
		{
			// Go through each character in the smithNotation string
			string::const_iterator it = smithNotation.cbegin();

			// get the source (positionFrom)
			int col = *it - 'a';
			it++;
			int row = *it - '1';
			it++;
			positionFrom = RC(row, col);

			// get the destination (positionTo)
			col = *it - 'a';
			it++;
			row = *it - '1';
			it++;
			positionTo = RC(row, col);

			// capture and promotion information
			for (; it != smithNotation.end(); ++it)
			{
				switch (*it)
				{
				case 'p':   // capture a pawn
				case 'n':   // capture a knight
				case 'b':   // capture a bishop
				case 'r':   // capture a rook
				case 'q':   // capture a queen
				case 'k':   // !! you can't capture a king you silly!
					this->capture = tolower(*it);
					break;

				case 'c':  // short castling or king's castle
					this->castlingKSide = true;
					break;
				case 'C':  // long castling or queen's castle
					this->castlingQSide = true;
					break;
				case 'E':  // En-passant
					this->enpassant = true;
					break;

				case 'N':  // Promote to knight
				case 'B':  // Promote to Bishop
				case 'R':  // Promote to Rook
				case 'Q':  // Promote to Queen
					this->promotion = *it;
					break;
				}
			}				
		}
		else
		{
			throw "Invalid Move: Smith's Notation too short";
		}
		
	};

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

	void setPromotion(char promote) { this->promotion = promote; };
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
	bool operator!= (Move const& other) const { return !(*this == other); };

	// Updated to use Smith notation to compare moves
	bool operator< (Move const& other) { return this->smithNotation < other.smithNotation; };
	bool operator< (Move const& other) const { return this->smithNotation < other.smithNotation; };
	inline friend ostream& operator<<(ostream& out, Move& m) {	return out << m.smithNotation; };

private:
	string smithNotation = "";	// The Smith's Notation of this Move
	RC positionFrom;				// Where the Move starts
	RC positionTo;					// Where the Move ends

	// Special Cases, default to false
	bool enpassant = false;
	bool castlingQSide = false;
	bool castlingKSide = false;

	char promotion = ' ';
	char capture = ' ';
};