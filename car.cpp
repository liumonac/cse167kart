//
//  car.cpp
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 12/2/13
//
//  Modified: 12/7/13
//

#include "car.h"

car::car(float size) {
  t = 0.06;
  curve = 0;
  xpos = 0.0;
  zpos = 0.0;
  scale = 0.8/size;
  fire = new FireCone();
}

void car::calculateBoundingSphere() {
  GLdouble winX, winY, winZ;
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];

  glGetDoublev( GL_PROJECTION_MATRIX, projection );
  glGetIntegerv( GL_VIEWPORT, viewport );
  glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

  gluProject(0.0, 0.0, 0.0, modelview, projection, viewport, &winX, &winY, &winZ);

//r2 and r3 discarded
  GLdouble radius, r1, r2, r3;
  gluProject(xr, 0.0, 0.0, modelview, projection, viewport, &r1, &r2, &r3);

  bounding = Vector4(winX, winY, winZ, r1-winX);
}

void car::draw() {
  glMatrixMode(GL_MODELVIEW);

//move the car
  glTranslatef(forwardTrans[0], forwardTrans[1], forwardTrans[2]);  
  glTranslatef(0.0, 0.0, zpos);
  glScalef(scale, scale, scale);

//orient the car to face the right direction
  glRotatef(90, 1.0, 0.0, 0.0);
  glRotatef(180, 0.0, 1.0, 0.0);

//hacky adjustments of rotation
  if (curve%2 == 1) glRotatef(180*t, 0.0, 1.0, 0.0);
  if (curve > 1) glRotatef(180, 0.0, 1.0, 0.0);
  float check = prevT[2] - forwardTrans[2];
  glRotatef(-check*600, 1.0, 0.0, 0.0);

  glTranslatef(xpos, 0.0, 0.0);
//draw car
  glColor3f(1, 1, 1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);
  glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, indices);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_NORMAL_ARRAY);

  calculateBoundingSphere();

  glPushMatrix();
  glTranslatef(0.5*xmax, ymin*scale, -zmin);
  fire->draw();
  glPopMatrix();

  glTranslatef(0.5*xmin, ymin*scale, -zmin);
  fire->draw();
}

void car::moveSide(GLfloat xtrans) {
  xpos += xtrans;
  if (xpos < -3.7) xpos = -3.7;
  if (xpos > 3.7) xpos = 3.7;
}

void car::moveForward(Vector3 v) {
  prevT = forwardTrans;
  forwardTrans = v;
}

void car::findMinMax() {
  int j = 0;
  for (int i = 0; i < nVerts; i++) {
    j = i * 3;
    if (vertices[j] > xmax) {
      xmax = vertices[j];
    } else if (vertices[j] < xmin) {   
      xmin = vertices[j];
    }
    if (vertices[j+1] > ymax) {
      ymax = vertices[j+1];
    } else if (vertices[j+1] < ymin) {
      ymin = vertices[j+1];
    }
    if (vertices[j+2] > zmax) {
      zmax = vertices[j+2];
    } else if (vertices[j+2] < zmin) {
      zmin = vertices[j+2];
    } 
  }
  zpos = -zmin*scale*.5;

  float xdiff = xmax - xmin;
  float ydiff = ymax - ymin;
  float zdiff = zmax - zmin;

  xr = xdiff/2;
  yr = ydiff/2;
  zr = zdiff/2; 
}

Vector4 car::getBoundingSphere() {
  return bounding;
}

void car::reset() {
  t = 0.06;
  curve = 0;
  xpos = 0;
}
