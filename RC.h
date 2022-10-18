/***********************************************************************
 * Header File:
 *		RC
 * Author
 *		Ashley DeMott
 * Description:
 *		RC or RowColumn, holds two integer values representing 
 *		a Row/Column combination on the Chess Board.
 ************************************************************************/

#pragma once
#include <string>
#include <iostream>

using namespace std;

class RC
{
public:
	// Constructors
	RC()
	{
		// If no row/col is given, invalid board positions are set
		this->row = -1;
		this->col = -1;
	}
	// Create a RC with a given row, col
	RC(int newRow, int newCol)
	{
		this->row = newRow;
		this->col = newCol;
	};

	// Get the row or column of the RC
	int getRow() { return this->row; };
	int getCol() { return this->col; };

	// Gets RC where the row is represented as a letter, ex: a1, b3
	string getString()
	{
		string rcString = "";

		// Convert the row to an alpha character
		char row = (char)('a' - 1 + this->getRow());
		
		// Combine together and return
		rcString += row + to_string(this->getCol() + 1);
		return rcString;
	};

	// Assignment operator
	void operator= (const RC& rc)
	{
		this->row = rc.row;
		this->col = rc.col;
	};

	// Comparison operators
	bool operator== (RC const& other) const { return (this->row == other.row && this->col == other.col); };
	bool operator!= (RC const& other) const { return !(*this == other); };
	bool operator< (RC const& other) const { return (this->row < other.row || this->col < other.col); };

private:
	int row;
	int col;
};

