/***********************************************************************
 * Source File:
 *    King
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		A king in chess. This file contains info on moving a king.
 ************************************************************************/

#pragma once
#include "King.h"

/***************************************
* GET POSSIBLE MOVES
* Get's the possible moves from a piece.
********************************************/
set <Move> King::getPossibleMoves(Board* board)
{
   set <Move> possible;

   // If the position is not valid, or the selected Position is an empty Space, or it is not this Piece's turn,
   if (!(board->isValidPosition(this->currentPosition)) || board->getCurrentTeam() != this->isWhite)
       return possible;

   // posible deltas, changes in position
   RC moves[8] =
   {
       {-1,  -1}, {-1,  0}, {-1,  1},
       {0,  -1},          {0,  1},
       {1, -1}, {1, 0}, {1, 1}
   };

   possible = getNonSlidingMoves(board, this->currentPosition, moves);

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column

   int r;                   // the row we are checking
   int c;                   // the column we are checking

   // Castling
   // If the King has not moved,
   if (!(hasMoved))
   {
       // If Rook at column 7 hasn't moved (King Side) AND the spaces between are clear
       if ((*board)[row][7]->getType() == 'r' && (!(*board)[row][7]->getHasMoved()) && (*board)[row][5]->isSpace() && (*board)[row][6]->isSpace())
       {
           // Define Move, then set to castling, then insert into set
           Move castlingK = Move(RC(row, col), RC(row, 6));
           castlingK.setCastlingK();
           possible.insert(castlingK);
       }
       // If the Rook at column 0 hasn't moved (Queen side) AND the spaces between are clear
       else if ((*board)[row][0]->getType() == 'r' && (!(*board)[row][0]->getHasMoved()) && (*board)[row][1]->isSpace() && (*board)[row][2]->isSpace() && (*board)[row][3]->isSpace())
       {
           Move castlingQ = Move(RC(row, col), RC(row, 2));
           castlingQ.setCastlingQ();
           possible.insert(castlingQ);
       }
   }

   return possible;
};