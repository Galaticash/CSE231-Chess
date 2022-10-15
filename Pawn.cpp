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
// Board ->getPiece
set <Move> Pawn::getPossibleMoves(Board* board, Move lastMove) {

    set <Move> possible = {}; // Store possible Moves in a set

    int row = this->currentPosition.getRow(); // current location row
    int col = this->currentPosition.getCol(); // current location column


    // TODO: board[r][c] instead of board.getPiece(RC(r, c))

    // If the position is not valid or the selected Position is an empty Space
    if (!(board->isValidPosition(this->currentPosition)) || board->getPieceAtPosition(RC(row, col))->isSpace())
        return possible;

    int r;                   // the row we are checking
    int c;                   // the column we are checking
    // TODO: change to use TEAM_ONE/TEAM_TWO (board orientation)
    int direction = (isWhite) ? 1 : -1; // The direction the Pawn is travelling

    // Check the space 1 row ahead of the Piece in the direction it is travelling
    c = col;
    r = row + direction;

    // Note: Pawn cannot capture while moving forward, only diagonal and en-passant

    // If the space in front of the Pawn is empty,
    if ((*board)[r][c]->isSpace())
    {
        Move moveForward = Move(RC(row, col), RC(r, c));
        // If the Pawn is going into the last row,
        if (r == (NUM_ROW - 1) || r == 0)
        {
            moveForward.setPromotion(); // Will promote to Queen***
        }
        possible.insert(moveForward);  // forward one blank space

        // If the Pawn has not yet moved AND the space 2 rows ahead is also empty,
        if ((!this->hasMoved) && (*board)[r + direction][c]->isSpace())
        {
            possible.insert(Move(RC(row, col), RC(r + direction, c))); // forward two blank spaces
        }
    }

    // Capture cases
    // TODO: Duplicate code, condense

    c = col - 1;
    // If the piece on the left diagonal is a Piece of the opposite color
    if (!((*board)[r][c]->isSpace()) && (*board)[r][c]->getIsWhite() != this->isWhite)
    {
        // The Pawn will move from its current position to the new position
        Move captureLeft = Move(RC(row, col), RC(r, c));

        // Capture the Piece at that position
        captureLeft.setCapture((*board)[r][c]->getType());

        // If the Pawn is moving into the last row,
        if (r == (NUM_ROW - 1) || r == 0)
        {
            captureLeft.setPromotion();
        }

        // Add to set of possible moves
        possible.insert(captureLeft); // left diagonal capture
    }

    c = col + 1;
    // If the piece on the right diagonal is a Piece of the opposite color
    if (!((*board)[r][c]->isSpace()) && (*board)[r][c]->getIsWhite() != this->isWhite)
    {
        // The Pawn will move from its current position to the new position
        Move captureRight = Move(RC(row, col), RC(r, c));

        // Capture the Piece at that position
        captureRight.setCapture((*board)[r][c]->getType());

        // If the Pawn is moving into the last row,
        if (r == (NUM_ROW - 1) || r == 0)
        {
            captureRight.setPromotion();
        }

        // Add to set of possible moves
        possible.insert(captureRight); // right diagonal capture
    }

    // En-Passant
    // If the lastMove was a Pawn travelling two vertical spaces,
    if ((*board).getPieceAtPosition(lastMove.getPositionTo())->getType() == this->getType() && abs(lastMove.getDelta().getRow()) == 2)
    {
        // Not really needed, or could be a part of Move (Piece color) && board[row][col -1].getIsWhite() != this->isWhite
        // Probably throw in an assert (opposite colors)
        //  && (*board)[row + direction][col - 1]->isSpace() <- always true, since Pawn can't jump over other Pieces. Could place an assert

        // If the enemy Pawn moved to the space one left of this Pawn,
        if (lastMove.getPositionTo() == RC(row, col - 1))
        {
            Move enPassantLeft = Move(RC(row, col), RC(row + direction, col - 1));
            enPassantLeft.setEnPassant();
            possible.insert(enPassantLeft); // Capture the Pawn En-Passant
        }
        // If the enemy Pawn moved to the space one right of this Pawn,
        else if (lastMove.getPositionTo() == RC(row, col + 1))
        {
            Move enPassantRight = Move(RC(row, col), RC(row + direction, col + 1));
            enPassantRight.setEnPassant();
            possible.insert(enPassantRight); // Capture the Pawn En-Passant
        }
    }

    return possible;
};

