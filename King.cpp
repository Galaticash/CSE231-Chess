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

   // Castling
   // Check if king has moved, check if rook has moved, check if the spaces between the two are empty.

   //King side
   if ((hasMoved == false && this->isWhite)) //((*board)[row][7]->getType() == "ROOK")
      if ((((*board)[row][7])->getHasMoved() == false) && ((*board)[row][7])->getIsWhite() == true)
         if (((*board)[row][5]->isSpace() == true) && ((*board)[row][6]->isSpace() == true))
         {
            possible.insert(Move(RC(row, col), RC(row, 6)));
            Move(RC(row, col), RC(row, 6)).setCastlingK();
         }

   if ((hasMoved == false && !this->isWhite))
      if ((((*board)[row][7])->getHasMoved() == false) && ((*board)[row][7])->getIsWhite() == false)
         if (((*board)[row][5]->isSpace() == true) && ((*board)[row][6]->isSpace() == true))
         {
            possible.insert(Move(RC(row, col), RC(row, 6)));
            Move(RC(row, col), RC(row, 6)).setCastlingK();
         }

   // Queen side
   if ((hasMoved == false && this->isWhite))
      if ((((*board)[row][0])->getHasMoved() == false) && ((*board)[row][0])->getIsWhite() == true)
         if (((*board)[row][1]->isSpace() == true) && ((*board)[row][2]->isSpace() == true) && ((*board)[row][3]->isSpace() == true))
         {
            possible.insert(Move(RC(row, col), RC(row, 2)));
            Move(RC(row, col), RC(row, 2)).setCastlingQ();
         }

   if ((hasMoved == false && !this->isWhite))
      if ((((*board)[row][0])->getHasMoved() == false) && ((*board)[row][0])->getIsWhite() == false)
         if (((*board)[row][1]->isSpace() == true) && ((*board)[row][2]->isSpace() == true) && ((*board)[row][3]->isSpace() == true))
         {
            possible.insert(Move(RC(row, col), RC(row, 2)));
            Move(RC(row, col), RC(row, 2)).setCastlingQ();
         }


   return possible;
};