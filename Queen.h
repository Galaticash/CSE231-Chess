/***********************************************************************
 * Header File:
 *    Queen:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	// Call the base Constructor
	Queen(RC position, bool isWhite) : Piece(position, isWhite)
    {
        this->type = "QUEEN";
    };
	set <Move> getPossibleMoves(Piece* board[], Move lastMove)
	{ 
		set <Move> possible; 

        int row = this->currentPosition.getRow(); // current location row
        int col = this->currentPosition.getCol(); // current location column

        // If the currentPosition is not valid or the selected Position is an empty Space
        if (!(isValidPosition(this->currentPosition)) || board[row][col].isSpace())
            return possible;

        int r;                   // the row we are checking
        int c;                   // the column we are checking

        RC moves[8] =
        {
            {-1,  1}, {0,  1}, {1,  1},
            {-1,  0},          {1,  0},
            {-1, -1}, {0, -1}, {1, -1}
        };

        for (int i = 0; i < 8; i++)
        {
            r = row + moves[i].getRow();
            c = col + moves[i].getCol();
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[r][c].isSpace())
            {
                possible.insert(Move(RC(row, col), RC(r, c)));
                r += moves[i].getRow();
                c += moves[i].getCol();
            }

            if (board[r][c].isSpace() || (!this->isWhite && board[r][c].getIsWhite()))
                possible.insert(Move(RC(row, col), RC(r, c)));
            if (board[r][c].isSpace() || (this->isWhite && !board[r][c].getIsWhite()))
                possible.insert(Move(RC(row, col), RC(r, c)));
        }
        

		return possible; 
	};
};