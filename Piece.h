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
using namespace std;

class Piece {
public:
	Move[] getPossibleMoves();
	bool getHasMoved() { return false; };
	bool move() { return false; }

protected:
	bool hasMoved;
	bool isWhite;

private:
}