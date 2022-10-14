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
set <Move> King::getPossibleMoves(Board* board, Move lastMove)
{
   set <Move> possible;

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column

   // If the currentPosition is not valid or the selected Position is an empty Space
   if (!board->isValidPosition(this->currentPosition) || (*board)[row][col].isSpace())
       return possible;

   int r;                   // the row we are checking
   int c;                   // the column we are checking

   // posible deltas, changes in position
   RC moves[8] =
   {
       {-1,  -1}, {-1,  0}, {-1,  1},
       {0,  -1},          {0,  1},
       {1, -1}, {1, 0}, {1, 1}
   };

   // For each possible move,
   for (int i = 0; i < 8; i++)
   {
      r = row + moves[i].getRow();
      c = col + moves[i].getCol();

      // Piece cannot move off the Board
      if (board->isValidPosition(RC(r, c)))
      {
          // If Move desitnation is a Space,
          if ((*board)[r][c].isSpace())
          {
              possible.insert(Move(RC(row, col), RC(r, c)));
          }
          // Else if Move destination is a Piece of the opposite color,
          else if (this->isWhite != (*board)[r][c].getIsWhite())
          {
              // Set what Piece is captured by this Move
              Move capture = Move(RC(row, col), RC(r, c));
              capture.setCapture((*board)[r][c].getType());
              possible.insert(capture);
          }
      }
   }

   // Castling
   // If the King has not moved,
   if (!(hasMoved))
   {
       // If Rook at column 7 hasn't moved (King Side) AND the spaces between are clear
       if ((*board)[row][7].getType() == 'r' && (!(*board)[row][7].getHasMoved()) && (*board)[row][5].isSpace() && (*board)[row][6].isSpace())
       {
           // Define Move, then set to castling, then insert into set
           Move castlingK = Move(RC(row, col), RC(row, 6));
           castlingK.setCastlingK();
           possible.insert(castlingK);
       }
       // If the Rook at column 0 hasn't moved (Queen side) AND the spaces between are clear
       else if ((*board)[row][0].getType() == 'r' && (!(*board)[row][0].getHasMoved()) && (*board)[row][1].isSpace() && (*board)[row][2].isSpace() && (*board)[row][3].isSpace())
       {
           Move castlingQ = Move(RC(row, col), RC(row, 2));
           castlingQ.setCastlingQ();
           possible.insert(castlingQ);
       }
   }

   return possible;
};