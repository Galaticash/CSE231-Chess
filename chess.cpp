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

#ifndef BOARD_CLASS
#define BOARD_CLASS
#include "board.h"
#endif

#ifndef PIECE_CLASSES
#define PIECE_CLASSES
#include "Pawn.h"
#include "Queen.h"
#include "Space.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#endif

Piece* DEFAULT_BOARD[NUM_ROW][NUM_COL] = {
            {new Rook(RC(0, 0), 0), new Bishop(RC(0, 1), 0), new Knight(RC(0, 2), 0), new Queen(RC(0, 3), 0), new King(RC(0, 4), 0), new Knight(RC(0, 5), 0), new Bishop(RC(0, 6), 0), new Rook(RC(0, 7), 0)},
            {new Pawn(RC(1, 0), 0), new Pawn(RC(1, 1), 0), new Pawn(RC(1, 2), 0), new Pawn(RC(1, 3), 0), new Pawn(RC(1, 4), 0), new Pawn(RC(1, 5), 0), new Pawn(RC(1, 6), 0),new Pawn(RC(1, 7), 0)},
            {new Space(RC(2, 0)), new Space(RC(2, 1)), new Space(RC(2, 2)), new Space(RC(2, 3)), new Space(RC(2, 4)), new Space(RC(2, 5)), new Space(RC(2, 6)), new Space(RC(2, 7))},
            {new Space(RC(3, 0)), new Space(RC(3, 1)), new Space(RC(3, 2)), new Space(RC(3, 3)), new Space(RC(3, 4)), new Space(RC(3, 5)), new Space(RC(3, 6)), new Space(RC(3, 7))},
            {new Space(RC(4, 0)), new Space(RC(4, 1)), new Space(RC(4, 2)), new Space(RC(4, 3)), new Space(RC(4, 4)), new Space(RC(4, 5)), new Space(RC(4, 6)), new Space(RC(4, 7))},
            {new Space(RC(5, 0)), new Space(RC(5, 1)), new Space(RC(5, 2)), new Space(RC(5, 3)), new Space(RC(5, 4)), new Space(RC(5, 5)), new Space(RC(5, 6)), new Space(RC(5, 7))},
            {new Pawn(RC(6, 0), 1), new Pawn(RC(6, 1), 1), new Pawn(RC(6, 2), 1), new Pawn(RC(6, 3), 1), new Pawn(RC(6, 4), 1), new Pawn(RC(6, 5), 1), new Pawn(RC(6, 6), 1), new Pawn(RC(6, 7), 1)},
            {new Rook(RC(7, 0), 1), new Bishop(RC(7, 1), 1), new Knight(RC(7, 2), 1), new Queen(RC(7, 3), 1), new King(RC(7, 4), 1), new Knight(RC(7, 5), 1), new Bishop(RC(7, 6), 1), new Rook(RC(7, 7), 1)} };


int getPosition(RC rcPos)
{
    int location = rcPos.getRow() * 8 + rcPos.getCol();
    return location;
}

RC getRC(int location)
{
    int row = location / 8;  // current location row
    int col = location % 8;  // current location column
    return RC(row, col);
}


/*********************************************************
 * GET POSSIBLE MOVES
 * Determine all the possible moves for a given chess piece
 *********************************************************/
set <int> getPossibleMoves(const char* board, int location)
{
   set <int> possible;

   // return the empty set if there simply are no possible moves
   if (location < 0 || location >= 64 || board[location] == ' ')
      return possible;
   int row = location / 8;  // current location row
   int col = location % 8;  // current location column
   int r;                   // the row we are checking
   int c;                   // the column we are checking
   bool amBlack;

   // board[index] --> Piece/None
   // IF piece:
   //   possible = piece.getMoves() --> RC/integer (index)
   // return possible
   
   return possible;
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

/*********************************************
 * MOVE 
 * Execute one movement. Return TRUE if successful
 *********************************************/
// NOTE: Functionality move to Board class
/*bool move(char* board, int positionFrom, int positionTo)
{
   // do not move if a move was not indicated
   if (positionFrom == -1 || positionTo == -1)
      return false;
   assert(positionFrom >= 0 && positionFrom < 64);
   assert(positionTo >= 0 && positionTo < 64);

   // find the set of possible moves from our current location
   // Find the Piece on the board
   // Piece movePiece =  board[previous.row][previous.col]
   // set <RC> possiblePrevious = movePiece.getPossibleMoves(board)
   set <int> possiblePrevious = getPossibleMoves(board, positionFrom);

   // only move there is the suggested move is on the set of possible moves
   if (possiblePrevious.find(positionTo) != possiblePrevious.end())
   {
      // board[positionTo.row][positionFrom.row] = board[positionFrom.row][positionRow.row]
      board[positionTo] = board[positionFrom];
      board[positionFrom] = ' ';

      // hasMoved = True OR nMoves ++
      return true;
   }

   return false;
}*/

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
    // Do the move that the user selected on the visual board
    // Find a move that has positionTo == positionClicked
    // Get the Move that has PosTo = position clicked
    Move currentMove = Move();

    RC prevPos = getRC(pUI->getPreviousPosition());
    RC selectPos = getRC(pUI->getSelectPosition());

    // If the Previous Position is a valid space on the Board,
    if (board->isValidPosition(prevPos))
    {
        Piece* selectedPiece = board->getPieceAtPosition(prevPos);

        set <Move> prevPossible = selectedPiece->getPossibleMoves(board, board->getLastMove());
        //(*board)[prevPos.getRow()][prevPos.getCol()].getPossibleMoves(board, board->getLastMove()); // Board[] const broken

        // If Move.positionTo == Move in possibleMoves
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

        // Get the last Move performed
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
            possible = board->getPieceAtPosition(getRC(pUI->getSelectPosition()))->getPossibleMoves(board, lastMove);
        }
    }
    // Rearrange, this is so the first click works
    else if(board->isValidPosition(selectPos))
    {
        possible = board->getPieceAtPosition(getRC(pUI->getSelectPosition()))->getPossibleMoves(board, board->getLastMove());
    }


    if (pUI->getSelectPosition() != -1 && board->getPieceAtPosition(getRC(pUI->getSelectPosition()))->isSpace())
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
{
   string::const_iterator it = textMove.cbegin();

   // get the source
   int col = *it - 'a';
   it++;
   int row = *it - '1';
   it++;
   positionFrom = row * 8 + col;

   // get the destination
   col = *it - 'a';
   it++;
   row = *it - '1';
   it++;
   positionTo = row * 8 + col;

   // capture and promotion information
   char capture = ' ';
   char piecePromotion = ' ';
   bool castleK = false;
   bool castleQ = false;
   bool enpassant = false;
   for (; it != textMove.end(); ++it)
   {
      switch (*it)
      {
      case 'p':   // capture a pawn
      case 'n':   // capture a knight
      case 'b':   // capture a bishop
      case 'r':   // capture a rook
      case 'q':   // capture a queen
      case 'k':   // !! you can't capture a king you silly!
         capture = tolower(*it);
         break;

      case 'c':  // short castling or king's castle
         castleK = true;
         break;
      case 'C':  // long castling or queen's castle
         castleQ = true;
         break;
      case 'E':  // En-passant
         enpassant = true;
         break;

      case 'N':  // Promote to knight
      case 'B':  // Promote to Bishop
      case 'R':  // Promote to Rook
      case 'Q':  // Promote to Queen
         piecePromotion = *it;
         break;

      }
   }

   // error checking
   if (positionFrom < 0 || positionFrom >= 64 ||
       positionTo   < 0 || positionTo   >= 64)
      positionFrom = positionTo = -1;
}

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
      int positionFrom;
      int positionTo;
      parse(textMove, positionFrom, positionTo);
      //valid = move(board, positionFrom, positionTo);
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

   // Initialize the game class
   // note this is upside down: 0 row is at the bottom
   Board board = Board(DEFAULT_BOARD);
   
   // TEST: Move a Piece,
   //board.move(Move(RC(6, 0), RC(5, 0)));


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
