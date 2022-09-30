#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#pragma once
#include "../Pawn.h"
#include "../King.h"

namespace ChessUnitTests
{
	TEST_CLASS(ChessUnitTests)
	{
	public:
		const int NUM_ROW = 8;
		const int NUM_COL = 8;

		/*Piece* DEFAULT_BOARD[NUM_ROW][NUM_COL] = {
					{&Rook(RC(0, 0), 0), &Bishop(RC(0, 1), 0), &Knight(RC(0, 2), 0), &Queen(RC(0, 3), 0), &King(RC(0, 4), 0), &Knight(RC(0, 5), 0), &Bishop(RC(0, 6), 0), &Rook(RC(0, 7), 0)},
					{&Pawn(RC(1, 0), 0), &Pawn(RC(1, 1), 0), &Pawn(RC(1, 2), 0), &Pawn(RC(1, 3), 0), &Pawn(RC(1, 4), 0), &Pawn(RC(1, 5), 0), &Pawn(RC(1, 6), 0), &Pawn(RC(1, 7), 0)},
					{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
					{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
					{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
					{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
					{&Pawn(RC(6, 0), 1), &Pawn(RC(6, 1), 1), &Pawn(RC(6, 2), 1), &Pawn(RC(6, 3), 1), &Pawn(RC(6, 4), 1), &Pawn(RC(6, 5), 1), &Pawn(RC(6, 6), 1), &Pawn(RC(6, 7), 1)},
					{&Rook(RC(7, 0), 1), &Bishop(RC(7, 1), 1), &Knight(RC(7, 2), 1), &Queen(RC(7, 3), 1), &King(RC(7, 4), 1), &Knight(RC(7, 5), 1), &Bishop(RC(7, 6), 1), &Rook(RC(7, 7), 1)} };
*/
		Piece* EMPTY_BOARD[8][8] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &King(RC(1, 1), 0), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

		// Figure out how to test without crashing (Maybe can't test Chess.cpp, but only Classes by including the .h file?)
		bool moveOne(char* board, int indexFrom, int indexTo) 
		{
			if (board[indexTo] == ' ' && board[indexFrom] != ' ')
			{
				board[indexTo] = board[indexFrom];
				board[indexFrom] = ' ';
				return true;
			}
			return false;
		}

		void insertPieceOne(Piece* board[], Piece insert) {
			board[insert.getCurrentPosition().getRow()][insert.getCurrentPosition().getCol()] = insert;
		}
		
		/*void displayBoard(Piece* board[])
		{
			string spacing = "    ";
			for (int r = 0; r < NUM_ROW; r++)
			{
				for (int c = 0; c < NUM_COL; c++)
				{
					cerr << board[r][c].getType() << spacing;
				}
				cerr << endl;
			}
		}*/

		TEST_METHOD(TestingInsert)
		{
			Piece* starting_board[8][8] = {
			{&Space(RC(0, 0)), &Space(RC(0, 1)), &Space(RC(0, 2)), &Space(RC(0, 3)), &Space(RC(0, 4)), &Space(RC(0, 5)), &Space(RC(0, 6)), &Space(RC(0, 7))},
			{&Space(RC(1, 0)), &King(RC(1, 1), 0), &Space(RC(1, 2)), &Space(RC(1, 3)), &Space(RC(1, 4)), &Space(RC(1, 5)), &Space(RC(1, 6)), &Space(RC(1, 7))},
			{&Space(RC(2, 0)), &Space(RC(2, 1)), &Space(RC(2, 2)), &Space(RC(2, 3)), &Space(RC(2, 4)), &Space(RC(2, 5)), &Space(RC(2, 6)), &Space(RC(2, 7))},
			{&Space(RC(3, 0)), &Space(RC(3, 1)), &Space(RC(3, 2)), &Space(RC(3, 3)), &Space(RC(3, 4)), &Space(RC(3, 5)), &Space(RC(3, 6)), &Space(RC(3, 7))},
			{&Space(RC(4, 0)), &Space(RC(4, 1)), &Space(RC(4, 2)), &Space(RC(4, 3)), &Space(RC(4, 4)), &Space(RC(4, 5)), &Space(RC(4, 6)), &Space(RC(4, 7))},
			{&Space(RC(5, 0)), &Space(RC(5, 1)), &Space(RC(5, 2)), &Space(RC(5, 3)), &Space(RC(5, 4)), &Space(RC(5, 5)), &Space(RC(5, 6)), &Space(RC(5, 7))},
			{&Space(RC(6, 0)), &Space(RC(6, 1)), &Space(RC(6, 2)), &Space(RC(6, 3)), &Space(RC(6, 4)), &Space(RC(6, 5)), &Space(RC(6, 6)), &Space(RC(6, 7))},
			{&Space(RC(7, 0)), &Space(RC(7, 1)), &Space(RC(7, 2)), &Space(RC(7, 3)), &Space(RC(7, 4)), &Space(RC(7, 5)), &Space(RC(7, 6)), &Space(RC(7, 7))} };

			insertPieceOne(*starting_board, King(RC(1, 1), 1));

			//displayBoard(*starting_board);
		};
	
	};
}
