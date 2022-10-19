/***********************************************************************
 * Source File:
 *    Pawn
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		A pawn in chess. This file contains info on moving a pawn.
 ************************************************************************/

#pragma once
#include "Pawn.h"

 /***************************************
 * GET POSSIBLE MOVES
 * Gets the possible moves from a Piece.
 ********************************************/
set <Move> Pawn::getPossibleMoves(Board* board) {

    set <Move> possible = {}; // Store possible Moves in a set

    int row = this->currentPosition.getRow(); // current location row
    int col = this->currentPosition.getCol(); // current location column
 
    // If the Piece isn't at a valid position, or it is not this Piece's turn,
    if (!(board->isValidPosition(this->currentPosition)) || board->getCurrentTeam() != this->isWhite)
        return possible;

    int r;                   // the row we are checking
    int c;                   // the column we are checking

    int direction = (isWhite) ? 1 : -1; // The direction the Pawn is travelling, assumes White at bottom

    // Check the space 1 row ahead of the Piece in the direction it is travelling
    c = col;
    r = row + direction;

    // If the space in front of the Pawn is empty,
    if (board->isValidPosition(RC(r, c)) && (*board)[r][c]->isSpace())
    {
        Move moveForward = Move(RC(row, col), RC(r, c));
        // If the Pawn is going into the last row,
        if (r == (NUM_ROW - 1) || r == 0)
        {
            moveForward.setPromotion('Q'); // Will promote to Queen
        }
        possible.insert(moveForward);  // forward one blank space

        // If the Pawn has not yet moved AND the space 2 rows ahead is also empty,
        if ((!this->hasMoved) && (*board)[r + direction][c]->isSpace())
        {
            possible.insert(Move(RC(row, col), RC(r + direction, c))); // forward two blank spaces
        }
    }

    // Capture cases
    // Left and right capture (-1 and +1)
    for (c = col - 1; c <= col + 1; c += 2)
    {
        // If the diagonal Piece is valid and an enemy of the opposite color
        if (board->isValidPosition(RC(r, c)) && !((*board)[r][c]->isSpace()) && (*board)[r][c]->getIsWhite() != this->isWhite)
        {
            // The Pawn will move from its current position to the new position
            Move capture = Move(RC(row, col), RC(r, c));

            // Capture the Piece at that position
            capture.setCapture((*board)[r][c]->getType());

            // If the Pawn is moving into the last row,
            if (r == (NUM_ROW - 1) || r == 0)
            {
                capture.setPromotion('Q');
            }

            // Add to set of possible moves
            possible.insert(capture); // diagonal capture
        }

    }

    // Get the last Move performed
    Move lastMove = board->getLastMove();

    // En-Passant
    // If the lastMove was a Pawn travelling two vertical spaces,
    if ((*board).getPieceAtPosition(lastMove.getPositionTo())->getType() == this->getType() && abs(lastMove.getDelta().getRow()) == 2)
    {
        // Not really needed, or could be a part of Move (Piece color) && board[row][col -1].getIsWhite() != this->isWhite
        // Probably throw in an assert (opposite colors)
        //assert(this->getIsWhite != (*board).getPieceAtPosition(lastMove.getPositionTo())->getIsWhite());
        //  && (*board)[row + direction][c]->isSpace() <- always true, since Pawn can't jump over other Pieces. Could place an assert
        //assert((*board)[row + direction][c]->isSpace())

        // Left and right cases (-1 and +1)
        for (c = col - 1; c <= col + 1; c += 2)
        {
            // If the enemy Pawn moved to the space one left or right of this Pawn,
            if (lastMove.getPositionTo() == RC(row, c))
            {
                // Capture the Pawn En-Passant
                // Move the current Pawn to the space behind the captured Pawn
                Move enPassant = Move(RC(row, col), RC(row + direction, c));
                enPassant.setEnPassant();
                possible.insert(enPassant);
            }
        }
    }

    return possible;
};

