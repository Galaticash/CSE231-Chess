/***********************************************************************
 * Source File:
 *    Pawn:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Pawn.h"

 /***************************************
 * GET POSSIBLE MOVES
 * Get's the possible moves from a piece.
 ********************************************/
set <Move> Pawn::getPossibleMoves(Piece* board[], Move lastMove) {

   // Store possible Moves in a set
   set <Move> possible = {};

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column

   // If the position is not valid or the selected Position is an empty Space
   if (!(Piece::isValidPosition(this->currentPosition)) || board[row][col].isSpace())
      return possible;

   int r;                   // the row we are checking
   int c;                   // the column we are checking

   c = col;
   r = row + isWhite ? 2 : -2; // Check the space 2 rows ahead of the Piece
   if (row == 6 && board[r][c].isSpace())
      //possible.insert(Move(this, RC(row, col), RC(r, c)));    // forward two blank spaces
      possible.insert(Move(RC(row, col), RC(r, c)));

   r = row + isWhite ? -1 : 1; // check the space right in front of the Piece
   if (r >= 0 && board[r][c].isSpace())
      possible.insert(Move(RC(row, col), RC(r, c)));  // forward one blank space

   c = col - 1; // left capture
   if (board[r][c].getIsWhite())
      //possible.insert(Move(this, RC(row, col), RC(r, c)));    // attack left
      possible.insert(Move(RC(row, col), RC(r, c)));

   c = col + 1; // right capture
   if (board[r][c].getIsWhite())
      //possible.insert(Move(this, RC(row, col), RC(r, c)));    // attack right
      possible.insert(Move(RC(row, col), RC(r, c)));

   // En-Passant
   //if lastMove.getPiece == "PAWN" && 

    //if (board[row +/- 1][col] == Pawn(RC(row +/- 1, col), !isWhite))

    // Pawn Promotion (assumes queen)
    // Move(from, to, Q

   return possible;
};
