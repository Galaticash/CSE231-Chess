/***********************************************************************
 * Header File:
 *    Bishop:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	// Call the base Constructor
	Bishop(RC position, bool isWhite)
	{
		Piece(position, isWhite);
	};
};