#include "../include/objeto_taca.h"

#include <GL/glut.h>

void initTaca(void) {
    glNewList(TACA, GL_COMPILE);

    GLUquadricObj *cone = gluNewQuadric();
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0, -0.6);
    gluCylinder(cone, 0.33, 0.05, 0.5, 10, 1);
    glPopMatrix();           // Restore the previous matrix state
    gluDeleteQuadric(cone);  // Delete the quadric object

    GLUquadricObj *handle = gluNewQuadric();
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0, -0.1);
    gluCylinder(handle, 0.05, 0.05, 0.5, 10, 1);
    glPopMatrix();             // Restore the previous matrix state
    gluDeleteQuadric(handle);  // Delete the quadric object

    GLUquadricObj *base = gluNewQuadric();
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0, 0.4);
    gluCylinder(base, 0.1, 0.1, 0.05, 10, 1);
    glPopMatrix();           // Restore the previous matrix state
    gluDeleteQuadric(base);  // Delete the quadric object

    glEndList();
}