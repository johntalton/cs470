#include <GL/glut.h>
#include <iostream.h>
#include <stdlib.h>
extern Chaos;
extern Animate;
void DrawScene();
/**************************************************************************
*   OpenGL
*      Basic GLUT app. This is my header file that take care of all the GL
*      stuff. you can include it in any C++ file and put you draw routines
*      the DrawScene. DrawScene is the only function you nead int you C++
*      file. You do not even nead a main. (matter of fact if you put a main
*      in you C++ file it will not work!) So there you go. Oh I also packed
*      up pixPlot for you. it has a c(color) value but that does not get user
*      will fix that later. This is my chaos extention header .. it is the 
*      same as the glcontrol header it just has to ability to become chaotic.
*      The higher the chaos vaule is the less like what you picture is soposed 
*      to be will be renderd.  Its a lot of fun if you animate it and change
*      some values around.
*     
*     This is what a minimum cpp file should have in it (prog0.cpp): 
*
*     |  #include "../glcontrol.h"  
*     |  int Animate = FALSE;
*     |  int Chaos   = 1;
*     |
*     |  void DrawScene(){
*     |     //setBackGround(0.0,0.0,0.0); // will work soon
*     |     setColor(1.0,0.0,0.0);
*     |     pixPlot(10,20);
*     |     pixPlot(10,-20);
*     |     pixPlot(-10,20);
*     |     pixPlot(10,50);
*     |     pixPlot(-20,20);
*     |     pixPlot(40,30);
*     |     pixPlot(50,-20);
*     |     pixPlot(10,60);
*     |     pixPlot(-10,110);
*     |  }
*
*   TODO
*      Clean up code.
*      Put in more comments. 
*      Fix the pixPlot color thingy.
*   @version 1.1  - all Chaos vertions are the same as glcontrols but end in .1
*   @author YNOP,jta001@coes.latech.edu
**************************************************************************/  
typedef enum { NONE,QUIT,AXIS,ZIN,ZOUT,ZSTD,RDRAW,FULLS } DisplayLists; // Global callback defs
GLenum doubleBuffer;  // ? are wie doubleBuffering ?
GLint windW = 400, windH = 400; // The original hight of our window
int axison = GL_TRUE;  // are we displaying the axis
int Zfactor = 0; // this is the amount we are soomed in or out
float bgr = 0.0, bgg = 0.0, bgb = 0.0; // Global backgroud color 
float fgr = 1.0, fgg = 1.0, fgb = 1.0;  // global forgraoud (draw) color
/**************************************************************************
*   pixPlot 
*       plot a pixel on our screen at the x,y position and thats all
*   @param int x is the x value
*   @param int y is our y value
*   @param int c is the color we want it in. but dont use it. dumb huh
*   @return void
**************************************************************************/
inline void pixPlot(int x, int y, int c)
{ 
   switch(c){
      case 0: glColor3f(0.0, 0.0, 0.0);break;
      case 1: glColor3f(1.0, 0.0, 0.0);break;
      case 2: glColor3f(0.0, 1.0, 0.0);break;
      case 3: glColor3f(1.0, 1.0, 0.0);break;
	   case 4: glColor3f(0.0, 0.0, 1.0);break;
   	case 5: glColor3f(1.0, 0.0, 1.0);break;
      case 6: glColor3f(0.0, 1.0, 1.0);break;
      case 7: glColor3f(1.0, 1.0, 1.0);break;
   }
   glBegin(GL_POINTS);  // this is my little code here
      glVertex2i( x, y );
   glEnd();
   glColor3f(fgr,fgg,fgb);
}
/**************************************************************************
*   pixPlot 
*       plot a pixel on our screen at the x,y position and thats all
*   @param int x is the x value
*   @param int y is our y value
*   @return void
**************************************************************************/
inline void pixPlot(int x, int y){
   glBegin(GL_POINTS);
      glVertex2i(x + (rand() % Chaos) - Chaos / 2 -1,y + (rand() % Chaos) - Chaos / 2 -1);
   glEnd();
}
/**************************************************************************
*   setColor
*   @param float r is the amount of red
*   @param float g is the amount of green
*   @param float b is the amount of black.. no no blue
*   @return void
**************************************************************************/
inline void setColor(float r, float g, float b){ glColor3f(r,g,b);fgr=r; fgg=g; fgb=b; }
/**************************************************************************
*   getColor
*   @param float r is the amount of red
*   @param float g is the amount of green
*   @param float b is the amount of black.. no no blue
*   @return void
**************************************************************************/
inline void getColor(float &r, float &g, float &b){ r=fgr; g=fgg; b=fgb; }
/**************************************************************************
*   Menu - callback
*   @param int item is the menu item we selected
*   @return void
**************************************************************************/
void Menu(int item)
{
   switch (item){
   case AXIS :
      axison = !axison;
      glutPostRedisplay();
      break;
   case ZIN:
      Zfactor -= 50;
      glutPostRedisplay();
      break;
   case ZOUT:
      Zfactor += 50;
      glutPostRedisplay();
      break;
   case ZSTD:
      Zfactor = 0;
      glutPostRedisplay();
      break;
   case RDRAW:
      glutPostRedisplay();
      break;
   case FULLS:
      glutFullScreen();
      break;
   case QUIT :
      exit(0);
      break;
   }
}
/**************************************************************************
*   Key - callback
*   @param unsigned char key is the scan code for the key we hit
*   @param int x
*   @param int y
*   @return void
**************************************************************************/
static void Key(unsigned char key, int x, int y)
{  
   switch (key) {
      case 27: // Esc key
         Menu(QUIT);
         break;
      case '+':
         Menu(ZIN);
         break;
      case '-':
         Menu(ZOUT);
         break;
      case 8:  // BackSpace
         Menu(ZSTD);
         break;
   }
}
/**************************************************************************
*   Reshape - callback
*   @param int width is the new width of the window
*   @param int height is the new - you gessed it - height of the widow
*   @return void
**************************************************************************/
static void Reshape(int width, int height)
{
    windW = width;
    windH = height;
}
/**************************************************************************
*   Draw 
*   @param void
*   @return void
**************************************************************************/
static void Draw(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-windW/2, windW/2, -windH/2, windH/2, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
   glPushAttrib(GL_COLOR_BUFFER_BIT);
      glColorMask(1, 1, 1, 1);
      glIndexMask(~0);
      glClearColor(0.0, 0.0, 0.0, 0.0);
      glClear(GL_COLOR_BUFFER_BIT);
   glPopAttrib();
   glShadeModel(GL_SMOOTH); // GL_FLAT
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL
   glViewport(Zfactor, Zfactor, windW-(2*Zfactor), windH-(2*Zfactor));
   //////////////////////////
   //// Draw code here //////
   //////////////////////////
   //This is a cheasy way of seting our background color
   /*glBegin(GL_POLYGON);
         glColor3f(bgr, bgg, bgb);  // the color we want
         glVertex2i(-windW/2,-windH/2);
         glVertex2i(windW/2,-windH/2);
         glVertex2i(windW/2,windH/2);
         glVertex2i(-windW/2,windH/2);
   glEnd();*/   

  /* if(axison){ // Draw the axis throught the center in prity blue :)
      glBegin(GL_LINES);
         glColor3f(0.0, 0.0, 1.0);
         glVertex2i(0,-windH/2);
         glVertex2i(0,windH/2);
         glVertex2i(-windW/2,0);
         glVertex2i(windW/2, 0);
      glEnd();
   }*/
   glColor3f(fgr,fgg,fgb);
   ////////////////////////////
   DrawScene(); // My Draw Functions
   ///////////////////////////
   if (doubleBuffer) {
	   glutSwapBuffers();
   } else {
	   glFlush();
   }
}
/**************************************************************************
*   main
*
*   @param int argc is the num of arguments passed on the command line
*   @param char **argv is the array of strings that ARE the paramiters
*   @return void
**************************************************************************/
void main(int argc, char **argv)
{
   GLenum type;
   int submenu1;
   int window;
   GLint i;
    
   glutInit(&argc, argv);
   //Handle all the command line pramiters
   doubleBuffer = GL_TRUE; // Make double Buffered by default
   for (i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-sb") == 0) {
	      doubleBuffer = GL_FALSE;
         cout << "double Buffering off\n" << flush;
      } else if (strcmp(argv[i], "-db") == 0) {
	      doubleBuffer = GL_TRUE;
         cout << "double Buffering on\n" << flush;
      }
   }
   // Set up the window with pramiters and return window
   type = GLUT_RGB; //GLUT_INDEX;
   type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
   glutInitDisplayMode(type);
   glutInitWindowSize(windW, windH);
   window = glutCreateWindow("¥NöP's OpenGL Chaos v1.1");
   // Extra suff to add in my own menu and submenu 
   submenu1 = glutCreateMenu(Menu);
   glutAddMenuEntry("In", ZIN);
   glutAddMenuEntry("Out", ZOUT);
   glutAddMenuEntry("Standard", ZSTD);
   glutCreateMenu(Menu);
   //glutAddMenuEntry("¥NöP's Demo", NONE);
   glutAddMenuEntry("´¯`·.¸¸.·´¯`·.¸¸.·´¯`", NONE);
   glutAddMenuEntry("Toggle Axis", AXIS);
  // glutAddMenuEntry("ReDraw",RDRAW);
 //  glutAddSubMenu("Zoom",submenu1);
   glutAddMenuEntry("FullScreen", FULLS);
   glutAddMenuEntry("´¯`·.¸¸.·´¯`·.¸¸.·´¯`", NONE);
   glutAddMenuEntry("Quit", QUIT);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   // Add in all of our callbacks.. this is cool stuff here.
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Key);
   glutDisplayFunc(Draw);
   if(Animate){ glutIdleFunc(Draw); }
   glutMainLoop();
}
