#include "../glcontrol.h" //Include the basics for adding this into OpenGL

#include "prog1.h"

int Animate = FALSE; // Use this to tell user whater we want to constanly redraw or not

int Chaos = 1; // this is part of the choas graphics package

/**************************************************************************

*   DrawScene

*      This is our function that is called on draw. This is really the

*      only thing that neads to be in here.

*

*   John Talton

*   prog1 cs470 1/6/99

*

*   @param void

*   @return void

**************************************************************************/

void DrawScene()

{



   bestFitLine(0,20,400,100);



   setColor(1.0,1.0,0.0);

   //bestFitLine(10,0,41,25);

   pixPlot(41,25);



   setColor(1.0,1.0,0.0);

   bresLine(10,20,-30,-5); // OK

   bresLine(-30,-5,10,20); // OK



   setColor(0.0,1.0,0.0);

   bestFitLine(-30,-5,-25,150); // OK

   bestFitLine(-25,150,-30,-5); // NOTOK****



   setColor(0.0,1.0,1.0);

   bestFitLine(10,150,-25,150); //  OK

   setColor(1.0,0.0,0.0);

   bestFitLine(-25,150,10,150); // OK



   setColor(1.0,0.5,0.5);

   bestFitLine(10,150,10,20); //OK

   bresLine(10,20,10,150); //OK



   setColor(1.0,0.0,0.0);

   bestFitLine(-10,-10,-50,-50); //OK

   bestFitLine(10,-10,50,-50);

   bestFitLine(10,10,50,50);

   bestFitLine(-10,10,-50,50);



   setColor(0.0,1.0,0.0);

   bestFitLine(150,50,50,50);

   bresLine(-150,50,-50,50);

   bestFitLine(150,-50,50,-50);

   bestFitLine(-150,-50,-50,-50);



   setColor(1.0,1.0,0.0);

   bestFitLine(50,50,50,150); //ok

   bestFitLine(-50,50,-50,150);

   bresLine(50,-50,50,-150);

   bestFitLine(-50,-50,-50,-150);



   setColor(1.0,0.0,0.0);

   bestFitLine(50,150,150,50);

   bestFitLine(-50,150,-150,50);

   bestFitLine(50,-150,150,-50);

   bestFitLine(-50,-150,-150,-50);





   bestFitLine(-50,50,20,-10);  //OK

   bestFitLine(20,-10,-50,50);



   setColor(0.0,0.0,1.0);

   bestFitLine(0,0,50,50);

   setColor(0.0,1.0,0.0);

   bestFitLine(10,-10,-50,50);



   setColor(1.0, 1.0, 1.0);

   bresCircle(50,50,10);

   spiralDDACircle(-50,50,10);

   parameterCircle(50,-50,10);

   spiralDDACircle(-50,-50,10);



   parameterCircle(50,50,200);



}
