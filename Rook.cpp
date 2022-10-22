/***********************************************************************
* Source File:
*    Rook
* Author:
*		Ashley DeMott, Logan Huston
* Summary:
*		A rook in chess. This file contains info on moving a rook. 
************************************************************************/

#pragma once
#include "Rook.h"

/***************************************
* GET POSSIBLE MOVES
* Get's the possible moves from a piece.
********************************************/
set <Move> Rook::getPossibleMoves(Board* board)
{
   set <Move> possible;

   // If the Piece isn't at a valid position, or it is not this Piece's turn,
   if (!(board->isValidPosition(this->currentPosition)) || board->getCurrentTeam() != this->isWhite)
      return possible;

   RC moves[4] =
   {
               {0,  1},
      {-1, 0},          {1, 0},
               {0, -1}
   };

   // The Rook only does sliding moves in the given directions
   possible = getSlidingMoves(board, this->currentPosition, moves);
   return possible;
};

