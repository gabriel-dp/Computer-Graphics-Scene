#include "../include/objeto_cadeira.h"

#include <GL/glut.h>

void initCadeira(void) {
    glNewList(CADEIRA, GL_COMPILE);

    // Assento
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);  // Posicao do assento
    glScalef(1.5, 0.15, 1.5);     // Dimensoes para o assento
    glutWireCube(1.0);
    glPopMatrix();

    // Dimensoes das pernas
    float legHeight = 1.0;      // Altura para as pernas
    float legThickness = 0.15;  // Espessura para as pernas
    float offset = 0.7;         // Posicionamento das pernas

    // Mesma forma para fazer os pes da mesa so que em forma de laço
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * offset, legHeight / 2, j * offset);
            glScalef(legThickness, legHeight, legThickness);
            glutWireCube(1.0);
            glPopMatrix();
        }
    }

    // Encosto
    glPushMatrix();
    glTranslatef(0.0, 1.8, -0.75);  // Posicao do encosto
    glScalef(1.5, 1.5, 0.1);        // Dimensoes para o encosto
    glutWireCube(1.0);
    glPopMatrix();

    glEndList();
}