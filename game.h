/***********************************************************************
 * Header File:
 *    Game:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once

#include "Piece.h"

/*
   board [2][3]
	      0 1 2 3 4 5 6 7 
       0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . p . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
		   0 1 2 3 4 5 6 7
*/

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