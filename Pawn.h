/***********************************************************************
 * Header File:
 *    Pawn:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"
#include "Space.h" // check for empty position

class Pawn : public Piece
{
public:
	// Call the base Constructor
	Pawn(RC position, bool isWhite) : Piece()
	{ };

	set <Move> getPossibleMove(Piece* board[]) {

        // TODO: Change to RCs
        // Note: stored 0 - 7 or 1 - 8? 0 - 7 is best for code (don't have to change to index every time board is used)
        //set <int> possible;
        set <Move> possible;

        int row = this->currentPosition.getRow(); // current location row
        int col = this->currentPosition.getCol(); // current location column

        // return the empty set if there simply are no possible moves
        if (row < 0 || row > 7 || col < 0 || row > 7 || board[row][col] == Space(RC(row, col)))
            return possible; 
        int r;                   // the row we are checking
        int c;                   // the column we are checking
        // C# -> type(board[r][c] == Space)

        c = col;
        r = row + isWhite ? 2 : -2; // row +/- 2, based on if moving up/down
        if (row == 6 && board[r * 8 + c] == Space())
            possible.insert(Move(RC(row, col), RC(r, c));
                //r * 8 + c);  // forward two blank spaces
        r = row + isWhite ? 1 : -1; // +/- 1 based on moving up/down
        if (r >= 0 && board[r * 8 + c] == Space())
            possible.insert(r * 8 + c);  // forward one black space
        c = col - 1; //same
        if (board[r][c].getIsWhite()) // isWhite(board, r, c))
            possible.insert(r * 8 + c);    // attack left
        c = col + 1; //same
        if (board[r][c].getIsWhite()) //(isWhite(board, r, c))
            possible.insert(r * 8 + c);    // attack right
        
       // what about en-passant and pawn promotion
        //if (board[row +/- 1][col] == Pawn(RC(row +/- 1, col), !isWhite))

        //if
        // Move(from, to, Q)

        // redundant, double check changes
        if (board[location] == 'p')
        {
            c = col;
            r = row + 2;
            if (row == 1 && board[r * 8 + c] == ' ')
                possible.insert(r * 8 + c);  // forward two blank spaces
            r = row + 1;
            if (r < 8 && board[r * 8 + c] == ' ')
                possible.insert(r * 8 + c);    // forward one blank space
            c = col - 1;
            if (isBlack(board, r, c))
                possible.insert(r * 8 + c);      // attack left
            c = col + 1;
            if (isBlack(board, r, c))
                possible.insert(r * 8 + c);      // attack right
             // what about en-passant and pawn promotion
        }
    };
};