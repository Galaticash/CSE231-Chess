/***********************************************************************
 * Source File:
 *    Bishop: A bishop in chess
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Contains the code for how a bishop moves.
 ************************************************************************/

#pragma once
#include "Bishop.h"

 /***************************************
 * GET POSSIBLE MOVES
 * Get's the possible moves from a piece.
 ********************************************/
set <Move> Bishop::getPossibleMoves(Board* board, Move lastMove)
{
   set <Move> possible;

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column

   // If the position is not valid, or the selected Position is an empty Space, or it is not this Piece's turn,
   if (!(board->isValidPosition(this->currentPosition)) || board->getPieceAtPosition(RC(row, col))->isSpace() || board->currentIsWhite() != this->isWhite)
       return possible;

   int r;                   // the row we are checking
   int c;                   // the column we are checking

   // The possible RC movement for a Bishop
   RC moves[4] =
   {
       {-1,  1}, {1,  1},
       {-1, -1}, {1, -1}
   };

   // For each possible direction,
   for (int i = 0; i < 4; i++)
   {
       r = row + moves[i].getRow();
       c = col + moves[i].getCol();
       if (board->isValidPosition(RC(r, c)))
       {
           // Check how many clear spaces are in each direction,
           //  goes until it is blocked or reaches the end of the board
           while (board->isValidPosition(RC(r, c)) &&
               (*board)[r][c]->isSpace())
           {
               possible.insert(Move(RC(row, col), RC(r, c)));
               r += moves[i].getRow();
               c += moves[i].getCol();
           }

           // TODO: Rewrite, keeps checking isValid
           // TODO: Move slide to Piece class, then have Bishop, Queen, etc call getSlide for each direction
           if (board->isValidPosition(RC(r, c)))
           {
               // Check if it can capture the piece that is blocking
               if ((*board)[r][c]->isSpace() || (!this->isWhite && (*board)[r][c]->getIsWhite()))
                   possible.insert(Move(RC(row, col), RC(r, c)));
               if ((*board)[r][c]->isSpace() || (this->isWhite && !(*board)[r][c]->getIsWhite()))
                   possible.insert(Move(RC(row, col), RC(r, c)));
           }
       }
   }

   return possible;
};

