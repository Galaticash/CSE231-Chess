
class RC
{
public:
	RC(int newRow, int newCol)
	{
		row = newRow;
		col = newCol;	
	};

	RC& operator == (const RC& other);

	int getRow()
	{
		return this->row;
	};
	int getCol()
	{
		return this->col;
	};

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