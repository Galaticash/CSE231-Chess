/*********************************************
 * Header file:
 *    UI INTERFACE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This module will create an OpenGL window,
 *    enter the OpenGL main loop, and accept events.
 *    The main methods are:
 *    1. Constructors - Create the window
 *    2. run()        - Run the main loop
 *    3. callback     - Specified in Run, this user-provided
 *                      function will get called with every frame
 *    4. isDown()     - Is a given key pressed on this loop?
 **********************************************/

#pragma once


/********************************************
 * INTERFACE
 * All the data necessary to keep our graphics
 * state in memory
 ********************************************/
class Interface
{
public:
   Interface() {}
   // Constructor if you want to set up the window with anything but
   // the default parameters
   Interface(const char* title)
   {
      initialize(title);
   }

   // This will set the game in motion
   void run(void (*callBack)(Interface*, void*), void* p);

   // Is it time to redraw the screen
   bool isTimeToDraw();

   // Set the next draw time based on current time and time period
   void setNextDrawTime();

   // Retrieve the next tick time... the time of the next draw.
   unsigned long getNextTick() { return nextTick; };

   // How many frames per second are we configured for?
   void setFramesPerSecond(double value);

   // Current frame rate
   double frameRate() const { return timePeriod; };

   // find the size of one square on the chess board
   double getSquareWidth() const
   {
      return (double)widthScreen / 8.0;
   }
   double getSquareHeight() const
   {
      return (double)heightScreen / 8.0;
   }
   void setScreen(int width, int height)
   {
      widthScreen = width;
      heightScreen = height;
   }
   
   int positionFromXY(int x, int y) const
   {
      int col =     (int)((double)x / getSquareWidth());
      int row = 7 - (int)((double)y / getSquareHeight());
      return (col >= 0 && col < 8 && row >= 0 && row < 8) ? row * 8 + col : -1;
   }
   
   int  getSelectPosition()   const { return posSelect; }
   int  getHoverPosition()    const { return posHover; }
   int  getPreviousPosition() const { return posSelectPrevious; }

   void setSelectPosition(int pos)
   {
      if (pos != posSelect)
         posSelectPrevious = posSelect;
      posSelect = pos;
   }
   void clearSelectPosition()
   {
      posSelectPrevious = -1;
      posSelect = -1;
   }
   void clearPreviousPosition()
   {
      posSelectPrevious = -1;
   }

   void setHoverPosition(int pos)
   {
      posHover = pos;
   }

   static void* p;                   // for client
   static void (*callBack)(Interface*, void*);

private:
   void initialize(const char* title);

   static bool         initialized;  // only run the constructor once!
   static double       timePeriod;   // interval between frame draws
   static unsigned long nextTick;     // time (from clock()) of our next draw

   static int  posHover;          // mouse hover position in chess coordinates
   static int  posSelect;         // mouse clicked position in chess coordinates
   static int  posSelectPrevious; // previous clicked position
   
   static int widthScreen;
   static int heightScreen;
};

/************************************************************************
 * RUN
 * Set the game in action.  We will get control back in our drawCallback
 *************************************************************************/
void run();

/***********************************
 * X FROM POSITION
 * Determine the x location of an item from
 * the chess board position
 ***********************************/
int xFromPosition(int position);
int yFromPosition(int position);
