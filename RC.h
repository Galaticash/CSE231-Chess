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
	bool operator== (RC const & other) const { return (this->row == other.row && this->col == other.col); };
	//bool _equals(RC const& other) const { return (this->row == other.row && this->col == other.col); };
	bool operator< (RC const& other) const { return (this->row < other.row || this->col < other.col); };


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