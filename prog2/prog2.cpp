#include "../glcontrol.h" //Include the basics for adding this into OpenGL
#include "../globals.h"
#include "../prog1/prog1.h"  //Include OUR old basic code
#include "prog2.h"   // this is what we are now makeing
#include <math.h>
int Animate = TRUE; // Use this to tell user whater we want to constanly redraw or not
/**************************************************************************
*   DrawScene
*      This is our function that is called on draw. This is really the 
*      only thing that neads to be in here. 
*   @param void
*   @return void
**************************************************************************/
void DrawScene()
{  
   Point2 p0[10],p1[10];
   int x;
   
   p0[0].x = 40;//80.3;
   p0[0].y = 58.8;
   p0[1].x = 101.6;
   p0[1].y = 71.9;
   p0[2].x = -10;//93.6
   p0[2].y = -10;//25.2
   p0[3].x = 147.7;
   p0[3].y = 45.1;

   setColor(0.0,0.0,1.0);
   polyfill(4,p0);
   setColor(1.0,1.0,0.0);
   polygon(4,p0); 
   
   setClipWindow(5,5,100,100);
   polyclip(4,p0,x,p1);
   gradfillFrom(1.0,0.0,0.0);
   gradfillTo(1.0,1.0,0.0);
   polyfillgrad(x,p1);
   
}