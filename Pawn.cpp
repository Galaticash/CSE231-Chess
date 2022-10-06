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
set <Move> Pawn::getPossibleMoves(Piece** board, Move lastMove) {

    // *** TODO: Add Move.capture ***

   set <Move> possible = {}; // Store possible Moves in a set

   int row = this->currentPosition.getRow(); // current location row
   int col = this->currentPosition.getCol(); // current location column

   // If the position is not valid or the selected Position is an empty Space
   if (!(isValidPosition(this->currentPosition)) || board[row][col].isSpace())
      return possible;

   int r;                   // the row we are checking
   int c;                   // the column we are checking
   int direction = (isWhite) ? -1 : 1; // The direction the Pawn is travelling

   // Check the space 1 row ahead of the Piece in the direction it is travelling
   c = col;   
   r = row + direction;
   
   // Note: Pawn cannot capture while moving forward, only diagonal and en-passant

   // If the space in front of the Pawn is empty,
   if (board[r][c].isSpace())
   {
       // If the Pawn is going into the last row,
       if (r == 8 || r == 0)
       {
           possible.insert(Move(RC(row, col), RC(r, c))); // Move forward one, and promote to Queen***
       }
       else
       {
           possible.insert(Move(RC(row, col), RC(r, c)));  // forward one blank space
       }

       // If the Pawn has not yet moved AND the space 2 rows ahead is also empty,
       if ((!this->hasMoved) && board[r + direction][c].isSpace())
       {
           possible.insert(Move(RC(row, col), RC(r + direction, c))); // forward two blank spaces
       }
   } 

   c = col - 1; 
   // If the piece on the left diagonal is a Piece of the opposite color
   if (!(board[r][c].isSpace()) && board[r][c].getIsWhite() != this->isWhite)
   {
       possible.insert(Move(RC(row, col), RC(r, c))); // left diagonal capture***
   }

   c = col + 1; 
   // If the piece on the right diagonal is a Piece of the opposite color
   if (!(board[r][c].isSpace()) && board[r][c].getIsWhite() != this->isWhite)
   {
       possible.insert(Move(RC(row, col), RC(r, c)));     // right diagonal capture***
   }

   // En-Passant
   // Pawns directly to the left/right of the current Pawn

   // If the lastMove was a Pawn travelling two vertical spaces,
   if (lastMove.getPieceType() == this->getType() && abs(lastMove.getDelta().getRow()) == 2)
   {   
       // If the enemy Pawn moved to the space one left of this Pawn
       // Not really needed, or could be a part of Move (Piece color) && board[row][col -1].getIsWhite() != this->isWhite
       // Probably throw in an assert (opposite colors)
       if (lastMove.getPositionTo() == RC(row, col - 1))
       {
           possible.insert(Move(RC(row, col), RC(row, col - 1))); // Capture the Pawn En-Passant***
       }
       // If the enemy Pawn moved to the space one right of this Pawn    
       else if (lastMove.getPositionTo() == RC(row + direction, col + 1))
       {
           possible.insert(Move(RC(row, col), RC(row + direction, col + 1))); // Capture the Pawn En-Passant***
       }
   }   

   return possible;
};

