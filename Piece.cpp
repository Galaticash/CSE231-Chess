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