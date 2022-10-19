#pragma once
#include "Piece.h"
#include "board.h"


// TODO: Use this for Queen, Bishop, and Rook
// To prevent method from being defined multiple times
#ifdef PIECE_METHODS
#define PIECE_METHODS
set <Move> Piece::getSlidingMoves(const Board* board, const RC current, const RC moves[])
{
    set<Move> possible;

    // The current position of the Piece
    int row = current.getRow();
    int col = current.getCol();

    // The row and column being checked
    int r = 0;
    int c = 0;

    int moveSize = sizeof(moves) / sizeof(moves[0]);

    // For each direction in moves,
    for (int i = 0; i < moveSize; i++)
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
#endif