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
*      ver4.0 -
*      ver3.9 -
*      ver3.8 - WARNING - old vertions each polygon was a differant object
                   now all points and vertexts must be put in the same list
                   this should be fixed but work for now. This is because of
                   the way painters algorithm works.
*      ver3.7 - got minimax test to work properly (I think)
*      ver3.6 - major updata, fixed backface removel, errly late promblem :)
*      ver3.5 - addend in more depth sort stuff (intersection test)
*      ver3.4 - addend depthsort beginings and minimax test.
*      ver3.3 - redid globals include the face colors - did backface fill
*      ver3.2 - put in backface removele for wirefram model
*      ver3.1 - added int a simple 3D fill begining of painters algorithm
*      ver3.0 - Finished 3D, added goofy demo for Al.
*      
*   @version 3.1
*   @author YNOP,jta001@coes.latech.edu,ynop@acm.org
*   @copyright 1998,1999 The Abstract Company
**************************************************************************/  

/**************************************************************************
*   polyfill3D
*      fill a 3D object that is described by a list of Plains and points
*      the plains MUST already be proken down into tryangles
*   @param void
*   @return void
**************************************************************************/
void polyfill3D(Point3D Vlist1[], int numPoints, Plane3D Plist1[],int numPlanes){ 
   Point3D *newVlist2 = new Point3D[numPoints];
   Point2 tempPoint2[4];
   ViewTransForm(Vlist1, numPoints,newVlist2);
   for(int i = 0;i < numPlanes; i++){
      tempPoint2[0].x = ((d * newVlist2[Plist1[i].P1].x) / (double)(d + newVlist2[Plist1[i].P1].z));
      tempPoint2[0].y = ((d * newVlist2[Plist1[i].P1].y) / (double)(d + newVlist2[Plist1[i].P1].z));
      tempPoint2[1].x = ((d * newVlist2[Plist1[i].P2].x) / (double)(d + newVlist2[Plist1[i].P2].z));
      tempPoint2[1].y = ((d * newVlist2[Plist1[i].P2].y) / (double)(d + newVlist2[Plist1[i].P2].z));
      tempPoint2[2].x = ((d * newVlist2[Plist1[i].P3].x) / (double)(d + newVlist2[Plist1[i].P3].z));
      tempPoint2[2].y = ((d * newVlist2[Plist1[i].P3].y) / (double)(d + newVlist2[Plist1[i].P3].z));
      setColor(Plist1[i].R,Plist1[i].G,Plist1[i].B);
      polyfill(3, tempPoint2);
   }
   delete newVlist2;
}
/**************************************************************************
*   removeBackFaces
*   @param void
*   @return void
**************************************************************************/
void removeBackFaces(Point3D Vlist[], int numPoints, Plane3D Pln[], int numPlanes){
   int i;
   double x1,x2,x3,y1,y2,y3,z1,z2,z3;
   double A,B,C,D;
   double blah;
   Point3D temp;

   for(i = 0;i < numPlanes; i++){
      x1 = Vlist[Pln[i].P1].x;
      y1 = Vlist[Pln[i].P1].y;
      z1 = Vlist[Pln[i].P1].z;

      x2 = Vlist[Pln[i].P2].x;
      y2 = Vlist[Pln[i].P2].y;
      z2 = Vlist[Pln[i].P2].z;

      x3 = Vlist[Pln[i].P3].x;
      y3 = Vlist[Pln[i].P3].y;
      z3 = Vlist[Pln[i].P3].z;
      
//    A =      ((y2 * z3)-(z2 * y3)) - y1 * ((     z3) - (z2     )) + z1 * ((     y3) - (y2     ));
//    B = x1 * ((     z3)-(z2     )) -      ((x2 * z3) - (z2 * x3)) + z1 * ((x2     ) - (     x3));
      C = x1 * ((y2     )-(     y3)) - y1 * ((x2     ) - (     x3)) +      ((x2 * y3) - (y2 * x3));
      D = x1 * ((y2 * z3)-(z2 * y3)) - y1 * ((x2 * z3) - (z2 * x3)) + z1 * ((x2 * y3) - (y2 * x3));
    
      temp.x = thisO.x - thisR.x;
      temp.y = thisO.y - thisR.y;
      temp.z = thisO.y - thisR.y;            
      blah = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
      blah = abs(blah);
      if((C * blah  - D) > 0){
         Pln[i].isBackFace = 1; //TRUE
      }else{
         Pln[i].isBackFace = 0; //Not a back Face
      }
   }
}
/**************************************************************************
*   Draw3DPoly
*      Draws a 3DPolygon using Depth-Projection
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void Draw3DPoly(Point3D Vlist[], Plane3D Plist[], int numVert,int numPlanes){
   double temp;
   Point3D *tempVlist = new Point3D[numVert];
   Point3D *ResultVlist = new Point3D[numVert];
   int i;
   Point2 tempPoint2D[4];
 
   /* Do our View Transformation on the points */
   ViewTransForm(Vlist, numVert,ResultVlist);

   //removeBackFaces(ResultVlist, numVert, Plist,numPlanes);

   /* This is our depth transform - Makes everything look kewl */
   for( i = 0;i < numVert;i++){
      tempVlist[i].x = ((d * ResultVlist[i].x) / (double)(d + ResultVlist[i].z));
      tempVlist[i].y = ((d * ResultVlist[i].y) / (double)(d + ResultVlist[i].z));
      tempVlist[i].z = ((ResultVlist[i].z)     / (double)(d + ResultVlist[i].z));
      /* Z is useless for our prog but GREAT for Z-buffering  */
   }
   
   /* Take the Transformed,Prespective points and remove useless Planes (ie Triangles) */
   removeBackFaces(tempVlist, numVert, Plist,numPlanes);

   //DepthSort(tempVlist, Plist,numVert,numPlanes);
   CheesySort(tempVlist, Plist,numVert,numPlanes);

  // PaintersAlg(tempVlist, Plist, numVert,numPlanes);
  
   for(i = 0;i < numPlanes;i++){
      if(!Plist[i].isBackFace){
         tempPoint2D[0].x = tempVlist[Plist[i].P1].x;
         tempPoint2D[0].y = tempVlist[Plist[i].P1].y;
         tempPoint2D[1].x = tempVlist[Plist[i].P2].x;
         tempPoint2D[1].y = tempVlist[Plist[i].P2].y;
         tempPoint2D[2].x = tempVlist[Plist[i].P3].x;
         tempPoint2D[2].y = tempVlist[Plist[i].P3].y;
         setColor(Plist[i].R,Plist[i].G,Plist[i].B);
         if(!WIREFRAME){
            polyfill(3, tempPoint2D);
         }else{
            bresLine(int(tempVlist[Plist[i].P1].x),
                     int(tempVlist[Plist[i].P1].y),
                     int(tempVlist[Plist[i].P2].x),
                     int(tempVlist[Plist[i].P2].y));
            bresLine(int(tempVlist[Plist[i].P2].x),
                     int(tempVlist[Plist[i].P2].y),
                     int(tempVlist[Plist[i].P3].x),
                     int(tempVlist[Plist[i].P3].y));
            bresLine(int(tempVlist[Plist[i].P3].x),
                     int(tempVlist[Plist[i].P3].y),
                     int(tempVlist[Plist[i].P1].x),
                     int(tempVlist[Plist[i].P1].y));
         }
      }
   }
   
  
   
   delete tempVlist;
   delete ResultVlist;
}


/**************************************************************************
*   CheesySort
*      A ripoff alg that works for most things 
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void CheesySort(Point3D Vlist[], Plane3D Plist[], int numVert,int numPlanes){
   int i,j,k;
   double B;
   for (i = 0; i < numVert; i++) {
      //PaintersData[i] = Max3(Vlist[Plist[i].P1].z,Vlist[Plist[i].P2].z,Vlist[Plist[i].P3].z) 
   }
   

}


/**************************************************************************
*   DepthSort
*      A array of algorithms that calculat depth for painters algorithm
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void DepthSort(Point3D Vlist[], Plane3D Plist[], int numVert,int numPlanes){
   int i,j,length,OverLap,tri1,tri2;
   double axl,axh,ayl,ayh,bxl,bxh,byl,byh;
   double x1,x2,x3,x4,y1,y2,y3,y4; 
   double D,eps = 0.00000000000000000000001;
   double s,t,ix,iy;
   Plane3D *frontPlist = new Plane3D[numPlanes];
      
   // Make a nice Plist with only fron faces.
   length = 0;
   for(i = 0; i < numPlanes;i++){
      if(Plist[i].isBackFace){
         frontPlist[length] = Plist[i];
         length++;
      }
   }

   //  INIT THE PAINTERS DATA STRUCTUR FIRST;
   
   /* MIN - MAX TEST */
   for(i = 0; i < length; i++){
      axl = Min3(Vlist[frontPlist[i].P1].x,
                 Vlist[frontPlist[i].P2].x,
                 Vlist[frontPlist[i].P3].x);
      axh = Max3(Vlist[frontPlist[i].P1].x,
                 Vlist[frontPlist[i].P2].x,
                 Vlist[frontPlist[i].P3].x);
      ayl = Min3(Vlist[frontPlist[i].P1].y,
                 Vlist[frontPlist[i].P2].y,
                 Vlist[frontPlist[i].P3].y);
      ayh = Max3(Vlist[frontPlist[i].P1].y,
                 Vlist[frontPlist[i].P2].y,
                 Vlist[frontPlist[i].P3].y);
      for(j = 0; j < length; j++){  
         if(i != j){
            bxl = Min3(Vlist[frontPlist[j].P1].x,
                       Vlist[frontPlist[j].P2].x,
                       Vlist[frontPlist[j].P3].x);
            bxh = Max3(Vlist[frontPlist[j].P1].x,
                       Vlist[frontPlist[j].P2].x,
                       Vlist[frontPlist[j].P3].x);
            byl = Min3(Vlist[frontPlist[j].P1].y,
                       Vlist[frontPlist[j].P2].y,
                       Vlist[frontPlist[j].P3].y);
            byh = Max3(Vlist[frontPlist[j].P1].y,
                       Vlist[frontPlist[j].P2].y,
                       Vlist[frontPlist[j].P3].y);
      
            if((axh < bxl) || (bxh < axl) ||
               (ayh < byl) || (byh < ayl)){
               OverLap = 0;break;
            }else {
               OverLap = 1; 
            }
         }
      }
      frontPlist[i].isOverLap = OverLap;      
   }


   /*  Intersection Test */
   /*
   for(i = 0; i < length; i++){
      if(frontPlist[i].isOverLap){
         for(j = 0; j < length; j++){
            //if(frontPlist[j].isOverLap){
            if(i != j){
               for(tri1 = 0; tri1 < 3; tri1++){
                  switch(tri1){
                  case 0:
                     x1 = Vlist[frontPlist[i].P1].x;
                     y1 = Vlist[frontPlist[i].P1].y;
                     x2 = Vlist[frontPlist[i].P2].x;
                     y2 = Vlist[frontPlist[i].P2].y;
                     break;
                  case 1:
                     x1 = Vlist[frontPlist[i].P2].x;
                     y1 = Vlist[frontPlist[i].P2].y;
                     x2 = Vlist[frontPlist[i].P3].x;
                     y2 = Vlist[frontPlist[i].P3].y;
                     break;
                  case 2:
                     x1 = Vlist[frontPlist[i].P3].x;
                     y1 = Vlist[frontPlist[i].P3].y;
                     x2 = Vlist[frontPlist[i].P1].x;
                     y2 = Vlist[frontPlist[i].P1].y;
                     break;
                  }
                  for(tri2 = 0; tri2 < 3; tri2++){
                     switch(tri1){
                     case 0:
                        x1 = Vlist[frontPlist[j].P1].x;
                        y1 = Vlist[frontPlist[j].P1].y;
                        x2 = Vlist[frontPlist[j].P2].x;
                        y2 = Vlist[frontPlist[j].P2].y;
                        break;
                     case 1:
                        x3 = Vlist[frontPlist[j].P2].x;
                        y3 = Vlist[frontPlist[j].P2].x;
                        x4 = Vlist[frontPlist[j].P3].x;
                        y4 = Vlist[frontPlist[j].P3].x;
                        break;
                     case 2:
                        x1 = Vlist[frontPlist[j].P3].x;
                        y1 = Vlist[frontPlist[j].P3].y;
                        x2 = Vlist[frontPlist[j].P1].x;
                        y2 = Vlist[frontPlist[j].P1].y;
                        break;
                     }
                     D = ((x3 - x4) * (y1 - y2)) - ((x1 - x2) * (y3 - y4));

                     if ((D < eps) && (D > -eps)){ 
                        // This means that the two lines are parallel
                        if(frontPlist[i].isOverLap != 1){frontPlist[i].isOverLap = 0; }//dont overlap nothing
                     }else{     
                                     
                        s = (((x3 - x4) * (y1 - y3)) - ((x1 - x3) * (y3 - y4)))/D;
                        t = (((x1 - x2) * (y1 - y3)) - ((x1 - x3) * (y1 - y2)))/D;
                       
                        if(((s > 0) && (s < 1)) && ((t > 0) && (t < 1)) ){
                           // the lines intersect
                           //cout << "adsf" << endl << flush;
                           frontPlist[i].isOverLap = 1; //dont overlap nothing
                           
                           ix = x1 + s * (x2 - x1);
                           iy = y1 + s * (y2 - y1);
                        }else{
                           if(frontPlist[i].isOverLap != 1){frontPlist[i].isOverLap = 0; }
                        
                        }
                     }
                     
                  }//end for tri2
               }//end for tri1
            }//end if j
         }//end for j
      }//end if i
   }//end for i

*/

   /* Center inside square test */
 /*  for(i = 0; i < length; i++){
      if(frontPlist[i].isOverLap){
         for(j = 0; j < length; j++){
            if(frontPlist[j].isOverLap){
    
            }
         }
      }
   }*/

  for(i = 0; i < length; i++){
  //if(frontPlist[i].isOverLap == 1)cout << ":" <<  flush;
  }//cout <<"!!"<< endl;
  



   delete[] frontPlist;
}
/**************************************************************************
*   PaintersAlg
*      A Sort little painter algorithm.. 
*   @param Point3D Vlist[] is the list of 3DPoints
*   @param Edge3D Elist[] is the list of order of the 3DPoints
*   @return void
**************************************************************************/
void PaintersAlg(Point3D Vlist[], Plane3D Plist[], int numVert,int numPlanes){
   int i,j,k;
   for(i = 1; i <= numPlanes;i++){
      j = 1;
      while(PaintersData[j].behind != 0){ j++; }
      //draw thsi triangle  Plist[i]
      PaintersData[j].behind--;
      for(k = 1;k < PaintersData[j].frontlist[0];k++){  // for all elements in the frontlist
         PaintersData[PaintersData[j].frontlist[k]].behind--;
      }
      
   Point2 tempPoint2D[4];    
      if(!Plist[j].isBackFace){
         tempPoint2D[0].x = Vlist[Plist[j].P1].x;
         tempPoint2D[0].y = Vlist[Plist[j].P1].y;
         tempPoint2D[1].x = Vlist[Plist[j].P2].x;
         tempPoint2D[1].y = Vlist[Plist[j].P2].y;
         tempPoint2D[2].x = Vlist[Plist[j].P3].x;
         tempPoint2D[2].y = Vlist[Plist[j].P3].y;
         setColor(Plist[j].R,Plist[j].G,Plist[j].B);
         polyfill(3, tempPoint2D);
      }
   }
}

