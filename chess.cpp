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

/***********************************************
 * Row Column
 * Simple row/column pair
 ************************************************/
struct RC
{
   int row;
   int col;
};

/****************************************************
 * IS NOT WHITE
 * Is the current location valid and the piece is either
 * black (uppercase) or space
 ***************************************************/
inline bool isNotWhite(const char* board, int row, int col)
{
   // not white if we are off the board or if we are looking at a space
   if (row < 0 || row >= 8 || col < 0 || col >= 8)
      return false;
   char piece = board[row * 8 + col];

   return piece == ' ' || (piece >= 'A' && piece <= 'Z');
}

/****************************************************
 * IS  WHITE
 * Is the current location valid and the piece is white
 ***************************************************/
inline bool isWhite(const char* board, int row, int col)
{
   // not white if we are off the board or if we are looking at a space
   if (row < 0 || row >= 8 || col < 0 || col >= 8)
      return false;
   char piece = board[row * 8 + col];

   return (piece >= 'a' && piece <= 'z');
}

/****************************************************
 * IS NOT BLACK
 * Is the current location valid and the piece is either
 * white (lowercase) or space
 ***************************************************/
inline bool isNotBlack(const char* board, int row, int col)
{
   // not white if we are off the board or if we are looking at a space
   if (row < 0 || row >= 8 || col < 0 || col >= 8)
      return false;
   char piece = board[row * 8 + col];

   return piece == ' ' || (piece >= 'a' && piece <= 'z');
}

/****************************************************
 * IS  BLACK
 * Is the current location valid and the piece is black
 ***************************************************/
inline bool isBlack(const char* board, int row, int col)
{
   // not white if we are off the board or if we are looking at a space
   if (row < 0 || row >= 8 || col < 0 || col >= 8)
      return false;
   char piece = board[row * 8 + col];

   return (piece >= 'A' && piece <= 'Z');
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
   bool amBlack = isBlack(board, row, col);

   // board[index] --> Piece/None
   // IF piece:
   //   possible = piece.getMoves() --> RC/integer (index)
   // return possible

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

   //
   // KNIGHT
   //
   if (board[location] == 'N' || board[location] == 'n')
   {
      RC moves[8] = 
      {
               {-1,  2}, { 1,  2},
      {-2,  1},                    { 2,  1},
      {-2, -1},                    { 2, -1},
               {-1, -2}, { 1, -2}
      };
      for (int i = 0; i < 8; i++)
      {
         r = row + moves[i].row;
         c = col + moves[i].col;
         if ( amBlack && isNotBlack(board, r, c))
            possible.insert(r * 8 + c);
         if (!amBlack && isNotWhite(board, r, c))
            possible.insert(r * 8 + c);
      }
   }

   //
   // KING
   //
   if (board[location] == 'K' || board[location] == 'k')
   {
      // posible deltas, changes in position
      RC moves[8] =
      {
         {-1,  1}, {0,  1}, {1,  1},
         {-1,  0},          {1,  0},
         {-1, -1}, {0, -1}, {1, -1}
      };
      for (int i = 0; i < 8; i++)
      {
         r = row + moves[i].row;
         c = col + moves[i].col;
         if ( amBlack && isNotBlack(board, r, c))
            possible.insert(r * 8 + c);
         if (!amBlack && isNotWhite(board, r, c))
            possible.insert(r * 8 + c);
      }
      // what about castling?
   }

   //
   // QUEEN
   //
   if (board[location] == 'Q' || board[location] == 'q')
   {
      RC moves[8] =
      {
         {-1,  1}, {0,  1}, {1,  1},
         {-1,  0},          {1,  0},
         {-1, -1}, {0, -1}, {1, -1}
      };
      for (int i = 0; i < 8; i++)
      {
         r = row + moves[i].row;
         c = col + moves[i].col;
         while (r >= 0 && r < 8 && c >= 0 && c < 8 && 
                board[r * 8 + c] == ' ')
         {
            possible.insert(r * 8 + c);
            r += moves[i].row;
            c += moves[i].col;
         }
         if ( amBlack && isNotBlack(board, r, c))
            possible.insert(r * 8 + c);
         if (!amBlack && isNotWhite(board, r, c))
            possible.insert(r * 8 + c);
      }
   }

   //
   // ROOK
   //
   if (board[location] == 'R' || board[location] == 'r')
   {
      RC moves[4] =
      {
                  {0,  1},
         {-1, 0},         {1, 0},
                  {0, -1}
      };
      for (int i = 0; i < 4; i++)
      {
         r = row + moves[i].row;
         c = col + moves[i].col;
         while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
            board[r * 8 + c] == ' ')
         {
            possible.insert(r * 8 + c);
            r += moves[i].row;
            c += moves[i].col;
         }
         if (amBlack && isNotBlack(board, r, c))
            possible.insert(r * 8 + c);
         if (!amBlack && isNotWhite(board, r, c))
            possible.insert(r * 8 + c);
      }
   }

   //
   // BISHOP
   //
   if (board[location] == 'B' || board[location] == 'b')
   {
      RC moves[4] =
      {
         {-1,  1}, {1,  1},
         {-1, -1}, {1, -1}
      };
      for (int i = 0; i < 4; i++)
      {
         r = row + moves[i].row;
         c = col + moves[i].col;
         while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
            board[r * 8 + c] == ' ')
         {
            possible.insert(r * 8 + c);
            r += moves[i].row;
            c += moves[i].col;
         }
         if (amBlack && isNotBlack(board, r, c))
            possible.insert(r * 8 + c);
         if (!amBlack && isNotWhite(board, r, c))
            possible.insert(r * 8 + c);
      }
   }
   
   return possible;
}

/***************************************************
 * DRAW
 * Draw the current state of the game
 ***************************************************/
void draw(const char* board, const Interface & ui, const set <int> & possible)
{
   ogstream gout;
   
   // draw the checkerboard
   gout.drawBoard();

   // draw any selections
   gout.drawHover(ui.getHoverPosition());
   gout.drawSelected(ui.getSelectPosition());

   // draw the possible moves
   set <int> :: iterator it;
   for (it = possible.begin(); it != possible.end(); ++it)
      gout.drawPossible(*it);


   // Note: Draw needs positions x,y instead of Row Columns, translate

   // draw the pieces
   for (int i = 0; i < 64; i++)
      switch (board[i])
      {
      case 'P':
         gout.drawPawn(i, true);
         break;
      case 'p':
         gout.drawPawn(i, false);
         break;
      case 'K':
         gout.drawKing(i, true);
         break;
      case 'k':
         gout.drawKing(i, false);
         break;
      case 'Q':
         gout.drawQueen(i, true);
         break;
      case 'q':
         gout.drawQueen(i, false);
         break;
      case 'R':
         gout.drawRook(i, true);
         break;
      case 'r':
         gout.drawRook(i, false);
         break;
      case 'B':
         gout.drawBishop(i, true);
         break;
      case 'b':
         gout.drawBishop(i, false);
         break;
      case 'N':
         gout.drawKnight(i, true);
         break;
      case 'n':
         gout.drawKnight(i, false);
         break;
      }
}

/*********************************************
 * MOVE 
 * Execute one movement. Return TRUE if successful
 *********************************************/
bool move(char* board, int positionFrom, int positionTo)
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

}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface *pUI, void * p)
{
   set <int> possible;

   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   char * board = (char *)p;  

   // move 
   if (move(board, pUI->getPreviousPosition(), pUI->getSelectPosition()))
      pUI->clearSelectPosition();
   else
       // possible = (currentPiece).getPossibleMoves(board)
      possible = getPossibleMoves(board, pUI->getSelectPosition());

   // if we clicked on a blank spot, then it is not selected
   if (pUI->getSelectPosition() != -1 && board[pUI->getSelectPosition()] == ' ')
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
void readFile(const char* fileName, char* board)
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
      valid = move(board, positionFrom, positionTo);
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
   char board[64] = {
      'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
      'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      // ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
      'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
   };

   // char board[8][8] = {}

   // pieces board[64] None

   // Piece's position: board[0] --> board[16]
   
   // pieces -> King, Pawn, Queens
   // moveset


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
