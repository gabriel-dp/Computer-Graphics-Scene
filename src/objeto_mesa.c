#include "../include/objeto_mesa.h"

#include <GL/glut.h>

void initMesa(void) {
    glNewList(MESA, GL_COMPILE);

    // Tampo da mesa
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0);
    glScalef(6.0, 0.33, 3.5);  // Proporcao da tampa
    glutWireCube(1.0);
    glPopMatrix();

    // Pernas da mesa
    float posX = 2.2;           // Posicao X das pernas
    float posZ = 1.3;           // Posicao Z das pernas
    float legHeight = 2.5;      // Altura das pernas
    float legThickness = 0.33;  // Espessura das pernas

    // Perna frontal esquerda
    glPushMatrix();
    glTranslatef(-posX, -legHeight / 2, posZ);
    glScalef(legThickness, legHeight, legThickness);
    glutWireCube(1.0);
    glPopMatrix();

    // Perna frontal direita
    glPushMatrix();
    glTranslatef(posX, -legHeight / 2, posZ);
    glScalef(legThickness, legHeight, legThickness);
    glutWireCube(1.0);
    glPopMatrix();

    // Perna traseira esquerda
    glPushMatrix();
    glTranslatef(-posX, -legHeight / 2, -posZ);
    glScalef(legThickness, legHeight, legThickness);
    glutWireCube(1.0);
    glPopMatrix();

    // Perna traseira direita
    glPushMatrix();
    glTranslatef(posX, -legHeight / 2, -posZ);
    glScalef(legThickness, legHeight, legThickness);
    glutWireCube(1.0);
    glPopMatrix();

    glEndList();
}