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
	RC(int newRow, int newCol)
	{
		this->row = newRow;
		this->col = newCol;
	};

	int getRow()
	{
		return this->row;
	};
	int getCol()
	{
		return this->col;
	};

	// Gets RC where the row is represented as a letter, ex: A1, B3
	string getString()
	{
		string row = to_string(this->getRow());
		//static_cast<char>('a' - 1 + this->getRow());
		string col = to_string(this->getCol());
		//col = atoi(col.substr(0));
		//col = static_cast<char>(this->getCol());
		string rcString = "" + row + col;
		return rcString;
	};

	/*RC& operator= (const RC& rc)
	{
		//this->row = rc.row;
		//this->col = rc.col;
		return *this;
	};*/
	void operator= (const RC& rc)
	{
		this->row = rc.row;
		this->col = rc.col;
	};
	bool operator== (RC const& other) const { return (this->row == other.row && this->col == other.col); };
	bool operator!= (RC const& other) const { return !(*this == other); };
	
	//bool _equals(RC const& other) const { return (this->row == other.row && this->col == other.col); };
	bool operator< (RC const& other) const { return (this->row < other.row || this->col < other.col); };

private:
	int row;
	int col;
};

