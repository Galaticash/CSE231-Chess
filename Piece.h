/***********************************************************************
 * Header File:
 *    Piece: 
 * Author:
 *    
 * Summary:
 *    
 ************************************************************************/

#pragma once
#include "Move.h"
#include <set>            // for STD::SET

using namespace std;

class Piece {
public:
	Piece() {
		this->currentPosition = RC(-1, -1);
		this->isWhite = false;
		this->hasMoved = false;
	};
	Piece(RC position, bool isWhite)
	{
		this->isWhite = isWhite;
		this->currentPosition = position;
		this->hasMoved = false;

	};
	set <RC> virtual getPossibleMoves(Piece* board[]) = 0;
	bool getHasMoved() { return this->hasMoved; };
	bool getIsWhite() { return this->isWhite; };
	bool move() { return false; };

protected:
	RC currentPosition;
	bool hasMoved;
	bool isWhite;

private:

  
};