/***********************************************************************
 * Header File:
 *    Bishop:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	// Call the base Constructor
	Bishop(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = "BISHOP";
    };

	set <Move> getPossibleMoves(Piece* board[], Move lastMove)
	{ 
		set <Move> possible;
		
        int row = this->currentPosition.getRow(); // current location row
        int col = this->currentPosition.getCol(); // current location column

        // If the position is not valid or the selected Position is an empty Space
        if (!(isValidPosition(this->currentPosition)) || board[row][col] == Space(RC(row, col)))
            return possible;

        int r;                   // the row we are checking
        int c;                   // the column we are checking

        // The possible RC movement for a Bishop
        RC moves[4] =
        {
            {-1,  1}, {1,  1},
            {-1, -1}, {1, -1}
        };

        // For each possible direction,
        for (int i = 0; i < 4; i++)
        {
            r = row + moves[i].getRow();
            c = col + moves[i].getCol();

            // Check how many clear spaces are in each direction,
            //  goes until it is blocked or reaches the end of the board
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[r][c].isSpace())
            {
                possible.insert(Move(this, RC(row, col), RC(r, c)));
                r += moves[i].getRow();
                c += moves[i].getCol();
            }

            // Check if it can capture the piece that is blocking
            if (board[r][c].isSpace() || (!this->isWhite && board[r][c].getIsWhite()))
                possible.insert(Move(this, RC(row, col), RC(r, c)));
            if (board[r][c].isSpace() || (this->isWhite && !board[r][c].getIsWhite()))
                possible.insert(Move(this, RC(row, col), RC(r, c)));
        }
		
		return possible;
	};
};