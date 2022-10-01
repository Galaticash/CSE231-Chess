/***********************************************************************
 * Header File:
 *    RC: Holds a row and a column.
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once

class RC
{
public:
	RC() 
	{
		row = -1;
		col = -1;
	};
	RC(int newRow, int newCol)
	{
		row = newRow;
		col = newCol;	
	};

	//RC& operator == (const RC& other);

	int getRow()
	{
		return this->row;
	};
	int getCol()
	{
		return this->col;
	};

	bool operator== (RC& other) { return (this->getRow() == other.getRow() && this->getCol() == other.getCol()); };


private:
	int row;
	int col;
};


/*bool RC& operator == (const RC& other)
{
	if (this.getRow() == other.getRow() and this.getCol() == other.getCol())
	{
		return true;
	}
	return false;
};*/