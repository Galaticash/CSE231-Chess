/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32


#include "uiDraw.h"
#include "uiInteract.h"

using namespace std;

// pieces: black and white
const int RGB_WHITE[] = { 255, 255, 255 };
const int RGB_BLACK[] = { 0, 0, 0 };

// normal squares: tan and brown
const int RGB_WHITE_SQUARE[] = { 210, 200, 170 };
const int RGB_BLACK_SQUARE[] = { 120, 100, 40 };

// the color of a selected square
const int RGB_SELECTED[] = { 256, 0, 0 };

/*************************************************************************
 * DISPLAY the text in the buffer on the screen
 *************************************************************************/
void ogstream::flush()
{
    string sOut;
    string sIn = str();

    // copy everything but the newlines
    for (string::iterator it = sIn.begin(); it != sIn.end(); ++it)
        // newline triggers an buffer flush and a move down
        if (*it == '\n')
        {
            drawText(x, y, sOut.c_str());
            sOut.clear();
            x -= 10;
        }
    // othewise append
        else
            sOut += *it;

    // put the text on the screen
    if (!sOut.empty())
    {
        drawText(x, y, sOut.c_str());
        x -= 10;
    }

    // reset the buffer
    str("");
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void ogstream::drawText(int x, int y, const char* text) const
{
    void* pFont = GLUT_TEXT;

    // prepare to draw the text from the top-left corner
    glRasterPos2f((GLfloat)x, (GLfloat)y);

    // loop through the text
    for (const char* p = text; *p; p++)
        glutBitmapCharacter(pFont, *p);
}

/************************************************************************
* GL COLOR
* Set the color on the board
*   INPUT  rgb  RGB color in integers (0...255)
*************************************************************************/
void glColor(const int * rgb)
{
   glColor3f((GLfloat)(rgb[0] / 256.0), 
             (GLfloat)(rgb[1] / 256.0),
             (GLfloat)(rgb[2] / 256.0));
}

/************************************************************************
* DRAW Piece
* Draw a piece at a certain location on the board
*   INPUT  Piece* p     A pointer to the Piece being drawn
*************************************************************************/
void ogstream::drawPiece(Piece* p) const
{   
    // Get the color and rectangles from the Piece
    bool black = !(p->getIsWhite());
    vector<Rect> rectangles = *(p->getRectangles());

    // Get the x, y position of the Piece (x = col, y = row)
    int x = (p->getCurrentPosition().getCol()) * 32;
    int y = (p->getCurrentPosition().getRow()) * 32;

    GLint xGL = (GLint)(x + 16 /* half a square width */);
    GLint yGL = (GLint)(y + 16 /* half a square height*/);

   // get ready to draw
   glBegin(GL_QUADS);
   glColor(black ? RGB_BLACK : RGB_WHITE);
   
   // For every rectangle in the vector,
   for (int i = 0; i < rectangles.size(); i++)
   {
       // The current Rectangle being drawn
       Rect currentRect = rectangles[i];

       // Draw every point
       glVertex2i(xGL + currentRect.x0, yGL + currentRect.y0);
       glVertex2i(xGL + currentRect.x1, yGL + currentRect.y1);
       glVertex2i(xGL + currentRect.x2, yGL + currentRect.y2);
       glVertex2i(xGL + currentRect.x3, yGL + currentRect.y3);
   }

   // finish the drawing
   glEnd();
}

/************************************************************************
* DRAW BOARD
* Draw the chess board
************************************************************************/
void ogstream::drawBoard()
{
   // get ready to draw
   glBegin(GL_QUADS);

   for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
      {
         // set the checker-board color
         if ((row + col) % 2 == 0)
            glColor(RGB_BLACK_SQUARE);
         else
            glColor(RGB_WHITE_SQUARE);

         // draw the square
         glVertex2i((GLint)((col + 0) * 32 + 1), 
                    (GLint)((row + 0) * 32 + 1));
         glVertex2i((GLint)((col + 1) * 32 - 1),
                    (GLint)((row + 0) * 32 + 1));
         glVertex2i((GLint)((col + 1) * 32 - 1),
                    (GLint)((row + 1) * 32 - 1));
         glVertex2i((GLint)((col + 0) * 32 + 1),
                    (GLint)((row + 1) * 32 - 1));
      }

   // done
   glEnd();
}

/************************************************************************
* DRAW SELECTED
* Highlight a chess square:
*   INPUT  location  The location of the selected square
************************************************************************/
void ogstream::drawSelected(int pos)
{
   // do nothing if there is nothing to do
   if (pos < 0 && pos >= 64)
      return;

   // find the row and column
   int row = pos / 8;
   int col = pos % 8;

   // set the color and drawing style
   glBegin(GL_QUADS);
   glColor(RGB_SELECTED);

   // draw the square
   glVertex2i((GLint)((col + 0) * 32  + 3),
              (GLint)((row + 0) * 32 + 3));
   glVertex2i((GLint)((col + 1) * 32  - 3),
              (GLint)((row + 0) * 32 + 3));
   glVertex2i((GLint)((col + 1) * 32  - 3),
              (GLint)((row + 1) * 32 - 3));
   glVertex2i((GLint)((col + 0) * 32  + 3),
              (GLint)((row + 1) * 32 - 3));

   // indicate we are finished
   glEnd();
}

/************************************************************************
* DRAW HOVER
* Highlight a chess square:
*   INPUT  location  The location of the selected square
************************************************************************/
void ogstream::drawHover(int pos)
{
   // do nothing if there is nothing to do
   if (pos < 0 || pos >= 64)
      return;

   // find the row and column
   int row = pos / 8;
   int col = pos % 8;

   // set the color and drawing style
   glBegin(GL_QUADS);
   glColor(RGB_SELECTED);

   // draw the square
   glVertex2i((GLint)((col + 0) * 32),
              (GLint)((row + 0) * 32));
   glVertex2i((GLint)((col + 1) * 32),
              (GLint)((row + 0) * 32));
   glVertex2i((GLint)((col + 1) * 32),
              (GLint)((row + 1) * 32));
   glVertex2i((GLint)((col + 0) * 32),
              (GLint)((row + 1) * 32));

   // set the checker-board color
   if ((row + col) % 2 == 0)
      glColor(RGB_BLACK_SQUARE);
   else
      glColor(RGB_WHITE_SQUARE);

   // draw the square
   glVertex2i((GLint)((col + 0) * 32 + 2),
              (GLint)((row + 0) * 32 + 2));
   glVertex2i((GLint)((col + 1) * 32 - 2),
              (GLint)((row + 0) * 32 + 2));
   glVertex2i((GLint)((col + 1) * 32 - 2),
              (GLint)((row + 1) * 32 - 2));
   glVertex2i((GLint)((col + 0) * 32 + 2),
              (GLint)((row + 1) * 32 - 2));

   // finish the drawing
   glEnd();
}

/************************************************************************
* DRAW POSSIBLE
* Highlight a chess square:
*   INPUT  location  The location of the selected square
************************************************************************/
void ogstream::drawPossible(RC rc)
{
   // do nothing if there is nothing to do
    if (rc.getRow() < 0 || rc.getRow() > 7 || rc.getCol() < 0 || rc.getCol() > 7)
    {
        return;
    }

   // find the row and column
    int row = rc.getRow();
       //pos / 8;
    int col = rc.getCol();
       //pos % 8;

   // set the color and drawing style
   glBegin(GL_QUADS);
   glColor(RGB_SELECTED);

   // draw the square
   glVertex2i((GLint)((col + 0) * 32 + 7),
              (GLint)((row + 0) * 32 + 7));
   glVertex2i((GLint)((col + 1) * 32 - 7),
              (GLint)((row + 0) * 32 + 7));
   glVertex2i((GLint)((col + 1) * 32 - 7),
              (GLint)((row + 1) * 32 - 7));
   glVertex2i((GLint)((col + 0) * 32 + 7),
              (GLint)((row + 1) * 32 - 7));

   // finish the drawing
   glEnd();
}
