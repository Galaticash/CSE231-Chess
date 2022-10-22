/***********************************************************************
* Source File:
*    Queen
* Author:
*		Ashley DeMott, Logan Huston
* Summary:
*		A queen in chess. This file contains info on moving a queen.
************************************************************************/

#pragma once
#include "Queen.h"

/***************************************
* GET POSSIBLE MOVES
* Get's the possible moves from a piece.
********************************************/
set <Move> Queen::getPossibleMoves(Board* board)
{
   set <Move> possible;

   // If the Piece isn't at a valid position, or it is not this Piece's turn,
   if (!(board->isValidPosition(this->currentPosition)) || board->getCurrentTeam() != this->isWhite)
      return possible;

   RC moves[8] =
   {
      {-1,  1}, {0,  1}, {1,  1},
      {-1,  0},          {1,  0},
      {-1, -1}, {0, -1}, {1, -1}
   };

   // The Queen only does sliding Moves in the given directions
   possible = getSlidingMoves(board, this->currentPosition, moves);
   return possible;
};