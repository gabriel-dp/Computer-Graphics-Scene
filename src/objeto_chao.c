#include "../include/objeto_chao.h"

#include <GL/glut.h>

void initChao(void) {
    glNewList(CHAO, GL_COMPILE);

    glPushMatrix();
    glTranslatef(0.0, -2.7, 0.0);
    glScalef(10.0, 0.33, 10.0);  // Proporcao
    glutWireCube(1.0);
    glPopMatrix();

    glEndList();
}