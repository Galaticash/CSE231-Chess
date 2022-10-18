/***********************************************************************
 * Source File:
 *      CHESS
 * Authors:
 *      Ashley DeMott and Logan Huston 
 * Description: 
 *      Plays the game of chess, showing the user the possible 
 *      Moves of the Pieces they click on. Will not show possible
 *      Moves for a Piece if it is not their turn.
 ************************************************************************/
/**********************************************************************
 * GL Demo
 * Just a simple program to demonstrate how to create an Open GL window, 
 * draw something on the window, and accept simple user input
 **********************************************************************/
#pragma once

#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for draw*
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
using namespace std;

#ifndef BOARD_CLASS // The Board Class
#define BOARD_CLASS
#include "board.h"
#endif

#ifndef PIECE_CLASSES   // All the children classes of Piece, included in Board
#define PIECE_CLASSES
#include "Pawn.h"
#include "Queen.h"
#include "Space.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#endif

// The Teams that Pieces can be assigned to
// Used to determine if a Piece can be moved (incomplete)
const bool TEAM_ONE = 1;
const bool TEAM_TWO = 0;

// For testing castling, replace Bishop -> Queen with spaces (Team Black)
// new Bishop(RC(7, 1), TEAM_TWO), new Knight(RC(7, 2), TEAM_TWO), new Queen(RC(7, 3), TEAM_TWO) 
// new Space(RC(7, 1)), new Space(RC(7, 2)), new Space(RC(7, 3))

/*********************************************************
 * GET POSITION
 * Calculates the int position from an RC position
 *********************************************************/
int getPosition(RC rcPos)
{
    int position = rcPos.getRow() * 8 + rcPos.getCol();
    return position;
}

/*********************************************************
 * GET RC
 * Calculates the RC position from an int position
 *********************************************************/
RC getRC(int position)
{
    int row = position / 8;  // current location row
    int col = position % 8;  // current location column
    return RC(row, col);
}

/***************************************************
 * DRAW
 * Draw the current state of the game
 ***************************************************/
void draw(const Board* board, const Interface & ui, const set <Move> & possible)
{
   ogstream gout;
   
   // draw the checkerboard
   gout.drawBoard();

   // draw any selections
   gout.drawHover(ui.getHoverPosition());
   gout.drawSelected(ui.getSelectPosition());

   // draw the possible moves
   for (set <Move> ::iterator it = possible.begin(); it != possible.end(); ++it)
   {
       Move currentMove = *it;
       int position = getPosition(currentMove.getPositionTo());
       gout.drawPossible(position);
   }

   // Draw each Piece on the Board
   for (int r = 0; r < 8; r++)
   {
       for (int c = 0; c < 8; c++)
       {
           if (!(board->getPieceAtPosition(RC(r, c))->isSpace()))
           {
               Piece* drawMe = board->getPieceAtPosition(RC(r, c));
                   //board[r][c]; // NOTE: const override isn't working
               char type = drawMe->getType();
               gout.drawPiece(drawMe);
           }
       }
   }
}

/*************************************
 *  CALLBACK
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface *pUI, void * p)
{
    set <Move> possible;

    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    Board* board = (Board*)p;

    // ** MOVE **
    Move currentMove = Move();

    RC prevPos = getRC(pUI->getPreviousPosition());
    RC selectPos = getRC(pUI->getSelectPosition());

    // If the Previous Position is a valid space on the Board,
    if (board->isValidPosition(selectPos))
    {
        if (board->isValidPosition(prevPos) && prevPos != selectPos)
        {
            Piece* selectedPiece = board->getPieceAtPosition(prevPos);

            set <Move> prevPossible = selectedPiece->getPossibleMoves(board, board->getLastMove());
            //(*board)[prevPos.getRow()][prevPos.getCol()].getPossibleMoves(board, board->getLastMove()); // Board[] const broken

            // If the possible Moves set is not empty,
            if (prevPossible.begin() != prevPossible.end())
            {
                // For every Move in the set,
                for (set <Move> ::iterator it = prevPossible.begin(); it != prevPossible.end(); it++)
                {
                    // Look for the current Move (only comparing positionTo)
                    Move checkMove = *it;
                    if (checkMove.getPositionTo() == selectPos)
                    {
                        // That is the current Move to be performed
                        currentMove = checkMove;
                        break;
                    }
                }
            }

            // Get the previous Move performed
            Move lastMove = board->getLastMove();

            // If the current Move can be done, do it
            if (lastMove != board->move(currentMove))
            {
                // Then clear the selected position
                pUI->clearSelectPosition();
            }

            // Otherwise, update possible Moves to display
            else
            {
                Piece* selectedPiece = board->getPieceAtPosition(getRC(pUI->getSelectPosition()));
                possible = selectedPiece->getPossibleMoves(board, lastMove);
            }
        }
        else
        {
            // TODO: adjust logic so possible Moves only changed in one place
            Piece* selectedPiece = board->getPieceAtPosition(getRC(pUI->getSelectPosition()));
            possible = selectedPiece->getPossibleMoves(board, board->getLastMove());
        }

    }

    // If the user clicks on a space or a Piece belonging to the opposite of current Team
    if (pUI->getSelectPosition() != -1 && (board->getPieceAtPosition(getRC(pUI->getSelectPosition()))->isSpace() || board->currentIsWhite() != board->getPieceAtPosition(getRC(pUI->getSelectPosition()))->getIsWhite()))
        pUI->clearSelectPosition();

    // draw the board
    draw(board, *pUI, possible);
}

/********************************************************
 * PARSE
 * Determine the nature of the move based on the input.
 * This is the only function understanding Smith notation
 *******************************************************/
void parse(const string& textMove, int& positionFrom, int& positionTo)
{}

/********************************************************
 * READ FILE
 * Read a file where moves are encoded in Smith notation
 *******************************************************/
void readFile(const char* fileName, Board* board)
{
   // open the file
   ifstream fin(fileName);
   if (fin.fail())
      return;

   // read the file, one move at a time
   string textMove;
   bool valid = true;
   while (valid && fin >> textMove)
   {
       try
       {
           // Create a move from the Smith's notation
           Move nextMove = Move(textMove);
           // If no errors thrown, perform the move
           board->move(nextMove);
       }
       catch (string errorMessage)
       {
           cerr << errorMessage;
           valid = false; // Stop reading moves
       }
   }

   // close and done
   fin.close();
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv) 
// or char *argv[] <-- find the name of the executable created, argc is the number of parameters
#endif // !_WIN32
{
   Interface ui("Chess");   

   // The default Chess Board
   Piece* defaultBoard[NUM_ROW][NUM_COL] = {
               {new Rook(RC(0, 0), TEAM_ONE), new Bishop(RC(0, 1), TEAM_ONE), new Knight(RC(0, 2), TEAM_ONE), new Queen(RC(0, 3), TEAM_ONE), new King(RC(0, 4), TEAM_ONE), new Knight(RC(0, 5), TEAM_ONE), new Bishop(RC(0, 6), TEAM_ONE), new Rook(RC(0, 7), TEAM_ONE)},
               {new Pawn(RC(1, 0), TEAM_ONE), new Pawn(RC(1, 1), TEAM_ONE), new Pawn(RC(1, 2), TEAM_ONE), new Pawn(RC(1, 3), TEAM_ONE), new Pawn(RC(1, 4), TEAM_ONE), new Pawn(RC(1, 5), TEAM_ONE), new Pawn(RC(1, 6), TEAM_ONE),new Pawn(RC(1, 7), TEAM_ONE)},
               {new Space(RC(2, 0)), new Space(RC(2, 1)), new Space(RC(2, 2)), new Space(RC(2, 3)), new Space(RC(2, 4)), new Space(RC(2, 5)), new Space(RC(2, 6)), new Space(RC(2, 7))},
               {new Space(RC(3, 0)), new Space(RC(3, 1)), new Space(RC(3, 2)), new Space(RC(3, 3)), new Space(RC(3, 4)), new Space(RC(3, 5)), new Space(RC(3, 6)), new Space(RC(3, 7))},
               {new Space(RC(4, 0)), new Space(RC(4, 1)), new Space(RC(4, 2)), new Space(RC(4, 3)), new Space(RC(4, 4)), new Space(RC(4, 5)), new Space(RC(4, 6)), new Space(RC(4, 7))},
               {new Space(RC(5, 0)), new Space(RC(5, 1)), new Space(RC(5, 2)), new Space(RC(5, 3)), new Space(RC(5, 4)), new Space(RC(5, 5)), new Space(RC(5, 6)), new Space(RC(5, 7))},
               {new Pawn(RC(6, 0), TEAM_TWO), new Pawn(RC(6, 1), TEAM_TWO), new Pawn(RC(6, 2), TEAM_TWO), new Pawn(RC(6, 3), TEAM_TWO), new Pawn(RC(6, 4), TEAM_TWO), new Pawn(RC(6, 5), TEAM_TWO), new Pawn(RC(6, 6), TEAM_TWO), new Pawn(RC(6, 7), TEAM_TWO)},
               {new Rook(RC(7, 0), TEAM_TWO), new Bishop(RC(7, 1), TEAM_TWO), new Knight(RC(7, 2), TEAM_TWO), new Queen(RC(7, 3), TEAM_TWO), new King(RC(7, 4), TEAM_TWO), new Knight(RC(7, 5), TEAM_TWO), new Bishop(RC(7, 6), TEAM_TWO), new Rook(RC(7, 7), TEAM_TWO)} };


   // Initialize the game class
   // note this is upside down: 0 row is at the bottom
   Board board = Board(defaultBoard);
   
   // TEST: Move a Piece (also this will be done for readFile,
   //   but need to convert Smith's notation to Move first)
   Move test = Move(RC(6, 0), RC(5, 0));
   test.getSmithNotation();
   board.move(test);

#ifdef _WIN32
 //  int    argc;
 //  LPWSTR * argv = CommandLineToArgvW(GetCommandLineW(), &argc);
 //  string filename = argv[1];
   if (__argc == 2)
      readFile(__argv[1], &board);
#else // !_WIN32
   if (argc == 2)
      readFile(argv[1], board);
#endif // !_WIN32

   // set everything into action
   ui.run(callBack, &board);

   return 0;
}
