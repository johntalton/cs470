#include <iostream.h>
#include "../glcontrol.h" //Include the basics for adding this into OpenGL
#include "../globals.h"  // All global vars and functions
#include "../prog1/prog1.h"  //Include OUR old basic code
#include "../prog2/prog2.h"   // includ some of our primitive stuff
#include "prog3.h" // hope we get it all in there
int Animate = 1; // Use this to tell user whater we want to constanly redraw or not
#define PI  3.14159265359

  Point3D Vlist0[] = {   -10,  0,    0, //Xaxis
                          10,  0,    0,
                          0,   -10,  0, //Yaxis
                          0,    10,  0,
                          0,    0,   -10, //Zaxis
                          0,    0,    10
                     };
  Edge3D Elist0[] =  {    0, 1,
                          2, 3,
                          4, 5
                     };

  Point3D Centroid1= {    0,    0.333 ,   0 
                     };
  Point3D Vlist1[] = {   -1.0,  0.0,  1.0, //0
                          1.0,  0.0,  1.0, //1
                          1.0,  0.0, -1.0, //2
                         -1.0,  0.0, -1.0, //3
                          0.0,  1.0,  0.0  //4
                      };
   Edge3D Elist1[] =  {   0, 1, // This sets up a pritty pyramid
                          1, 2,
                          2, 3,
                          3, 0,
                          0, 4,
                          1, 4,
                          2, 4,
                          3, 4
                      };
   Point3D Centroid2= {   6,    1,    1 
                      };
   Point3D Vlist2[] = {   5.0,  0.0,  0.0, //0
                          7.0,  0.0,  0.0, //1
                          7.0,  0.0,  2.0, //2
                          5.0,  0.0,  2.0, //3
                          5.0,  2.0,  0.0, //4
                          7.0,  2.0,  0.0, //5
                          7.0,  2.0,  2.0,  //6
                          5.0,  2.0,  2.0 //7
                      };
   Edge3D Elist2[] =  {   0, 1, //bottom
                          1, 2,
                          2, 3,
                          3, 0,
                          4, 5, //top
                          5, 6,
                          6, 7,
                          7, 4,
                          0, 4, //sides
                          1, 5,
                          2, 6,
                          3, 7
                       };

double t = 0;
Point3D O = { 0, 4, -5.4}; 
Point3D R = { 0, 0, 0}; 
Point3D V = { 0, 1, 0 };
Point3D newVlist1[10];
Point3D newVlist2[10];
/**************************************************************************
*   DrawScene
*      This is our function that is called on draw. This is really the 
*      only thing that neads to be in here. 
*   @param void
*   @return void
**************************************************************************/
void DrawScene()
{
   if(t < 4*PI){ // spin around twice
      O.x = 17 * sin(t);
      O.z = -17 * cos(t);
      t =  t + .01;
   }else{       // and then zoom out Z axis if neg toward user
      O.z = O.z - 0.5;
   }
    
   ViewPoint(O, R,V);

   if(axison){
      setColor(0.4,0.4,0.4);
      Draw3DPoly(Vlist0,Elist0,6,3);
   }

   setColor(1,0,0);
   //Scale(Vlist1,5,Centroid1,30,newVlist1); 
   Draw3DPoly(Vlist1,Elist1,5,8);
   //Ortho(newVlist1,Elist1,5,8);
     
   setColor(0,1,0);
   //Scale(Vlist2,8,Centroid2,30,newVlist2);
   Draw3DPoly(Vlist2,Elist2,8,12);
   //Ortho(newVlist2,Elist2,8,12);
}