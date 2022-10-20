/***********************************************************************
 * Source File:
 *    Knight
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		A knight in chess. This file contains info on moving a knight.
 ************************************************************************/

#pragma once
#include "Knight.h"

/***************************************
* GET POSSIBLE MOVES
* Get's the possible moves from a piece.
********************************************/
set <Move> Knight::getPossibleMoves(Board* board)
{
   set <Move> possible;
   
   // If the position is not valid, or the selected Position is an empty Space, or it is not this Piece's turn,
   if (!(board->isValidPosition(this->currentPosition)) || board->getCurrentTeam() != this->isWhite)
       return possible;

   // The possible moves for a Knight
   RC moves[8] =
   {
               {-1,  2}, { 1,  2},
   {-2,  1},                    { 2,  1},
   {-2, -1},                    { 2, -1},
               {-1, -2}, { 1, -2}
   };

   // The Knight only does non-sliding Moves in the given directions
   possible = getNonSlidingMoves(board, this->currentPosition, moves);

   return possible;
};