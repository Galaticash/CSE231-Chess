/***********************************************************************
 * Source File:
 *    Bishop
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		A bishop in chess. This file contains info on moving a bishop.
 ************************************************************************/

#pragma once
#include "Bishop.h"

 /***************************************
 * GET POSSIBLE MOVES
 * Get's the possible moves from a piece.
 ********************************************/
set <Move> Bishop::getPossibleMoves(Board* board)
{
    set <Move> possible;

    // If the Piece isn't at a valid position, or it is not this Piece's turn,
    if (!(board->isValidPosition(this->currentPosition)) || board->currentIsWhite() != this->isWhite)
        return possible;

   // The possible RC movement for a Bishop
   RC moves[4] =
   {
       {-1,  1}, {1,  1},
       {-1, -1}, {1, -1}
   };

   // The Bishop only does sliding Moves in the given directions
   //possible = getSlidingMoves(board, this->currentPosition, moves);

   // The current position of the Piece
   int row = this->getCurrentPosition().getRow();
   int col = this->getCurrentPosition().getCol();

   // The row and column being checked
   int r = 0;
   int c = 0;

   // For each direction in moves,
   for (int i = 0; i < sizeof(moves); i++)
   {
       r = row + moves[i].getRow();
       c = col + moves[i].getCol();

       // If the space is a valid position on the board,
       if (board->isValidPosition(RC(r, c)))
       {
           while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
               (*board)[r][c]->isSpace())
           {
               possible.insert(Move(RC(row, col), RC(r, c)));
               r += moves[i].getRow();
               c += moves[i].getCol();
           }

           // If the capture position is a valid position on the board,
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

