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
set <Move> Queen::getPossibleMoves(Board* board, Move lastMove)
{
   set <Move> possible;

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column
   
   // If the position is not valid, or the selected Position is an empty Space, or it is not this Piece's turn,
   if (!(board->isValidPosition(this->currentPosition)) || board->getPieceAtPosition(RC(row, col))->isSpace() || board->currentIsWhite() != this->isWhite)
       return possible;

   int r;                   // the row we are checking
   int c;                   // the column we are checking

   RC moves[8] =
   {
       {-1,  1}, {0,  1}, {1,  1},
       {-1,  0},          {1,  0},
       {-1, -1}, {0, -1}, {1, -1}
   };

   for (int i = 0; i < 8; i++)
   {
      r = row + moves[i].getRow();
      c = col + moves[i].getCol();
      if (board->isValidPosition(RC(r, c)))
      {
          while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
              (*board)[r][c]->isSpace())
          {
              possible.insert(Move(RC(row, col), RC(r, c)));
              r += moves[i].getRow();
              c += moves[i].getCol();
          }

          if (board->isValidPosition(RC(r, c)))
          {
              if ((*board)[r][c]->isSpace() || (!this->isWhite && (*board)[r][c]->getIsWhite()))
                  possible.insert(Move(RC(row, col), RC(r, c)));
              if ((*board)[r][c]->isSpace() || (this->isWhite && !(*board)[r][c]->getIsWhite()))
                  possible.insert(Move(RC(row, col), RC(r, c)));
          }
      }
   }


   return possible;
};

