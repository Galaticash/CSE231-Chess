/***********************************************************************
 * Source File:
 *    Rook:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Rook.h"

 /***************************************
 * GET POSSIBLE MOVES
 * Get's the possible moves from a piece.
 ********************************************/
set <Move> Rook::getPossibleMoves(Board* board, Move lastMove)
{
   set <Move> possible;

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column

   // If the position is not valid, or the selected Position is an empty Space, or it is not this Piece's turn,
   if (!(board->isValidPosition(this->currentPosition)) || board->getPieceAtPosition(RC(row, col))->isSpace() || board->currentIsWhite() != this->isWhite)
       return possible;

   int r;                   // the row we are checking
   int c;                   // the column we are checking

   RC moves[4] =
   {
               {0,  1},
       {-1, 0},         {1, 0},
               {0, -1}
   };

   // For each possible direction
   for (int i = 0; i < 4; i++)
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

