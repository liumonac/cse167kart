//
//  Track.cpp
//  cse167kart
//
//  Nick Troast, Monica Liu, Andrew Lin
//

#include "Track.h"
#include <stdlib.h>
#include <cmath>

Track::Track()
{
  curves.clear();
  stacks = 0.01;
  width = 0.5;
  eye_t = 0;
  center_t = 0.15;
  eyeCurve = 0;
  centerCurve = 0;
  laneCount = 2;
  maxLevels = 4;
}

void Track::addCurve(BCurve * c) {
  curves.push_back(c);
}

int Track::getSize() {
  return curves.size();
}

BCurve * Track::getCurve(int i) {
  if (i < 0) return NULL;
  if (i >= curves.size()) return NULL;
  return curves[i];
}

void Track::drawCurves() {
  glColor3f(1,0,0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < curves.size(); i++) {
    for (GLfloat j = 0; j <= 1; j += stacks) {
      glVertex3f(curves[i]->getPoint(j)[0], curves[i]->getPoint(j)[1], 
        		curves[i]->getPoint(j)[2]);
    }
  }
  glEnd();
}

void Track::drawPoints() {
  glPointSize(10);
  glBegin(GL_POINTS);
  for (int i = 0; i < curves.size(); i++) {
    glColor3f(0,0,1);
    glVertex3fv(curves[i]->getCPointer(0));
    glColor3f(0,1,0);
    for (GLfloat j = 1; j < 3; j++) {
      glVertex3fv(curves[i]->getCPointer(j));
    }
  }
  glEnd();
}

void Track::drawTrack() {
  glColor3f(1,1,1);
  glBegin(GL_QUAD_STRIP);
  glEnable(GL_TEXTURE_2D); 
  int texHeight = 0;
  int vertCounter = 0;
  for (int i = 0; i < curves.size(); i++) { 
    
    
    for (GLfloat j = 0; j <= 1; j += stacks) {
//code for rendering track
      Vector3 temp4((curves[i]->getTangent(j)));
      temp4.normalize();
      temp4 = temp4.scale(width);
      
      if(texHeight>10) texHeight=1;
      
     Vector3 v1(-temp4[1]+(curves[i]->getPoint(j))[0], 
                 temp4[0]+(curves[i]->getPoint(j))[1], 
        	 curves[i]->getPoint(j)[2]);

      Vector3 v2(temp4[1]+(curves[i]->getPoint(j))[0], 
                 -temp4[0]+(curves[i]->getPoint(j))[1],
                 curves[i]->getPoint(j)[2]);

      glTexCoord2f(0, (texHeight/10.0)); //Texture
      glNormal3f(0, 0, 1);
      glVertex3f(v1[0],v1[1],v1[2]);

      glTexCoord2f(laneCount, (texHeight/10.0)); //Texture
      glNormal3f(0, 0, 1);
      glVertex3f(v2[0],v2[1],v2[2]);

      if(texHeight==10){
      glTexCoord2f(0, (0/10.0)); //Texture
      glNormal3f(0, 0, 1);
      glVertex3f(v1[0],v1[1],v1[2]);

      glTexCoord2f(laneCount, (0/10.0)); //Texture
      glNormal3f(0, 0, 1);
      glVertex3f(v2[0],v2[1],v2[2]);

      }

      texHeight++;

      //code for rendering terrain - Version 1
      if(l0.size()<400){
      Vector3 v3(-temp4[1]+(curves[i]->getPoint(j))[0], 
            	 temp4[0]+(curves[i]->getPoint(j))[1], 
        	     curves[i]->getPoint(j)[2]);
      l0.push_back(v3);

      int reset = 1;
      Vector3 original = temp4;
      temp4 = temp4.scale(1);//1+std::pow(-1.0,(rand()%2))*(rand()%5)/10.0);
     /* Vector3 v4(-temp4[1]+(curves[i]->getPoint(j))[0],  // ORIGINAL
            	 temp4[0]+(curves[i]->getPoint(j))[1], 
        	     curves[i]->getPoint(j)[2]);*/ 

      Vector3 v4(-temp4[1]+v3[0], 
            	 temp4[0]+v3[1],
        	     v3[2]+(rand()%3/5.0+.25)*reset);
      l1.push_back(v4);

      temp4 = original.scale(1+/*reset*std::pow(-1.0,(rand()%10))*/(rand()%10)/100.0);
     /* Vector3 v5(-temp4[1]+(curves[i]->getPoint(j))[0], // ORIGINAL
            	 temp4[0]+(curves[i]->getPoint(j))[1], 
        	     curves[i]->getPoint(j)[2]);*/

      Vector3 v5(-temp4[1]+v4[0],
            	 temp4[0]+v4[1],
        	     v4[2]+reset*(rand()%20/30.0+.5));
      l2.push_back(v5);
      int x = std::pow(-1.0,(rand()%10));

      temp4 = original.scale(.8+reset*std::pow(-1.0,(rand()%10))*(rand()%10)/40.0);
      Vector3 v6(-temp4[1]+v5[0],
            	 temp4[0]+v5[1],
        	     v5[2]+(rand()%20/20.0+.5)*reset);
      l3.push_back(v6);

      temp4 = original.scale(.6+reset*std::pow(-1.0,(rand()%10))*(rand()%10)/30.0);
      Vector3 v7(-temp4[1]+v5[0],
            	 temp4[0]+v5[1],
        	     v5[2]+(rand()%20/20.0+.50)*reset);
      l4.push_back(v7);

      temp4 = original.scale(.6+reset*std::pow(-1.0,(rand()%10))*(rand()%10)/10.0);
      Vector3 v8(-temp4[1]+v5[0],
            	 temp4[0]+v5[1],
        	     v5[2]+(rand()%30/10.0+.75)*reset);
      l5.push_back(v8);

      temp4 = original.scale(.5+reset*std::pow(-1.0,(rand()%10))*(rand()%5)/5.0);
      Vector3 v9(-temp4[1]+v5[0],
            	 temp4[0]+v5[1],
        	     v5[2]+(rand()%30/8+.75)*reset);
      l6.push_back(v9);

      temp4 = original.scale(1.1);
      Vector3 v10(-temp4[1]+v5[0],
            	 temp4[0]+v5[1],
        	     /*v5[2]*/+15);
      l7.push_back(v10);

	  }
  //l1.push_back(genInner(l0[l0.size()-1],v1));
    }
        glDisable(GL_TEXTURE_2D); 
  }
  glEnd();
}


void Track::drawTerrainHelper(std::vector<Vector3> v1, std::vector<Vector3> v2, int level){
  glColor3f(1,1,1);
  //glNormal3f(0, 0, 1);
  glBegin(GL_QUAD_STRIP);
  glEnable(GL_TEXTURE_2D); 

  int texHeight=1;
  int repeatX = 5;
  int repeatY = 4;
  for (int i = 0; i < v1.size(); i++) {
      
      if(texHeight>repeatX) texHeight=1;

      glTexCoord2f(texHeight/(repeatX*1.0),level/(maxLevels*1.0/repeatY));
      glNormal3f(-v1[i][1], v1[i][0], 1);
      glVertex3f(v1[i][0],v1[i][1],v1[i][2]);

      glTexCoord2f(texHeight/(repeatX*1.0),(level+1)/(maxLevels*1.0/repeatY));
      glNormal3f(-v2[i][1], v2[i][0], 1);
      glVertex3f(v2[i][0],v2[i][1],v2[i][2]);


      if (texHeight==repeatX&&((i+1)!=v1.size())){
          glTexCoord2f(0/repeatX*1.0,level/(maxLevels*1.0/repeatY));
          glNormal3f(-v1[i][1], v1[i][0], 1);
          glVertex3f(v1[i][0],v1[i][1],v1[i][2]);

          glTexCoord2f(0/(repeatX*1.0),(level+1)/(maxLevels*1.0/repeatY));
          glNormal3f(-v2[i][1], v2[i][0], 1);
          glVertex3f(v2[i][0],v2[i][1],v2[i][2]);
          /*
          glTexCoord2f(1/repeat,level/maxLevels);
          glNormal3f(-v1[i+1][1], v1[i+1][0], 1);
          glVertex3f(v1[i+1][0],v1[i+1][1],v1[i+1][2]);

          glTexCoord2f(1/repeat,(level+1)/maxLevels);
          glNormal3f(-v2[i+1][1], v2[i+1][0], 1);
          glVertex3f(v2[i+1][0],v2[i+1][1],v2[i+1][2]);
          */
      }
      texHeight++;
  }
  /*
      int i = v1.size()-1;

      glTexCoord2f(0/repeat,level/maxLevels);
      glNormal3f(-v1[i][1], v1[i][0], 1);
      glVertex3f(v1[i][0],v1[i][1],v1[i][2]);

      glTexCoord2f(0/repeat,(level+1)/maxLevels);
      glNormal3f(-v2[i][1], v2[i][0], 1);
      glVertex3f(v2[i][0],v2[i][1],v2[i][2]);
      */
      int i = 0;
      glTexCoord2f(1/(repeatX*1.0),level/(maxLevels*1.0/repeatY));
      glNormal3f(-v1[i][1], v1[i][0], 1);
      glVertex3f(v1[i][0],v1[i][1],v1[i][2]);

      glTexCoord2f(1/(repeatX*1.0),(level+1)/(maxLevels*1.0/repeatY));
      glNormal3f(-v2[i][1], v2[i][0], 1);
      glVertex3f(v2[i][0],v2[i][1],v2[i][2]);
      
  glEnd();


}
void Track::drawTerrain(){
  /*
  glColor3f(1,0,0);
  glNormal3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < l0.size(); i++) {
      glVertex3f(l0[i][0],l0[i][1],l0[i][2]);
  }
  glEnd();

  glColor3f(1,0,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < l1.size(); i++) {
      glVertex3f(l1[i][0],l1[i][1],l1[i][2]);
  }
  glEnd();

  glColor3f(1,0,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < l1.size(); i++) {
      glVertex3f(l2[i][0],l2[i][1],l2[i][2]);
  }
  glEnd();

  glColor3f(1,0,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < l1.size(); i++) {
      glVertex3f(l3[i][0],l3[i][1],l3[i][2]);
  }
  glEnd();*/

  /*
  glColor3f(1,1,1);
  //glNormal3f(0, 0, 1);
  glBegin(GL_QUAD_STRIP);
  glEnable(GL_TEXTURE_2D); 

  int texHeight=1;
  double repeat = 20.0;
  for (int i = 0; i < l0.size(); i++) {
      
      if(texHeight>repeat) texHeight=1;

      glTexCoord2f(texHeight/repeat,0);
      glNormal3f(-l0[i][1], l0[i][0], 1);
      glVertex3f(l0[i][0],l0[i][1],l0[i][2]);

      glTexCoord2f(texHeight/repeat,1);
      glNormal3f(-l1[i][1], l1[i][0], 1);
      glVertex3f(l1[i][0],l1[i][1],l1[i][2]);


      if (texHeight==repeat){
          glTexCoord2f(0/repeat,0);
          glNormal3f(-l0[i][1], l0[i][0], 1);
          glVertex3f(l0[i][0],l0[i][1],l0[i][2]);

          glTexCoord2f(0/repeat,1);
          glNormal3f(-l1[i][1], l1[i][0], 1);
          glVertex3f(l1[i][0],l1[i][1],l1[i][2]);


      }
      texHeight++;

  }
  
  glTexCoord2f(texHeight/repeat,0);
  glNormal3f(-l0[0][1], l0[0][0], 1);
  glVertex3f(l0[0][0],l0[0][1],l0[0][2]);
  glTexCoord2f(texHeight/repeat,1);
  glNormal3f(-l1[0][1], l1[0][0], 1.0/maxLevels);
  glVertex3f(l1[0][0],l1[0][1],l1[0][2]);

  glEnd();

  */
 drawTerrainHelper(l0,l1,0);
 drawTerrainHelper(l1,l2,1);
 drawTerrainHelper(l2,l3,2);
 drawTerrainHelper(l3,l4,3);
 drawTerrainHelper(l4,l5,4);
 drawTerrainHelper(l5,l6,5);
 drawTerrainHelper(l6,l7,6);
 /*
 glColor3f(1,1,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i < l0.size(); i++) {

      glNormal3f(-l2[i][1], l2[i][0], 1);
      glVertex3f(l2[i][0],l2[i][1],l2[i][2]);
      glNormal3f(-l1[i][1], l1[i][0], 1);
      glVertex3f(l1[i][0],l1[i][1],l1[i][2]);
  }
  glNormal3f(-l2[0][1], l2[0][0], 1);
  glVertex3f(l2[0][0],l2[0][1],l2[0][2]);
  glNormal3f(-l1[0][1], l1[0][0], 1);
  glVertex3f(l1[0][0],l1[0][1],l1[0][2]);
  
  glEnd();
  
  glColor3f(1,1,1);
  glNormal3f(0, 0, 1);
  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i < l0.size(); i++) {

      glNormal3f(-l3[i][1], l3[i][0], 1);
      glVertex3f(l3[i][0],l3[i][1],l3[i][2]);

      glNormal3f(-l2[i][1], l2[i][0], 1);
      glVertex3f(l2[i][0],l2[i][1],l2[i][2]);
  }
  glNormal3f(-l3[0][1], l3[0][0], 1);
  glVertex3f(l3[0][0],l3[0][1],l3[0][2]);
  glNormal3f(-l2[0][1], l2[0][0], 1);
  glVertex3f(l2[0][0],l2[0][1],l2[0][2]);
  glDisable(GL_TEXTURE_2D); 
  glEnd();
  */
  /*
 glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(l0[0][0],l0[0][1],l0[0][2]);
  glVertex3f(l1[0][0],l1[0][1],l1[0][2]);

  for (int i = 1; i < l1.size()/2; i++) {

      glVertex3f(l0[2*i-1][0],l0[2*i-1][1],l0[2*i-1][2]);
          glVertex3f(l1[i][0],l1[i][1],l1[i][2]);
          glVertex3f(l0[2*i][0],l0[2*i][1],l0[2*i][2]);

  }
  glEnd();
  l0.clear();
  l1.clear();*/
}

Vector3 Track::getPoint(GLfloat &t, GLfloat step, int &curve)
{
  //check if the tstep needs to be reset
  if (t + step > 1) {
    //loop back eyeCurve to first curve on the track
    if (curve == curves.size() - 1) curve = 0;
    else curve++;
    t = step - (1 - t);
  }
  else t = t + step;
  return curves[curve]->getPoint(t);
}


Vector3 genInner(Vector3 v1, Vector3 v2){
        Vector3 v3(0,0,0);
        return v3;

}

Vector3 calcNormal(Vector3 v1){
  Vector3 vec, norm;
  /**
  Vector4 test1, test2, test3, test4;

  Matrix4 r;




 
      vec = v1;
      norm = Vector3(-v1[1], v1[0], 0);




      norm.normalize();



      test1 = Vector4(v1[0], v1[1], v1[2], 1);
      test3 = Vector4(norm[0], norm[1], norm[2], 1);

      test1 = r * test1;

      test3 = r * test3;


      norm = Vector3(test3[0], test3[1], test3[2]);


      */ return vec;





}
