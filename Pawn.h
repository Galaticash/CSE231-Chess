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

class Pawn : public Piece
{
public:
	// Call the base Constructor
	Pawn(RC position, bool isWhite)
	{
		Piece(position, isWhite);
	};

	void getPossibleMove() {

        // TODO: Change to RCs
        set <int> possible;

        // return the empty set if there simply are no possible moves
        if (this->currentPosition.getRow() < 0 || location >= 64 || board[location] == ' ')
            return possible;
        int row = location / 8;  // current location row
        int col = location % 8;  // current location column
        int r;                   // the row we are checking
        int c;                   // the column we are checking
        bool amBlack = !this->isWhite;

        //
        // PAWN
        //
        if (board[location] == 'P')
        {
            c = col;
            r = row - 2;
            if (row == 6 && board[r * 8 + c] == ' ')
                possible.insert(r * 8 + c);  // forward two blank spaces
            r = row - 1;
            if (r >= 0 && board[r * 8 + c] == ' ')
                possible.insert(r * 8 + c);  // forward one black space
            c = col - 1;
            if (isWhite(board, r, c))
                possible.insert(r * 8 + c);    // attack left
            c = col + 1;
            if (isWhite(board, r, c))
                possible.insert(r * 8 + c);    // attack right
             // what about en-passant and pawn promotion
        }
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