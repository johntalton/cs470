#include <math.h>
/**************************************************************************
*   Draw routines for my graphis packedge.
*      ¥NöP's Graphics Package
*      This was originaly wirten for my cs470 graphics classs.
*      it is not verry usefull for much else but it is good
*      for learning the basics about how the primitive graphics
*      work.
*   TODO
*      fix some stuff.. make look nice doc's and all
*   HISTORY
*      ver2.0.9 - Upgrading all programs that depend on this.
*      ver2.0.8 - devising a new method for assigning color to a point
*      ver2.0.7 - colors are off. negation problem
*      ver2.0.6 - fixed Sort. Work finally. all tri's fill correctal
*      ver2.0.5 - workged on sort more and fixed grad fill problem
*      ver2.0.4 - finished tri fill
*      ver2.0.3 - re-started on trifill. new algorithm (only triangls)
*      ver2.0.2 - started work on tri gradiant fill of polygons
*      ver2.0.1 - added a horizontal gradiant fill line
*      ver2.0 - polygon stuff finished
*      ver1.9 - polyfillgrad,gradFrom,gradTo - for Gradient poly fill
*      ver1.8 - polygonfill finished - cleaned up
*      ver1.7 - some fixes like figured out < is not the same as <= in polyfill :)
*      ver1.4 - fixed polyclip's delete pointer problem
*      ver1.3 - Polygon cliping is in now :)
*      ver1.2 - Polygon drawing
*      ver1.1 - beging polygon representation
*      ver1.0 - Lines Complete.
*
*   @version 2.0.9
*   @author YNOP,jta001@coes.latech.edu,ynop@acm.org
*   @copyright 1998,1999 The Abstract Company
**************************************************************************/


/**************************************************************************
*   horizLine
*      this is a simple left to right hoizontal line drawing alg. it is 
*      suposed to be sort and sweat so that it runs fast as all for our
*      polygon fill - later.
*   @param int x1 is the left x value
*   @param int x2 is the right x value
*   @param int y is the y value or hight
*   @return void
**************************************************************************/
void horizLinegrad(int x1,int x2, int y){
   if(x2 < x1){ int t = x2; x2=x1;x1 = t;}
   int i;
   float Rstep = (horizGradtoR - horizGradfromR)  / (double)(x2 - x1),
         Gstep = (horizGradtoG - horizGradfromG)  / (double)(x2 - x1),
         Bstep = (horizGradtoB - horizGradfromB)  / (double)(x2 - x1);
   float curR = horizGradfromR,
         curG = horizGradfromG,
         curB = horizGradfromB;
   for(i = x1; i <= x2; i++){
      curR = curR+Rstep;
      curG = curG+Gstep; 
      curB = curB+Bstep;
      setColor(curR,curG,curB);
      pixPlot(i,y);
   }
}
/**************************************************************************
*   horizgradfillFrom
*      Sets the color to gradient fill form
*   @param int R is the red value to start with
*   @param int G is the green value to start with
*   @param int B is the blue value to start with
*   @return void
**************************************************************************/
void horizgradfillFrom(float R,float G,float B){
   horizGradfromR = R;
   horizGradfromG = G;
   horizGradfromB = B;
}
/**************************************************************************
*   horzgradfillTo
*      sets the color to fill to
*   @param int R is the red value to end with
*   @param int G is the green value to end with
*   @param int B is the blue value to end with
*   @return void
**************************************************************************/
void horizgradfillTo(float R,float G,float B){
   horizGradtoR = R;
   horizGradtoG = G;
   horizGradtoB = B;
}
/**************************************************************************
*   polygon
*      uses our wanderfull struct of point2 and our bresline from earyler.
*      it just makes you standard plolygon I gess :)
*   @param const int numPoints is the number of points in the polygon
*   @param const Point2 p[] is the array of struct point2 holding the points
*   @return void
**************************************************************************/
void polygon(const int numPoints, Point2 p[]){
   int i,j;
   for(i = 0; i < numPoints; i++){
      if(i==numPoints-1){ j = 0; }else { j = i+1; }
      bresLine(p[i].x,p[i].y,p[j].x,p[j].y);
   }
}
/**************************************************************************
*   Sort
*      Sorts a edge list by its y value - Basicly got this of the net
*      not a big deal, changed some things and all.. it is just a simple
*      Sort algorithm
*   @param int a[] is the list to sort
*   @param int len is the length of the list to sort
*   @return void
**************************************************************************/
void sort(int a[], int len) {
   for (int i = 1; i < len; i++) {
      int j = i;
      int B = a[i];
      while ((j > 0) && (a[j-1] > B)) {
         a[j] = a[j-1];
         j--;
      }
      a[j] = B;
   }
}
/**************************************************************************
*   polyfill
*      a prity good algorithm for fillen polys.. does prity good I gess
*   @param const int numPoints is the number of points in the polygon
*   @param const Point2 p[] is the array of struct point2 holding the points
*   @return void
**************************************************************************/
void polyfill(const int numPoints, const Point2 p[]){
   int y,i;
   float MinY = p[0].y,MaxY = p[0].y;
   float xmax;
   Edge *elist = new Edge[numPoints];

   for(i = 0;i < numPoints-1; i++){
      if(p[i].y > p[i+1].y){ elist[i].ymax = p[i].y; elist[i].ymin = p[i+1].y; xmax = p[i].x;}
      else { elist[i].ymax = p[i+1].y; elist[i].ymin = p[i].y; xmax = p[i+1].x;}

      if((p[i].y - p[i+1].y)!=0){elist[i].dx = -((p[i].x - p[i+1].x)/(p[i].y - p[i+1].y));} else { elist[i].dx = (p[i].x - p[i+1].x);}

      elist[i].x = xmax + -(elist[i].dx)*(ceil(elist[i].ymax)-elist[i].ymax);
      if(elist[i].ymin < MinY){ MinY = elist[i].ymin;}
      if(elist[i].ymax > MaxY){ MaxY = elist[i].ymax;}
   }

   if(p[i].y > p[0].y){ elist[i].ymax = p[i].y; elist[i].ymin = p[0].y; xmax = p[i].x;}
   else { elist[i].ymax = p[0].y; elist[i].ymin = p[i].y; xmax = p[0].x;}
   if((p[i].y - p[0].y)!=0){elist[i].dx = -((p[i].x - p[0].x)/(p[i].y - p[0].y));} else { elist[i].dx = (p[i].x - p[0].x);}
   elist[i].x = xmax + -(elist[i].dx)*(ceil(elist[i].ymax)-elist[i].ymax);
   if(elist[i].ymin < MinY){ MinY = elist[i].ymin;}
   if(elist[i].ymax > MaxY){ MaxY = elist[i].ymax;}

/*
   if(p[0].y > p[numPoints-1].y){ elist[i].ymax = p[0].y; elist[i].ymin = p[numPoints-1].y; xmax = p[0].x;}
   else { elist[0].ymax = p[numPoints-1].y; elist[i].ymin = p[0].y; xmax = p[numPoints-1].x;}
   if((p[0].y - p[numPoints-1].y)!=0){elist[i].dx = -((p[0].x - p[numPoints-1].x)/(p[0].y - p[numPoints-1].y));} else { elist[i].dx = (p[0].x - p[numPoints-1].x);}
   elist[i].x = xmax + -(elist[i].dx)*(ceil(elist[i].ymax)-elist[i].ymax);
*/
   //for( i=0;i<numPoints;i++){
  //    cout << elist[i].ymax << "  " << elist[i].ymin << "  " << elist[i].dx << "  " << elist[i].x << endl << flush;
  // } cout << endl << flush;
   for (i = 1; i < numPoints; i++) {// sort table by Y's
      int j = i;
      Edge temp = elist[i];
      while ((j > 0) && (elist[j-1].ymax < temp.ymax)) {
         elist[j] = elist[j-1];
         j--;
      }
      elist[j] = temp;
   } //end sort

  // for( i=0;i<numPoints;i++){
  //    cout << elist[i].ymax << "  " << elist[i].ymin << "  " << elist[i].dx << "  " << elist[i].x << endl << flush;
  // } cout << endl << flush;

   int Head = 0 ,Tail = 0,xcount;
   int *xlist = new int[numPoints];
  //cout << MaxY << "   " << MinY << endl << flush;
   for(y = ceil(MaxY)-1; y >= ceil(MinY); y--){
      xcount = 0;
      //cout  << y << endl << flush;
      while((Tail < numPoints)&&(elist[Tail].ymax > y)){ Tail++;}
      //cout << Tail << endl << flush;
      for(i = Head; i < Tail; i++){
         elist[i].x += elist[i].dx;
         if (elist[i].ymin <= y){ xlist[xcount] = elist[i].x; xcount++; }
         else{ elist[i] = elist[Head]; Head++; }
      }

      if(xcount&1){ // this is not really realevent now
         cout << "Critical ERROR: invalide param list for x-list: odd number" << endl << flush;
         cout << xcount << endl << flush;
         return;
      }

      sort(xlist,xcount);
      //cout << xcount << flush;
      //for(i = 0; i < xcount;i++){ cout << xlist[i] << " " << flush; } cout << endl << flush;
      for(i = 0;i < xcount;i+=2){ horizLine(xlist[i],xlist[i+1],y); }
      if(Head==Tail){break;}
   }
   delete elist;
   delete xlist;

}
/**************************************************************************
*   gradfillFrom
*      Sets the color to gradient fill form
*   @param int R is the red value to start with
*   @param int G is the green value to start with
*   @param int B is the blue value to start with
*   @return void
**************************************************************************/
void gradfillFrom(float R,float G,float B){
   GradfromR = R;
   GradfromG = G;
   GradfromB = B;
}
/**************************************************************************
*   gradfillTo
*      sets the color to fill to
*   @param int R is the red value to end with
*   @param int G is the green value to end with
*   @param int B is the blue value to end with
*   @return void
**************************************************************************/
void gradfillTo(float R,float G,float B){
   GradtoR = R;
   GradtoG = G;
   GradtoB = B;
}
/**************************************************************************
*   polyfillgrad
*      a prity good algorithm for fillen polys.. does prity good I gess
*   @param const int numPoints is the number of points in the polygon
*   @param const Point2 p[] is the array of struct point2 holding the points
*   @return void
**************************************************************************/
void polyfillgrad(const int numPoints, const Point2 p[]){
   int y,i;
   float MinY = p[0].y,MaxY = p[0].y;
   float xmax;
   Edge *elist = new Edge[numPoints];
   for(i = 0;i < numPoints-1; i++){
      if(p[i].y > p[i+1].y){ elist[i].ymax = p[i].y; elist[i].ymin = p[i+1].y; xmax = p[i].x;}
      else { elist[i].ymax = p[i+1].y; elist[i].ymin = p[i].y; xmax = p[i+1].x;}
      if((p[i].y - p[i+1].y)!=0){elist[i].dx = -((p[i].x - p[i+1].x)/(p[i].y - p[i+1].y));} else { elist[i].dx = (p[i].x - p[i+1].x);}
      elist[i].x = xmax + -(elist[i].dx)*(ceil(elist[i].ymax)-elist[i].ymax);
      if(elist[i].ymin < MinY){ MinY = elist[i].ymin;}
      if(elist[i].ymax > MaxY){ MaxY = elist[i].ymax;}
   }
   if(p[i].y > p[0].y){ elist[i].ymax = p[i].y; elist[i].ymin = p[0].y; xmax = p[i].x;}
   else { elist[i].ymax = p[0].y; elist[i].ymin = p[i].y; xmax = p[0].x;}
   if((p[i].y - p[0].y)!=0){elist[i].dx = -((p[i].x - p[0].x)/(p[i].y - p[0].y));} else { elist[i].dx = (p[i].x - p[0].x);}
   elist[i].x = xmax + -(elist[i].dx)*(ceil(elist[i].ymax)-elist[i].ymax);
   if(elist[i].ymin < MinY){ MinY = elist[i].ymin;}
   if(elist[i].ymax > MaxY){ MaxY = elist[i].ymax;}
   for (i = 1; i < numPoints; i++) { //start a sort by Ymax
      int j = i;
      Edge temp = elist[i];
      while ((j > 0) && (elist[j-1].ymax < temp.ymax)) {
         elist[j] = elist[j-1];
         j--;
      }
      elist[j] = temp;
   }        // end the sort
   int Head = 0 ,Tail = 0,xcount;
   int *xlist = new int[numPoints];
   float range = MaxY - MinY;
   float stepR = (GradtoR - GradfromR)/range,
         stepG = (GradtoG - GradfromG)/range,
         stepB = (GradtoB - GradfromB)/range;
   float curR = GradfromR,
         curG = GradfromG,
         curB = GradfromB;
   float tempr, tempb, tempg;
   getColor(tempr, tempb, tempg); //Save our old color
   for(y = ceil(MaxY)-1; y >= ceil(MinY); y--){
      xcount = 0;
      while((Tail < numPoints)&&(elist[Tail].ymax > y)){ Tail++;}
      for(i = Head; i < Tail; i++){
         elist[i].x += elist[i].dx;
         if (elist[i].ymin <= y){ xlist[xcount] = elist[i].x; xcount++; }
         else{ elist[i] = elist[Head]; Head++; }
      }
      sort(xlist,xcount);//sort so we dont get errors
      setColor(curR+=stepR,curG+=stepG,curB+=stepB);//dose the fill
      for(i = 0;i < xcount;i+=2){ horizLine(xlist[i],xlist[i+1],y); }
      if(Head==Tail){break;}
   }
   setColor(tempr, tempb, tempg);//Set color back to old color
   delete elist;
   delete xlist;
}
/**************************************************************************
*   Sortbyy
*      Sorts three points my there y values.
*   @param int a[] is the list to sort
*   @return void
**************************************************************************/
void move(Point2 a[],int i,int j){
   Point2 t;
          t = a[i];
       a[i] = a[j];
       a[j] = t;   
}
void sortbyy(Point2 a[]) {
   if(a[0].y < a[1].y){move(a,0,1);}
   if(a[0].y < a[2].y){move(a,0,2);}
   if(a[1].y < a[2].y){move(a,1,2);}
}
/**************************************************************************
*   polyfilltri
*      filles a triangle useing a color at each vertex.
*   @param const int numPoints is the number of points in the polygon
*   @param const Point2 p[] is the array of struct point2 holding the points
*   @return void
**************************************************************************/
void tripolyfill(const int numPoints,  Point2 p[]){
   if(numPoints != 3){setColor(1,1,1);polyfill(numPoints,p); return; }   
  
   float c0[3] = { 1.0,0.0,0.0 };
   float c1[3] = { 0.0,1.0,0.0 };
   float c2[3] = { 0.0,0.0,1.0 };
   
   sortbyy(p);
  
   int y;
   double dx1 = (p[0].x - p[1].x) / (p[0].y - p[1].y);
   double dx2 = (p[1].x - p[2].x) / (p[1].y - p[2].y);
   double dx3 = (p[0].x - p[2].x) / (p[0].y - p[2].y);
   float x1 = p[0].x;
   float x2 = p[0].x;   

   float range01 = fabs(p[0].x - p[1].x);
   float range02 = fabs(p[0].x - p[2].x);
   float range12 = fabs(p[1].x - p[2].x);
   
   float colorDx01R = (c1[0] - c0[0]) / range01; 
   float colorDx01G = (c1[1] - c0[1]) / range01; 
   float colorDx01B = (c1[2] - c0[2]) / range01; 
 
   float colorDx02R = (c2[0] - c0[0]) / range02; 
   float colorDx02G = (c2[1] - c0[1]) / range02; 
   float colorDx02B = (c2[2] - c0[2]) / range02; 

   float colorDx12R = (c2[0] - c1[0]) / range12; 
   float colorDx12G = (c2[1] - c1[1]) / range12; 
   float colorDx12B = (c2[2] - c1[2]) / range12; 
   
   float curR1 = c0[0];
   float curG1 = c0[1];
   float curB1 = c0[2];
   
   double curR2 = c0[0];
   double curG2 = c0[1];
   double curB2 = c0[2];
  
   
   for(y = p[0].y;y > p[1].y; y--){
      horizgradfillFrom(fabs(curR1),fabs(curG1),fabs(curB1));
      horizgradfillTo(fabs(curR2),fabs(curG2),fabs(curB2));
      
      horizLinegrad(x1,x2,y);
      x1 = x1 - dx1;
      x2 = x2 - dx3;
      curR1=curR1+colorDx01R;
      curG1=curG1+colorDx01G;
      curB1=curB1+colorDx01B;
      
      curR2=curR2+colorDx02R;
      curG2=curG2+colorDx02G;
      curB2=curB2+colorDx02B;
   }
   
   for(y = p[1].y;y > p[2].y; y--){
      horizgradfillFrom(fabs(curR1),fabs(curG1),fabs(curB1));
      horizgradfillTo(fabs(curR2),fabs(curG2),fabs(curB2));
      horizLinegrad(x1,x2,y);
      x1 = x1 - dx2;
      x2 = x2 - dx3;
      curR1=curR1+colorDx12R;
      curG1=curG1+colorDx12G;
      curB1=curB1+colorDx12B;
      
      curR2=curR2+colorDx02R;
      curG2=curG2+colorDx02G;
      curB2=curB2+colorDx02B;
   }
}
/**************************************************************************
*   Inside
*      determins whether a point is inside or outsid of the cliping boundry
*   @param Point2 testVertex is the point to test
*   @return boolean if we are inside TRUE or not FALSE
**************************************************************************/
static int Inside(Point2 testVertex){
   switch(aganstxy){
      case 'x':
         switch(GorL){
            case '>':
               if(testVertex.x > boundry) { return 1; } else { return 0; }
               break;
            case '<':
               if(testVertex.x < boundry) { return 1; } else { return 0; }
               break;
         }
         break;
      case 'y':
         switch(GorL){
            case '>':
               if(testVertex.y > boundry) { return 1; } else { return 0; }
               break;
            case '<':
               if(testVertex.y < boundry) { return 1; } else { return 0; }
               break;
         }
         break;
  }
  cout << "ERROR: inside coulde not determin the location of your polygon" << endl << flush;
  return NULL;
}
/**************************************************************************
*   Output
*      Addes the point to the array and keeps up with the total number of
*      points so far. This should probably not be a fucntion
*   @param
*   @return
**************************************************************************/
inline static void Output(Point2 newVertex, int *numResult,Point2 result[]){
   result[*numResult] = newVertex;
   *numResult = *numResult + 1;
   //pixPlot(result[*numResult-1].x,result[*numResult-1].y,0);
}
/**************************************************************************
*   Intersect
*      is our bit nasty function to claculate the intersection of the boundry
*      line and the line created by the two points
*   @param Point2 first is the first point in the line
*   @param Point2 second is the second point in the line
*   @return Point2 the point at which they intersect
**************************************************************************/
static Point2 Intersect(Point2 first, Point2 second){
   float m,x,y;
   Point2 p;
   if(first.x == second.x) {  p.x = first.x;  p.y = boundry; return p; }
  // if((second.x - first.x)==0){ m = ((first.y-second.y ) / (first.x-second.x)); }else{ m = ((second.y - first.y) / (second.x - first.x)); }
   m = ((second.y - first.y) / (second.x - first.x));
   float b = -((m * first.x) - first.y);
   switch(aganstxy){
      case 'x':
         x = boundry;
         y = (m*x) + b;
         break;
      case 'y':
         y = boundry;
         x = (y-b)/m;
         break;
      default: cout << "Error: Intersect is bad" << endl << flush; break;
  }
  p.x = x;
  p.y = y;
  return p;
}
/**************************************************************************
*   clipper
*      Checks all the edges of the polygon (points) and clipes them aganist
*      the bounding line we have set using the function clipagainst
*   @param const int numPoints is the number of points in the polygon
*   @param const Point2 p[] is the array of struct point2 holding the points
*   @param int & numResult
*   @param Point2 results
*   @return void
**************************************************************************/
void clipper(const int numPoints, const Point2 points[], int & numResult, Point2 results[]){
   Point2 s,p,i;
   int j;
   s=points[numPoints-1];
   for(j = 0; j < numPoints; j++){
      p = points[j];
      if(Inside(p)){
         if(Inside(s)){
            Output(p,&numResult,results);
         } else {
            i = Intersect(s,p);
             Output(i,&numResult,results);
            Output(p,&numResult,results);
         }
      } else {
         if (Inside(s)){
            i = Intersect(s,p);

            Output(i,&numResult,results);
         }
      }
      s = p;
   }
}
/**************************************************************************
*   clipagainst
*      sets the valuse for clipper, Intersect, and Inside to use. should
*      probably be a macro of some type.
*   @param char a
*   @param char b
*   @param char c
*   @return void
**************************************************************************/
void clipagainst(char a,char b,int c){
   aganstxy = a;
   GorL = b;
   boundry = c;
}
/**************************************************************************
*   polyclip
*      Seeing that clipper only clips against one line at a time we nead a
*      cute little driver function that goes around and clips against all
*      the lines in the window.  Thw window hight and window width are set
*      globale so we can cand those for each polygon
*   @param const int numPoints is the number of points in the polygon
*   @param const Point2 p[] is the array of struct point2 holding the points
*   @param int & numResult
*   @param Point2 results
*   @return void
**************************************************************************/
void polyclip(const int numPoints, const Point2 points[], int & numResult, Point2 results[]){
   int m;
   int x = numPoints;
   Point2 *p = new Point2[numPoints];
   for(m = 0; m < x;m++){ p[m].x = points[m].x; p[m].y = points[m].y; }
   //clip Left
   numResult = 0;
   clipagainst('x','>',ClipWindowX1); // -35
   clipper(x,p,numResult,results);
   //clip Right
   x = numResult;
   for(m = 0; m < x;m++){ p[m].x = results[m].x; p[m].y = results[m].y; }
   numResult = 0;
   clipagainst('x','<', ClipWindowX2); // 35
   clipper(x,p,numResult,results);
   //clip Bottom
   x = numResult;
   for(m = 0; m < x;m++){ p[m].x = results[m].x; p[m].y = results[m].y; }
   numResult = 0;
   clipagainst('y','>', ClipWindowY1); // 15
   clipper(x,p,numResult,results);
   //clip Top
   x = numResult;
   for(m = 0; m < x;m++){ p[m].x = results[m].x; p[m].y = results[m].y; }
   numResult = 0;
   clipagainst('y','<', ClipWindowY2); // 85
   clipper(x,p,numResult,results);
   delete p;
}
/**************************************************************************
*   ClipWindow
*      Sets the window we want to clip against, it is set by forming a window
*      or box out of two points P1(x1,y1) and P2(x2,y2)
*   @param int x1 the x value of our first point
*   @param int y1 the y value
*   @param int x2 the x value of our second point
*   @param int y2 the y value of that second point
*   @return void
**************************************************************************/
void setClipWindow(int x1, int y1, int x2, int y2)
{                     //-35 15 35 85
   ClipWindowX1 = x1;
   ClipWindowY1 = y1;
   ClipWindowX2 = x2;
   ClipWindowY2 = y2;
}
