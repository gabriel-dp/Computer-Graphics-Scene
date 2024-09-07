#include "../include/objeto_taca.h"

#include <GL/glut.h>

void initTaca(void) {
    glNewList(TACA, GL_COMPILE);

    glColor3f(0.7, 0.7, 0.7);  // Cinza clarinho

    // Bojo
    GLUquadricObj *bojo = gluNewQuadric();
    glPushMatrix();
    glRotatef(90, 1, 0, 0);                     // Vertical
    glTranslatef(0, 0, -0.6);                   // Topo
    gluCylinder(bojo, 0.33, 0.05, 0.5, 20, 1);  // Tronco de cone
    gluDisk(bojo, 0, 0.33, 20, 1);              // Fechando o fundo do bojo
    glPopMatrix();
    gluDeleteQuadric(bojo);

    // Haste
    GLUquadricObj *haste = gluNewQuadric();
    glPushMatrix();
    glRotatef(90, 1, 0, 0);                      // Vertical
    glTranslatef(0, 0, -0.1);                    // Meio
    gluCylinder(haste, 0.05, 0.05, 0.5, 10, 1);  // Ciclindro longo
    glPopMatrix();
    gluDeleteQuadric(haste);

    // Base
    GLUquadricObj *base = gluNewQuadric();
    glPushMatrix();
    glRotatef(90, 1, 0, 0);                    // Vertical
    glTranslatef(0, 0, 0.4);                   // Baixo
    gluCylinder(base, 0.1, 0.1, 0.05, 10, 1);  // Cilindro curto e largo
    gluDisk(base, 0, 0.1, 10, 1);              // Fechando o fundo da base
    glPopMatrix();
    gluDeleteQuadric(base);

    glEndList();
}
