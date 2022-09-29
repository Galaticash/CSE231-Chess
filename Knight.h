/***********************************************************************
 * Header File:
 *    Knight:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	// Call the base Constructor
	Knight(RC position, bool isWhite) : Piece()
	{};
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

        // The possible moves for a Knight
        RC moves[8] =
        {
                    {-1,  2}, { 1,  2},
        {-2,  1},                    { 2,  1},
        {-2, -1},                    { 2, -1},
                    {-1, -2}, { 1, -2}
        };
        
        // For each move, check 
        for (int i = 0; i < 8; i++)
        {
            r = row + moves[i].getRow();
            c = col + moves[i].getCol();

            // If the piece at the position is the opposite color, or a Space
            if (board[r][c].isSpace() || (!this->isWhite && board[r][c].getIsWhite()))
                possible.insert(Move(this, RC(row, col), RC(r, c)));
            if (board[r][c].isSpace() || (this->isWhite && !board[r][c].getIsWhite()))
                possible.insert(Move(this, RC(row, col), RC(r, c)));
        }

		return possible;
    };

};