#pragma once

#include "Piece.h"

class Game
{
public:
	Game(Piece stargingBoard[][]) {
		board = startingBoard[][];

	};

	struct RC
	{
		int row;
		int col;
	};

	bool move(RC positionFrom, RC positionTo)
	{
		if (!(positionTo.row == positionFrom.row && positionTo.col == positionFrom.col))
		{
			return true;
		}

		return false;
	};


private:
	Piece board[][];
	// ogstream

	bool start() { return true; };

};