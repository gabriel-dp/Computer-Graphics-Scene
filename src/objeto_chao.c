#include "../include/objeto_chao.h"

#include <GL/glut.h>

void initChao(void) {
    glNewList(CHAO, GL_COMPILE);

    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0.0, -2.7, 0.0);
    glScalef(12.0, 0.33, 12.0);  // Proporcao
    glutSolidCube(1.0);
    glPopMatrix();

    glEndList();
}