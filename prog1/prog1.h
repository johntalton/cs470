#include <iostream.h>
#include <string.h>
#include <math.h>
#define BLANK  "\0                                                                                                                                                                    ";
/**************************************************************************
*   Draw routines for my graphis packedge.
*      ¥NöP's Graphics Package
*      This was originaly wirten for my cs470 graphics classs.
*      it is not verry usefull for much else but it is good 
*      for learning the basics about how the primitive graphics
*      work. 
*
*   John Talton 439.57.4799
*   prog1 cs470 1/6/99
*
*   TODO
*      get rid of all that damn BLANK space. there has got ot be a better
*         way of makeing a array of .. well big.
*      do some more documentation. Always nead that. 
*   HISTORY
*      ver1.0 - Lines Complete.
*      ver0.5 - more Line algorithms. Not user but 
*               good practic and I am trying to get my
*               class work done. :)
*      ver0.1 - basic primitive pixPlot and some lines
*      
*   @version 1.0
*   @author YNOP,jta001@coes.latech.edu,ynop@acm.org
*   @copyright 1998,1999 The Abstract Company
**************************************************************************/  
//int Gcd(int a,int b){while(b!=0){int t=a;a=b;b=t;b=b % a;}return a;}//Euclid's GCD
/**************************************************************************
* stuff avalible in this ver
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
void horizLine(int x1,int x2, int y){
   int i;
   for(i = x1; i <= x2; i++){ pixPlot(i,y); }
}
/**************************************************************************
*   bestFitLine
*      this algorithm sucks im my opinion. if findes a pattern that the line
*      fits and then repeats it untill it has drawn the line.
*   @param int x1 is the x value of our first point
*   @param int y1 is our y value of our first point
*   @param int x2 is our x value of our second point
*   @param int y2 is our y value of our second point
*   @return void
***************************************************************************
*   inv 
*      a sting invers func used in bestFit .. is sucks for preformance
*      be carefull is does not return a string it modifyes the original!!!      
*   @param char *s is a string of any length to be reversed.
*   @return void!!!
**************************************************************************/
inline void inv(char *s){
   s = _strrev(s);   //afer writeing this code .. found this func that did it
 /*  int l = strlen(s);
   int x = 0;
   l--;
   char *news = BLANK;
   while(l >= 0){
      news[x++] = s[l--];
   }
   news[x] = '\0';
   strcpy(s,news);*/
}
/**************************************************************************/
void bestFitLine(int x1, int y1, int x2, int y2){
   int x = x2 - x1;
   int y = y2 - y1;
   int oct = 0;
   if(y==0){ if(x1>x2){int t=x1;x1=x2;x2=t;}horizLine(x1,x2,y1); return;}
   if(y<0){ y = -y; oct+=4; }
   if(x<0){ x = -x; oct+=2;}//bit1=1
   if(x<y){ int t=x; x=y; y=t; oct+=1;}//bit0=1
   int origanlx = x;
   char *sub1 = BLANK; // This is really suck
   char *sub2 = BLANK; // because they can only be this long :(
   strcpy(sub1,"0");
   strcpy(sub2,"1");
   x = x - y;         // 130 - 0 = 130
   while(x!=y){
        if(!y){ sub1[0] = '\0';sub2[0] = '\0'; break; }
        if(!x){ strcpy(sub1,"1"); strcpy(sub2,"1"); break; }
      if(x > y){
         inv(sub2);
         sub2 = strcat(sub2,sub1);
         x = x - y;
      }else if(x==y){
         //finished 
      }else if(x < y){
         inv(sub1);
         sub1 = strcat(sub1,sub2);
         y = y - x;
      }
   } 
   inv(sub2);
   strcat(sub2,sub1);
   int counter = 0;
   y = 0;x = 0;
   while (x <= origanlx) {
       switch (oct) {
          case 0: pixPlot( x + x1,  y + y1);break;
          case 1: pixPlot( y + x1,  x + y1);break;
          case 2: pixPlot(-x + x1 , y + y1);break;
          case 3: pixPlot(-y + x1 , x + y1);break;
          case 4: pixPlot( x + x1 ,-y + y1);break;      
          case 5: pixPlot( y + x1 ,-x + y1);break;           
          case 6: pixPlot(-x + x1 ,-y + y1);break;     
          case 7: pixPlot(-y + x1 ,-x + y1);break;         
       }
       if (sub2[counter] == '\0'){ counter = 0;}
       if (sub2[counter++] == '1'){ y++; }
       x++;
   } 
   delete sub1;
   delete sub2;
}
/**************************************************************************
*   simpleDDALine
*      Uhhh could this be any slllooowwwerrr.. I just love floating point 
*      numbers..
*   @param int x1 is the x value of our first point
*   @param int y1 is our y value of our first point
*   @param int x2 is our x value of our second point
*   @param int y2 is our y value of our second point
*   @return void
**************************************************************************/
void simpleDDALine(int x1, int y1, int x2, int y2){
   double Dx = 0,
          Dy = 0,
          x = x1,
          y = y1;
   int    i,
          nstep = abs(x1 - x2);

   if(abs(y1-y2) > nstep){ nstep = abs(y1 - y2); }
   if(nstep > 0){
      Dx = (double)(x2 - x1)/nstep;
      Dy = (double)(y2 - y1)/nstep;
   }
   for (i = 0; i<= nstep; i++){
      pixPlot((int)(x+0.5),(int)(y+0.5));
      x += Dx;
      y += Dy;
   }
}
/**************************************************************************
*   bresLine 
*      This is the one that we will actually use. it is pritty nice compared
*      to the others here. It does a nifty math trick and figures out when 
*      to inc y or x. go look it up some place for explanation - its all over
*      the net. 
*   @param int x1 is the x value of our first point
*   @param int y1 is our y value of our first point
*   @param int x2 is our x value of our second point
*   @param int y2 is our y value of our second point
*   @return void
**************************************************************************/
void bresLine(int x1, int y1, int x2, int y2){
   int oct = 0;
   int xoff = x1;
   int yoff = y1; 
   x2=x2-xoff;
   y2=y2-yoff; 
   x1=0;
   y1=0;
   if(y2==0){ if (x1>x2){int t=x1;x1=x2;x2=t;}horizLine(x1+xoff,x2+xoff,y1+yoff); return;}
   if(y2<0){ y2 = -y2; oct+=4; }//bit2=1
   if(x2<0){ x2 = -x2; oct+=2;}//bit1=1
   if(x2<y2){ int t=x2; x2=y2; y2=t; oct+=1;}//bit0=1
   int x=x1,
       y=y1,
       sum=x2-x1,
       Dx=2*(x2-x1),
       Dy=2*(y2-y1);
   for(int i=0; i <= x2-x1; i++){ 
      switch(oct){
         case 0:pixPlot(( x)+xoff,( y)+yoff);break;
         case 1:pixPlot(( y)+xoff,( x)+yoff);break;
         case 3:pixPlot((-y)+xoff,( x)+yoff);break;
         case 2:pixPlot((-x)+xoff,( y)+yoff);break;
         case 6:pixPlot((-x)+xoff,(-y)+yoff);break;
         case 7:pixPlot((-y)+xoff,(-x)+yoff);break;
         case 5:pixPlot(( y)+xoff,(-x)+yoff);break;
         case 4:pixPlot(( x)+xoff,(-y)+yoff);break;
      }
      x++;
      sum-=Dy;
      if(sum < 0){
         y++;
         sum += Dx;
      }
   }
}
/**************************************************************************
*   parameterCircle
*      A slow ass way of drawing circles. very logical though
*   @param int x1 is our x cord of the center of the circle
*   @param int y2 is our y cord of the center
*   @parma int r is the radius
*   @return void
**************************************************************************/
void parameterCircle(int x1, int y1, int r){
	double x = (double)r,
          y = 0,
          theta = 0,
          dtheta = atan(1.0 / (double)r);
	while(theta <= 0.79){
		x = r * cos(theta);
		y = r * sin(theta);
		theta += dtheta;
		pixPlot( x+x1, y+y1);
      pixPlot(-x+x1, y+y1);
      pixPlot( x+x1,-y+y1);
      pixPlot(-x+x1,-y+y1);
      pixPlot( y+x1, x+y1);
      pixPlot(-y+x1, x+y1);
      pixPlot( y+x1,-x+y1);
      pixPlot(-y+x1,-x+y1);
	}
}
/**************************************************************************
*   spiralDDACircle
*      ahhhh spirallll  circle ... thats what is does. Nice
*   @param int x1 is our x cord of the center of the circle
*   @param int y2 is our y cord of the center
*   @param int r is our radius
*   @return void
**************************************************************************/
void spiralDDACircle(int x1, int y1, int r){
	double x = (double)r,
          y = 0.0,
          e = 1.0 / (double)r; //set our epsilon value
	while(x > y){
      pixPlot( x+x1, y+y1);
      pixPlot(-x+x1, y+y1);
      pixPlot( x+x1,-y+y1);
      pixPlot(-x+x1,-y+y1);
      pixPlot( y+x1, x+y1);
      pixPlot(-y+x1, x+y1);
      pixPlot( y+x1,-x+y1);
      pixPlot(-y+x1,-x+y1);
		x -= e * y;
		y += e * x;
	}
}
/**************************************************************************
*   bresCircle
*      They say it is one of the better ones. So I gess it is ... looks nice
*      on the screen and runns good. Plus it was easy to code :)
*   @param int x1 is our x cord of the center of the circle
*   @param int y2 is our y cord of the center
*   @param int r is our radius
*   @return void
**************************************************************************/
void bresCircle(int x1, int y1, int r){
   int x = 0,
       y = r,
       s = 3 - 2 * r;  //our first magic equation
   while(x <= y){
      pixPlot( x+x1, y+y1);
      pixPlot(-x+x1, y+y1);
      pixPlot( x+x1,-y+y1);
      pixPlot(-x+x1,-y+y1);
      pixPlot( y+x1, x+y1);
      pixPlot(-y+x1, x+y1);
      pixPlot( y+x1,-x+y1);
      pixPlot(-y+x1,-x+y1);
      s += s <= 0 ? 4*x++ + 6 : 4*(x++ - y--) + 10;  // this is one nasty if statmen
                 // that has been packed up and cotain our final two magic equations
   }
}