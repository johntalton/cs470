/**************************************************************************
*   Draw routines for my graphis packedge.
*      ¥NöP's Graphics Package
*      This was originaly wirten for my cs470 graphics classs.
*      it is not verry usefull for much else but it is good
*      for learning the basics about how the primitive graphics
*      work.
*   TODO
*
*   HISTORY
*      ver3.0 - Finished 3D, added goofy demo for Al.
*      ver2.9 - Fixed 2.6 hack and got the view right with z neg toward user.
*      ver2.8 - Major revisions of the Viewtransform .. Math updata and stuff
*      ver2.7 - Scale() added and bugfixes
*      ver2.6 - fixed neg Y problem (y = -y) Hack
*      ver2.5 - ViewTranform done
*      ver2.4 - Setup ViewTranfor
*      ver2.3 - Depth projection
*      ver2.2 - Orthographic projection done . useless
*      ver2.1 - 3D point and Edge list set up
*      ver2.0 - polygon stuff finished
*
*   @version 3.0
*   @author YNOP,jta001@coes.latech.edu,ynop@acm.org
*   @copyright 1998,1999 The Abstract Company
**************************************************************************/


/**************************************************************************
* stuff avalible in this ver
**************************************************************************/

/**************************************************************************
*   ViewPoint
*      Sets up the viewPoint at which to display form
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void ViewPoint(Point3D newO, Point3D newR,Point3D newV){
   thisO = newO;
   thisR = newR;
   thisV = newV;
}
/**************************************************************************
*   Normalize
*      Normalizes a vector
*   @param Point3D Vector is the Vector we want normalize
*   @return void
**************************************************************************/
void Normalize(Point3D &Vector){
   double Magnitude = sqrt(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z);
   Vector.x = Vector.x/Magnitude;
   Vector.y = Vector.y/Magnitude;
   Vector.z = Vector.z/Magnitude;
}
/**************************************************************************
*   CrossProduct
*      proforms a CorssProduct of 2 vectors
*   @param Point3D Vector is the Vector we want normalize
*   @return void
**************************************************************************/
inline Point3D CrossProduct(Point3D A, Point3D B) {
   Point3D R;
   R.x = A.y * B.z - A.z * B.y;
   R.y = A.z * B.x - A.x * B.z;
   R.z = A.x * B.y - A.y * B.x;
   return R;
}
/**************************************************************************
*   DotProduct
*      dose a dotProduct on 2 vectors
*   @param Point3D A is the Vector we want normalize
*   @return void
**************************************************************************/
inline double DotProduct(Point3D A,Point3D B){
   return (A.x * B.x + A.y * B.y + A.z * B.z);
}
/**************************************************************************
*   ViewTransForm
*      Sets up the viewPoint at which to display form
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void ViewTransForm(Point3D Vlist[], int numVert,Point3D ResultVlist[]){
   Point3D X,Y,Z;
   double l,VbyCosOfAngle;
   double MagnitudeV = sqrt(thisV.x*thisV.x + thisV.y*thisV.y + thisV.z*thisV.z);
   double MagnitudeZ;

   Z.x = thisR.x - thisO.x;
   Z.y = thisR.y - thisO.y;
   Z.z = thisR.z - thisO.z;
   
   MagnitudeZ = sqrt(Z.x*Z.x + Z.y*Z.y + Z.z*Z.z); //these two line are realalistic
   realscale = (windH/MagnitudeZ);                         //  scale .... 
   
   Normalize(Z);

   VbyCosOfAngle = DotProduct(Z,thisV);

   l = VbyCosOfAngle;

   Y.x = thisV.x - Z.x * l;
   Y.y = thisV.y - Z.y * l;
   Y.z = thisV.z - Z.z * l;
   Normalize(Y);

   X = CrossProduct(Y, Z);
   Normalize(X);

   for (int i = 0; i < numVert; i++){
      ResultVlist[i].x = ((Vlist[i].x * X.x) + (Vlist[i].y * X.y) + (Vlist[i].z*X.z) - (thisO.x * X.x) - (thisO.y*X.y) - (thisO.z*X.z)) * (windH/MagnitudeZ);
      ResultVlist[i].y = ((Vlist[i].x * Y.x) + (Vlist[i].y * Y.y) + (Vlist[i].z*Y.z) - (thisO.x * Y.x) - (thisO.y*Y.y) - (thisO.z*Y.z)) * (windH/MagnitudeZ);
      ResultVlist[i].z = ((Vlist[i].x * Z.x) + (Vlist[i].y * Z.y) + (Vlist[i].z*Z.z) - (thisO.x * Z.x) - (thisO.y*Z.y) - (thisO.z*Z.z)) * (windH/MagnitudeZ);
   }
}
/**************************************************************************
*   Draw3DPoly
*      Draws a 3DPolygon using Depth-Projection
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void Draw3DPoly(Point3D Vlist[], Edge3D Elist[], int numVert,int numEdges){
   double temp;
   Point3D *tempVlist = new Point3D[numVert];
  // Edge3D  *tempElist = new Edge3D[numEdges];
   Point3D *ResultVlist = new Point3D[numVert];
   int i;

   ViewTransForm(Vlist, numVert,ResultVlist);

   for( i = 0;i < numVert;i++){
      tempVlist[i].x = ((d * ResultVlist[i].x) / (double)(d + ResultVlist[i].z));
      tempVlist[i].y = ((d * ResultVlist[i].y) / (double)(d + ResultVlist[i].z));
      tempVlist[i].z = ((ResultVlist[i].z) / (double)(d + ResultVlist[i].z));
      /* Z is useless for our prog but GREAT for Z-buffering  */
   }

   for( i = 0;i < numEdges;i++){
      bresLine(int(tempVlist[Elist[i].P1].x),
               int(tempVlist[Elist[i].P1].y),
               int(tempVlist[Elist[i].P2].x),
               int(tempVlist[Elist[i].P2].y));
   }
   delete tempVlist;
  //  delete tempElist;
   delete ResultVlist;
}
/**************************************************************************
*   Ortho
*      Draws a 3DPolygon using Orthographic View
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void Ortho(Point3D Vlist[], Edge3D Elist[], int numVert, int numEdges){
   Ortho(Vlist,Elist,numVert,numEdges,1);
}
void Ortho(Point3D Vlist[], Edge3D Elist[], int numVert, int numEdges,int Scale){
   Point3D *ResultVlist = new Point3D[numVert];
   ViewTransForm(Vlist, numVert,ResultVlist);
   for(int i = 0;i < numEdges;i++){
      bresLine(int(ResultVlist[Elist[i].P1].x)*Scale,int(ResultVlist[Elist[i].P1].y*Scale),
               int(ResultVlist[Elist[i].P2].x)*Scale,int(ResultVlist[Elist[i].P2].y*Scale));
   }
}
/**************************************************************************
*   Scale
*      scales a set of points
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param int numVert is the num of Vertaces to scale
*   @param double scale is the scale factor
*   @return void
**************************************************************************/
void Scale(Point3D Vlist[], int numVert, Point3D Centroid, double scale,Point3D outVlist[]){
   double temp;
   for(int i = 0; i < numVert; i++){
      temp = Vlist[i].x - Centroid.x;
      temp = temp * scale;
      outVlist[i].x = temp + (Centroid.x * scale);

      temp = Vlist[i].y - Centroid.y;
      temp = temp * scale;
      outVlist[i].y = temp + (Centroid.y * scale);

      temp = Vlist[i].z - Centroid.z;
      temp = temp * scale;
      outVlist[i].z = temp + (Centroid.z * scale);


   }
}
/**************************************************************************
*   Rotation
*      Prefoms a 3D rotation of a set of Vertexts
*
*      x-CW            y-CW            z-CW
*      [ 1  0  0 0 ]   [ C  0 -S 0 ]   [ C  S  0 0 ]
*      [ 0  C  S 0 ]   [ 0  1  0 0 ]   [-S  C  0 0 ]
*      [ 0 -S  C 0 ]   [ S  0  C 0 ]   [ 0  0  1 0 ]
*      [ 0  0  0 1 ]   [ 0  0  0 1 ]   [ 0  0  0 1 ]
*
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void Rotation(Point3D Vlist[], int numVert, double Theta, Point3D VlistOUT[]){
   int x,y,z;

   for(int i = 0; i < numVert; i++){
      x = (int(Vlist[i].x));
      y = (int(Vlist[i].y));
      z = (int(Vlist[i].z));
   }
}
/**************************************************************************
*   MaxtrixMult
*      does a matrix multiply for Rotation - Translation - Scale functions
*                 c   r->
*                \|/
*
*      [x y z 1][ 0    1  2  3 ]
*               [ 4    5  6  7 ]
*               [ 8    9 10 11 ]
*               [ 12  13 14 15 ]
*
*   @param
*   @param
*   @return void
**************************************************************************/
void MaxrixMult(){/*
      R[0] = (x * M[0]) +
             (y * M[4]) +
             (z * M[8]) +
             (1 * M[12]);

      R[1] = (x * M[1]) +
             (y * M[5]) +
             (z * M[9]) +
             (1 * M[13]);

      R[2] = (x * M[2]) +
             (y * M[6]) +
             (z * M[10])+
             (1 * M[15]);*/
}

















