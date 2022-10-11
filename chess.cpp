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


#include "board.h"
#include "Pawn.h"
#include "Queen.h"
#include "Space.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"

/***********************************************
 * Row Column
 * Simple row/column pair
 ************************************************/

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
   for (set <Move> ::iterator it = possible.begin(); it != possible.end(); it++)
   {
       Move currentMove = *it;
       gout.drawPossible(getPosition(currentMove.getPositionTo()));
   }

   // Draw each Piece on the Board
   /*for (int r = 0; r < 8; r++)
   {
       for (int c = 0; c < 8; c++)
       {
           if (!(board)[r][c]->isSpace())
           {
               gout.drawPiece(board[r][c]);
           }
       }
   }*/
}


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
   Board * board = (Board *)p; 

   Board pieceBoard = Board();

   // ** MOVE **
   // Do the move that the user selected on the visual board
   //pieceBoard.move();

   //if(pieceBoard.move()))

   //if (move(board, pUI->getPreviousPosition(), pUI->getSelectPosition()))
   //    pUI->clearSelectPosition();
   //else
       // possible = (currentPiece).getPossibleMoves(board)
       // possible = {};
       //getPossibleMoves(board, pUI->getSelectPosition());

   // if we clicked on a blank spot, then it is not selected
   RC selectPos = getRC(pUI->getSelectPosition());
   if (pUI->getSelectPosition() != -1 && (*board)[selectPos.getRow()][selectPos.getCol()]->getType() == 's')
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
void readFile(const char* fileName, Board board)
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
      //valid = move(board, positionFrom, positionTo); ***
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
   Board board = Board();

#ifdef _WIN32
 //  int    argc;
 //  LPWSTR * argv = CommandLineToArgvW(GetCommandLineW(), &argc);
 //  string filename = argv[1];
   if (__argc == 2)
      readFile(__argv[1], board);
#else // !_WIN32
   if (argc == 2)
      readFile(argv[1], board);
#endif // !_WIN32

   // set everything into action
   ui.run(callBack, board);             

   return 0;
}
