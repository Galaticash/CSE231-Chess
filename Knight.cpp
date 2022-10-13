/***********************************************************************
 * Source File:
 *    Knight: A knight in chess
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Contains the code for how a knight moves.
 ************************************************************************/

#pragma once
#include "Knight.h"

/***************************************
* GET POSSIBLE MOVES
* Get's the possible moves from a piece.
********************************************/
set <Move> Knight::getPossibleMoves(Board* board, Move lastMove)
{
   set <Move> possible;

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column

   /*
   // If the position is not valid or the selected Position is an empty Space
   if (!(isValidPosition(this->currentPosition)) || board[row][col].isSpace())
      return possible;

   int r;                   // the row we are checking
   int c;                   // the column we are checking

   // The possible moves for a Knight
   RC moves[8] =
   {
               {-1,  2}, { 1,  2},
   {-2,  1},                    { 2,  1},
   {-2, -1},                    { 2, -1},
               {-1, -2}, { 1, -2}
   };

   // For each move, check 
   for (int i = 0; i < 8; i++)
   {
      r = row + moves[i].getRow();
      c = col + moves[i].getCol();

      // If the piece at the position is the opposite color, or a Space
      if (board[r][c].isSpace() || (!this->isWhite && board[r][c].getIsWhite()))
         possible.insert(Move(RC(row, col), RC(r, c)));
      if (board[r][c].isSpace() || (this->isWhite && !board[r][c].getIsWhite()))
         possible.insert(Move(RC(row, col), RC(r, c)));
   }*/

   return possible;
};