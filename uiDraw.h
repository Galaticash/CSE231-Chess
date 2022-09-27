/***********************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. ogstream works
 *    much like COUT except it also has some convenient methods for
 *    drawing chess pieces on the screen.
 ************************************************************************/

#pragma once

#include <sstream>    // for OSTRINGSTRING
using std::string;

 /*************************************************************************
  * GRAPHICS STREAM
  * A graphics stream that behaves much like COUT except on a drawn screen.
  * Special methods are added to facilitate drawing simulator elements.
  *************************************************************************/
class ogstream : public std::ostringstream
{
public:
    ogstream() : x(0), y(0)                  {          }
    ogstream(int position): x(0), y(0)       {          }
    ~ogstream()                              { flush(); }

    // Methods specific to drawing text on the screen
    virtual void flush();
    void setPosition(int x, int y) { flush(); this->x = x; this->y = y;}


    // Methods to draw the chess pieces on the screen
    virtual void drawKing(  int position, bool black);
    virtual void drawQueen( int position, bool black);
    virtual void drawRook(  int position, bool black);
    virtual void drawPawn(  int position, bool black);
    virtual void drawBishop(int position, bool black);
    virtual void drawKnight(int position, bool black);

    // Methods to draw the board 
    virtual void drawBoard();
    virtual void drawSelected(int position);
    virtual void drawHover(   int position);
    virtual void drawPossible(int position);

protected:
    int x; // location of text on the screen
    int y;

private:
    // One rectangle, for drawing pieces.
    struct Rect
    {
        int x0;
        int y0;
        int x1;
        int y1;
        int x2;
        int y2;
        int x3;
        int y3;
    };
   
    // Draw a piece with a collection of rectangles
    void drawPiece(int x, int y, bool black, Rect rectangle[], int num) const;

    // Put text at location X, Y
    void drawText(int x, int y, const char* text) const;
};
