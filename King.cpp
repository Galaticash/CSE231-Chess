/***********************************************************************
 * Source File:
 *    King:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "King.h"

/***************************************
* GET POSSIBLE MOVES
* Get's the possible moves from a piece.
********************************************/
set <Move> King::getPossibleMoves(Piece* board[][8][8], Move lastMove)
{
   set <Move> possible;

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column

   // If the currentPosition is not valid or the selected Position is an empty Space
   if (!(isValidPosition(this->currentPosition)) || (*board)[row][col]->isSpace())
      return possible;

   int r;                   // the row we are checking
   int c;                   // the column we are checking

   // posible deltas, changes in position
   RC moves[8] =
   {
       {-1,  1}, {0,  1}, {1,  1},
       {-1,  0},          {1,  0},
       {-1, -1}, {0, -1}, {1, -1}
   };

   // For each possible move,
   for (int i = 0; i < 8; i++)
   {
      r = row + moves[i].getRow();
      c = col + moves[i].getCol();

      if ((*board)[row][col]->isSpace() || (!this->isWhite && (*board)[r][c]->getIsWhite()))
         //possible.insert(Move(this, RC(row, col), RC(r, c)));
         possible.insert(Move(RC(row, col), RC(r, c)));

      if ((*board)[row][col]->isSpace() || (this->isWhite && !(*board)[r][c]->getIsWhite()))
         //possible.insert(Move(this, RC(row, col), RC(r, c)));
         possible.insert(Move(RC(row, col), RC(r, c)));
   }

   // what about castling?


   return possible;
};