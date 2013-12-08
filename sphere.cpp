//
//  sphere.cpp
//  cse167kart
//
//  Authors: Nick Troast, Monica Liu, Andrew Lin
//  Created: 12/2/13
//
//  Modified: 12/7/13
//

#include "geode.h"

class sphere : public geode {
  private:void calculateBoundingSphere() {
    GLdouble winX, winY, winZ;
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];

    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

    GLdouble r1, r2, rad;
    gluProject(0.0, 0.0, 0.0, modelview, projection, viewport, &winX, &winY, &winZ);
    gluProject(r, 0.0, 0.0, modelview, projection, viewport, &rad, &r1, &r2);

    bounding = Vector4(winX, winY, winZ, std::abs(rad-winX));
  }

  public: sphere(float radius, Vector3 pos) {
    trans = pos;
    r = radius;
  }

  public: void draw() {
    glTranslatef(trans[0], trans[1], trans[2]+r);   
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(r, 10.0, 10.0);
    calculateBoundingSphere();
    glTranslatef(-trans[0], -trans[1], -(trans[2]+r));
  }

  public: Vector4 getBoundingSphere() {
    return bounding;
  }
};
