/***********************************************************************
 * Header File:
 *    Knight:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	// Call the base Constructor
	Knight(RC position, bool isWhite)
	{
		Piece(position, isWhite);
	};
};