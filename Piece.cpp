/***********************************************************************
 * Source File:
 *		Piece
 * Authors:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		The base class for all types of Pieces in a chess game.
 ************************************************************************/
#pragma once
#include "Piece.h"

/***************************************
* GET SLIDING MOVES
* Gets the possible sliding moves for a Piece,
* given the starting position and the move deltas
********************************************/
set <Move> Piece::getSlidingMoves(const Board* board, RC current, RC moves[])
{
    set<Move> possible;

    // The current position of the Piece
    int row = current.getRow();
    int col = current.getCol();

    // The row and column being checked
    int r = 0;
    int c = 0;

    int moveSize = sizeof(moves);

    // For each direction in moves,
    for (int i = 0; i < moveSize; i++)
    {
        r = row + moves[i].getRow();
        c = col + moves[i].getCol();

        // If the space is a valid position on the board,
        if (board->isValidPosition(RC(r, c)))
        {
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                (*board).getPieceAtPosition(RC(r, c))->isSpace())
            {
                possible.insert(Move(RC(row, col), RC(r, c)));
                r += moves[i].getRow();
                c += moves[i].getCol();
            }

            // If the capture position is a valid position on the board,
            if (board->isValidPosition(RC(r, c)))
            {
                if ((*board).getPieceAtPosition(RC(r, c))->isSpace() || (!this->isWhite && (*board).getPieceAtPosition(RC(r, c))->getIsWhite()))
                    possible.insert(Move(RC(row, col), RC(r, c)));
                if ((*board).getPieceAtPosition(RC(r, c))->isSpace() || (this->isWhite && !(*board).getPieceAtPosition(RC(r, c))->getIsWhite()))
                    possible.insert(Move(RC(row, col), RC(r, c)));
            }
        }
    }
    return possible;
};

/***************************************
* GET NON SLIDING MOVES
* Gets the possible non-sliding moves for a Piece,
* given the starting position and the move deltas
********************************************/
set <Move> Piece::getNonSlidingMoves(const Board* board, RC current, RC moves[]) 
{
   set<Move> possible;

   // The current position of the Piece
   int row = current.getRow();
   int col = current.getCol();

   // The row and column being checked
   int r = 0;
   int c = 0;

   int moveSize = sizeof(moves);

   // For each move, check 
   for (int i = 0; i < moveSize; i++)
   {
      r = row + moves[i].getRow();
      c = col + moves[i].getCol();
      if (board->isValidPosition(RC(r, c)))
      {
         // If the piece at the position is the opposite color, or a Space
         if ((*board).getPieceAtPosition(RC(r, c))->isSpace() || (!this->isWhite && (*board).getPieceAtPosition(RC(r, c))->getIsWhite()))
            possible.insert(Move(RC(row, col), RC(r, c)));
         if ((*board).getPieceAtPosition(RC(r, c))->isSpace() || (this->isWhite && !(*board).getPieceAtPosition(RC(r, c))->getIsWhite()))
            possible.insert(Move(RC(row, col), RC(r, c)));
      }
   }
   return possible;
}