/***********************************************************************
 * Source File:
 *     UI INTERACT
 * Author:
 *     Br. Helfrich
 * Description:
 *     Implement the interfaces specified in uiInterface.h.  This handles
 *     all the interfaces and events necessary to work with OpenGL.  Your
 *     program will interface with this thorough the callback function
 *     pointer towards the bottom of the file.
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock
#include <cstdlib>    // for rand()


#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>    // Main OpenGL library
#include <GL/glut.h>  // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <Gl/glut.h>           // OpenGL library we copied
#include <ctime>            // for ::Sleep();
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "uiInteract.h"

using namespace std;

/***********************************
 * X FROM POSITION
 * Determine the x location of an item from
 * the chess board position
 ***********************************/
int xFromPosition(int position)
{
   return (int)((double)(position % 8) * 32.0);
}
int yFromPosition(int position)
{
   return (int)((double)(position / 8) * 32.0);
}

/*********************************************************************
 * SLEEP
 * Pause for a while.  We want to put the program to sleep until it
 * is time to draw again.  Note that this requires us to tell the OS
 * that we are idle.  the nanosleep function performs this task for us
 *   INPUT: msSleep: sleep time in milliseconds
 *********************************************************************/
void sleep(unsigned long msSleep)
{
   // Windows handles sleep one way
#ifdef _WIN32
   ::Sleep(msSleep + 35);

   // Unix-based operating systems (OS-X, Linux) do it another
#else // LINUX, XCODE
   timespec req = {};
   time_t sec = (int)(msSleep / 1000);
   msSleep -= (sec * 1000);

   req.tv_sec = sec;
   req.tv_nsec = msSleep * 1000000L;

   while (nanosleep(&req, &req) == -1)
      ;
#endif // LINUX, XCODE
   return;
}

/************************************************************************
 * DRAW CALLBACK
 * This is the main callback from OpenGL. It gets called constantly by
 * the graphics engine to refresh and draw the window.  Here we will
 * clear the background buffer, draw on it, and send it to the forefront
 * when the appropriate time period has passsed.
 *
 * Note: This and all other callbacks can't be member functions, they must
 * have global scope for OpenGL to see them.
 *************************************************************************/
void drawCallback()
{
   // even though this is a local variable, all the members are static
   Interface ui;
   // Prepare the background buffer for drawing
   glClear(GL_COLOR_BUFFER_BIT); //clear the screen
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   
   //calls the client's display function
   assert(ui.callBack != NULL);
   ui.callBack(&ui, ui.p);
   
   //loop until the timer runs out
   if (!ui.isTimeToDraw())
      sleep((unsigned long)((ui.getNextTick() - clock()) / 1000));

   // from this point, set the next draw time
   ui.setNextDrawTime();

   // bring forth the background buffer
   glutSwapBuffers();
}

/************************************************************************
 * CLICK CALLBACK
 * When the user has clicked the mouse
 *   INPUT   button:   the mouse button we selected
 *           state:    the state of the button (down, up, etc)
 *           x,y:      coordinates of the mouse at click
 *************************************************************************/
void clickCallback(int button, int state, int x, int y)
{
   // determine what to do if the button is selected
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      // Even though this is a local variable, all the members are static
      // so we are actually getting the same version as in the constructor.
      Interface ui;

      // get coordinates from screen dimensions
      int pos = ui.positionFromXY(x, y);
      
      // if the current cell is selected, then deselect it
      if (ui.getSelectPosition() == pos)
         ui.clearSelectPosition();
      else
         ui.setSelectPosition(pos);
   }
}

/************************************************************************
 * MOVE CALLBACK
 * When the user has clicked the mouse
 *   INPUT   x,y:      coordinates of the mouse at click
 *************************************************************************/
void moveCallback(int x, int y)
{
   // Even though this is a local variable, all the members are static
   // so we are actually getting the same version as in the constructor.
   Interface ui;

   // get coordinates from screen dimensions
   int pos = ui.positionFromXY(x, y);

   ui.setHoverPosition(pos);
}

/************************************************************************
 * RESIZE CALLBACK
 * When the user has clicked the mouse
 *   INPUT   x,y:      coordinates of the mouse at click
 *************************************************************************/
void resizeCallback(int width, int height)
{
    // Even though this is a local variable, the square_width and square_height
    // member variables are static.
    Interface ui;
    ui.setScreen(width, height);

    glViewport(0, 0, width, height);
}

/************************************************************************
 * CLOSE CALLBACK
 * Get the close button to appear so we can exit
 *************************************************************************/
void closeCallback()
{
   exit(0);
}

/************************************************************************
 * INTEFACE : IS TIME TO DRAW
 * Have we waited long enough to draw swap the background buffer with
 * the foreground buffer?
 *************************************************************************/
bool Interface::isTimeToDraw()
{
   return ((unsigned int)clock() >= nextTick);
}

/************************************************************************
 * INTERFACE : SET NEXT DRAW TIME
 * What time should we draw the buffer again?  This is a function of
 * the current time and the frames per second.
 *************************************************************************/
void Interface::setNextDrawTime()
{
   nextTick = clock() + static_cast<unsigned long> (timePeriod * CLOCKS_PER_SEC);
}

/************************************************************************
 * INTERFACE : SET FRAMES PER SECOND
 * The frames per second dictates the speed of the game.  The more frames
 * per second, the quicker the game will appear to the user.  We will default
 * to 30 frames/second but the client can set this at will.
 *    INPUT  value        The number of frames per second.  5 is default
 *************************************************************************/
void Interface::setFramesPerSecond(double value)
{
    timePeriod = (1.0 / value);
}

/***************************************************
 * STATICS
 * All the static member variables need to be initialized
 * Somewhere globally.  This is a good spot
 **************************************************/
int      Interface::posHover = -1;
int      Interface::posSelect = -1;
int      Interface::posSelectPrevious = -1;
int      Interface::widthScreen = 32 * 8;
int      Interface::heightScreen = 32 * 8;

bool          Interface::initialized   = false;
double        Interface::timePeriod    = 0.2; // default to 5 frames/second
unsigned long Interface::nextTick      = 0;        // redraw now please
void *        Interface::p             = NULL;
void (*Interface::callBack)(Interface *, void *) = NULL;

/************************************************************************
 * INTEFACE : INITIALIZE
 * Initialize our drawing window.  This will set the size and position,
 * get ready for drawing, set up the colors, and everything else ready to
 * draw the window.  All these are part of initializing Open GL.
 *  INPUT    argc:       Count of command-line arguments from main
 *           argv:       The actual command-line parameters
 *           title:      The text for the titlebar of the window
 *************************************************************************/
void Interface::initialize(const char * title)
{
   if (initialized)
      return;
   
   // set up the random number generator
   srand((unsigned int)time(NULL));

   // create the window
   int argc = 0;
   glutInit(&argc, NULL);
   glutInitWindowSize(8 * 32 - 1, 8 * 32 - 1);   // size of the window
            
   glutInitWindowPosition( 10, 10);                // initial position 
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // double buffering
   glutCreateWindow(title);                        // text on titlebar
   glutIgnoreKeyRepeat(true);
   
   // set up the drawing style: B/W and 2D
   glClearColor(0,0,0, 0);                   // Black is the background color
   gluOrtho2D((GLdouble)0.0, (GLdouble)(widthScreen),
              (GLdouble)0.0, (GLdouble)(heightScreen));
   glutReshapeWindow(widthScreen, heightScreen);

   // register the callbacks so OpenGL knows how to call us
   glutDisplayFunc(      drawCallback    );
   glutIdleFunc(         drawCallback    );
   glutMouseFunc(        clickCallback   );
   glutPassiveMotionFunc(moveCallback    );
   glutReshapeFunc(      resizeCallback  );
#ifdef __APPLE__
   glutWMCloseFunc(      closeCallback   );
#endif 
   initialized = true;
   
   // done
   return;
}

/************************************************************************
 * INTERFACE : RUN
 *            Start the main graphics loop and play the game
 * INPUT callBack:   Callback function.  Every time we are beginning
 *                   to draw a new frame, we first callback to the client
 *                   to see if he wants to do anything, such as move
 *                   the game pieces or respond to input
 *       p:          Void point to whatever the caller wants.  You
 *                   will need to cast this back to your own data
 *                   type before using it.
 *************************************************************************/
void Interface::run(void (*callBack)(Interface *, void *), void *p)
{
   // setup the callbacks
   this->p = p;
   this->callBack = callBack;

   glutMainLoop();

   return;
}

