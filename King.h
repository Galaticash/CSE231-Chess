/***********************************************************************
 * Header File:
 *    King:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	// Call the base Constructor
	King(RC position, bool isWhite) : Piece()
	{};
	set <Move> getPossibleMoves(Piece* board[], Move lastMove) 
	{ 
		set <Move> possible; 

        int row = this->currentPosition.getRow(); // current location row
        int col = this->currentPosition.getCol(); // current location column

        // If the currentPosition is not valid or the selected Position is an empty Space
        if (!(isValidPosition(this->currentPosition)) || board[row][col] == Space(RC(row, col)))
            return possible;

        int r;                   // the row we are checking
        int c;                   // the column we are checking

        // posible deltas, changes in position
        RC moves[8] =
        {
            {-1,  1}, {0,  1}, {1,  1},
            {-1,  0},          {1,  0},
            {-1, -1}, {0, -1}, {1, -1}
        };

        // For each possible move,
        for (int i = 0; i < 8; i++)
        {
            r = row + moves[i].getRow();
            c = col + moves[i].getCol();

            if (board[r][c].isSpace() || (!this->isWhite && board[r][c].getIsWhite()))
                possible.insert(Move(this, RC(row, col), RC(r, c)));
            if (board[r][c].isSpace() || (this->isWhite && !board[r][c].getIsWhite()))
                possible.insert(Move(this, RC(row, col), RC(r, c)));
        }
        
        // what about castling?
        
		
		return possible;
	};
};