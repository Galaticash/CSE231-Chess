/***********************************************************************
 * Header File:
 *    Rook:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	// Call the base Constructor
	Rook(RC position, bool isWhite)
	{
		Piece(position, isWhite);
	};
};