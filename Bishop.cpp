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
    if (!(board->isValidPosition(this->currentPosition)) || board->getCurrentTeam() != this->isWhite)
        return possible;

    // The possible RC movement for a Bishop
    RC moves[4] =
    {
        {-1,  1}, {1,  1},
        {-1, -1}, {1, -1}
    };

    // The Bishop only does sliding Moves in the given directions
    possible = getSlidingMoves(board, this->currentPosition, moves);
    return possible;
};

