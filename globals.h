/**************************************************************************
*   Draw routines for my graphis packedge.
*      ¥NöP's Graphics Package Global vars
*      This is all the global vars that I have used
*      in all my progs
*   TODO
*
*   HISTORY
*      
*
*   @version 1.0
*   @author YNOP,jta001@coes.latech.edu,ynop@acm.org
*   @copyright 1998,1999 The Abstract Company
**************************************************************************/  
#include <math.h>
/**************************************************************************
*   Added for ver1.0
**************************************************************************/  
void horizLine(int x1,int x2, int y);
void bestFitLine(int x1, int y1, int x2, int y2);
void simpleDDALine(int x1, int y1, int x2, int y2);
void bresLine(int x1, int y1, int x2, int y2);
void parameterCircle(int x, int y, int r);
void spiralDDACircle(int x, int y, int r);
void bresCircle(int x, int y, int r);
/**************************************************************************
*   Added for ver2.0
**************************************************************************/  
char aganstxy;  // the axis we are curently cliping against. used internally not user var
char GorL;      // whether we are cliping to the left or right of the cliping line. non-user
int  boundry;   // the value of the cliping line. Users should not change the valuse
typedef struct{ // this is how we are going to store points in our polygon .. damn float
   float x;
   float y;
} Point2;
int ClipWindowX1 = -400; //our initial values for the cliping window is the size
int ClipWindowY1 = -400; //   of the drawing space
int ClipWindowX2 =  400;
int ClipWindowY2 =  400;
typedef struct{   // Struct of Edges for polyfill
   float x;      // the ever changeing x that we find
   float ymax;   // that edges max
   float ymin;   // that edges min
   float dx;     // sloap of each edge
} Edge;
 // This is colors we use for a Gradient Polygon fill
float GradfromR = 1;  // We set the fill form white to black
float GradfromG = 1;  //    for our init.
float GradfromB = 1;
float GradtoR = 0;
float GradtoG = 0;
float GradtoB = 0;   // last Gradient fill var
// this is the colors we use for gradient filling a line
float horizGradfromR = 1;  // We set the fill form white to black
float horizGradfromG = 1;  //    for our init.
float horizGradfromB = 1;
float horizGradtoR = 0;
float horizGradtoG = 0;
float horizGradtoB = 0;   // last Gradient fill var

void polygon(const int numPoints, const Point2 p[]);
void polyfill(const int numPoints, const Point2 p[]);
void polyclip(const int numPoints, const Point2 p[], int & numResult, Point2 results[]);
void setClipWindow(int x1,int y1, int x2, int y2);
void gradfillFrom(float R,float G,float B);
void gradfillTo(float R,float G,float B);
void polyfillgrad(const int numPoints, const Point2 p[]);
void horizLinegrad(int x1,int x2, int y);
void horizgradfillFrom(float R,float G,float B);
void horizgradfillTo(float R,float G,float B);
void tripolyfill(const int numPoints, Point2 p[]);
/**************************************************************************
*   Added for ver3.0
**************************************************************************/  
typedef struct{ //a 3D point
   double x;
   double y;
   double z;
} Point3D;

typedef struct{ // a line from on 3Dp ot another 3Dp
   int P1;
   int P2;
} Edge3D;

double realscale = 1; // a post scaling factor (1 is good)
double d = 300;  /// our D used for depth transform
Point3D thisO = { 0,0,0 };
Point3D thisR = { 0,0,0 };
Point3D thisV = { 0,1,0 };

void Draw3DPoly(Point3D Vlist[], Edge3D Elist[], int numVert, int numEdges);
void Ortho(Point3D Vlist[], Edge3D Elist[],int numVert, int numEdges);
void Ortho(Point3D Vlist[], Edge3D Elist[],int numVert, int numEdges, int Scale);
void ViewPoint(int Sx, int Sy, int Sz, int Dx, int Dy, int Dz);
void Rotation(Point3D Vlist[], Edge3D Elist[], int numVert, int numEdges,Point3D VlistOUT[]);
/**************************************************************************
*   Added for ver4.0
**************************************************************************/  
#define MAXTRI 100
int WIREFRAME = 0; // bool, draw as wireframe model?
typedef struct{ // a line from on 3Dp ot another 3Dp
   int P1;
   int P2;
   int P3;
   int isBackFace;
   int isOverLap;
   float R, G ,B;
} Plane3D;

typedef struct{
   int frontlist[MAXTRI];
   int behind;
} PaintersNode;

PaintersNode PaintersData[MAXTRI];


double Max3(double a,double b,double c){
   double t;
   if (a > b){ t = a; }else{ t = b; }
   if (t > c){ return t; }else{ return c; }
  
}
double Min3(double a,double b,double c){
   double t;
   if (a < b){ t = a; }else{ t = b; }
   if (t < c){ return t; }else{ return c; }
}



void polyfill3D(Point3D Vlist1[], int numPoints, Plane3D Plist1[],int numPlains);
void removeBackFaces(Point3D Vlist[], int numPoints, Plane3D Pln[], int numPlanes);
void DepthSort(Point3D Vlist[], Plane3D Plist[], int numVert,int numPlanes);
void PaintersAlg(Point3D Vlist[], Plane3D Plist[], int numVert,int numPlanes);
void CheesySort(Point3D Vlist[], Plane3D Plist[], int numVert,int numPlanes);
