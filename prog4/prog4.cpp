#include "../glchaos.h" //Include the basics for adding this into OpenGL
#include "../globals.h"  // Any and every global var used by my graphics package
#include "../prog1/prog1.h"  //Include OUR old basic code
#include "../prog2/prog2.h"   // includ some of our primitive stuff
#include "../prog3/prog3.h"  // Include our 3d libs and stuff
#include "prog4.h" // this issuse
int Animate = 1; // Use this to tell user whater we want to constanly redraw or not
int Chaos = 1;
//#define PI  3.14159265359 or atam(1) use biult in stuff is good :)

/*
   Al's phone :  255-7014
   Al's pager :  689-7626
*/

long double PI =  4*atan(1);

  Point3D Vlist0[] = {   -10,   0,   0, //Xaxis
                          10,   0,   0,
                           0, -10,   0, //Yaxis
                           0,  10,   0,
                           0,   0, -10, //Zaxis
                           0,   0,  10
                     };
  Edge3D Elist0[] =  {    0, 1,
                          2, 3,
                          4, 5
                     };
 
 
 
  Point3D Vlist1[] = {   -1.0,  0.0,  1.0, //0
                          1.0,  0.0,  1.0, //1
                          1.0,  0.0, -1.0, //2
                         -1.0,  0.0, -1.0, //3
                          0.0,  1.41, 0.0, //4
                          0.0, -1.41, 0.0,  //5
                        
                          5.0,  0.0,  0.0, //0
                          7.0,  0.0,  0.0, //1
                          7.0,  0.0,  2.0, //2
                          5.0,  0.0,  2.0, //3
                          5.0,  2.0,  0.0, //4
                          7.0,  2.0,  0.0, //5
                          7.0,  2.0,  2.0, //6
                          5.0,  2.0,  2.0  //7
                      };
                      
   Plane3D Plist1[] = {  //0, 1, 2,
                         //0, 2, 3,
                         0, 1, 4, 0, 1, 0, 0, 1,
                         1, 2, 4, 0, 1, 1, 1, 0,
                         2, 3, 4, 0, 1, 0, 0, 1,
                         3, 0, 4, 0, 1, 1, 1, 0,
                         
                         1, 0, 5, 0, 1, 1, 1, 0,
                         2, 1, 5, 0, 1, 0, 0, 1,
                         3, 2, 5, 0, 1, 1, 1, 0,
                         0, 3, 5, 0, 1, 0, 0, 1,
                      
                         6, 7, 8, 0, 1, 1, 1, 1, // Bottom
                         9, 6, 8, 0, 1, 1, 1, 1,

                         10, 12, 11, 0, 1, 1, 1, 1, // Top
                         10, 13, 12, 0, 1, 1, 1, 1,
     
                         6, 10, 11, 0, 1, 0.5, 0, 1, // Front
                         7, 6,  11, 0, 1, 0.5, 0, 1,

                         11, 12, 8, 0, 1, 0.5, 0, 0, // Rigth
                         8,  7,  11, 0, 1, 0.5, 0, 0,

                         12, 9,  8, 0, 1, 0.5, 0, 1, // Back
                         12, 13, 9, 0, 1, 0.5, 0, 1,

                         13, 10, 9, 0, 1, 0.5, 0, 0, // Left
                         10, 6,  9, 0, 1, 0.5, 0, 0
                      };                      
  

double t = 0;
int r = 10;
Point3D O = { 0, 3, r }; 
Point3D R = { 0, 0, 0 }; 
Point3D V = { 0, 1, 0 };
Point3D newVlist1[10];
Point3D newVlist2[10];
Point2 tempPoint2[4];
Point3D ResultVlist[5];
/**************************************************************************
*   DrawScene
*      This is our function that is called on draw. This is really the 
*      only thing that neads to be in here. 
*   @param void
*   @return void
**************************************************************************/
void DrawScene()
{
   WIREFRAME = 0;//setto wireframe model
   O.x =  r * sin(t);
   O.z = -r * cos(t);
   t =  t + .007;
   if(t > (2*PI)) {t = 0; }

   ViewPoint(O, R,V);

   if(axison){
      setColor(0.4,0.4,0.4);
      Draw3DPoly(Vlist0,Elist0,6,3);
   }
      
   Draw3DPoly(Vlist1,Plist1,14,20);
}