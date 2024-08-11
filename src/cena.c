#include "../include/cena.h"

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "../include/objeto_cadeira.h"
#include "../include/objeto_mesa.h"

#define MAX_ANGLE_RADIANS 6.1

float angle = 0.0;          // Ângulo de rotacao da câmera
float cameraHeight = 10.0;  // Altura inicial da câmera
float zoom = 45.0;          // Campo de visão inicial (zoom)

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Cor de fundo

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    initMesa();
    initCadeira();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // Cor das linhas
    glLoadIdentity();

    // Define a posicao da câmera com rotacao
    gluLookAt(10.0 * cos(angle), cameraHeight, 10.0 * sin(angle),  // Posicao da câmera
              0.0, 0.0, 0.0,                                       // Ponto central da visão
              0.0, 1.0, 0.0);                                      // Vetor Up

    // Desenha a MESA
    glPushMatrix();
    glCallList(MESA);
    glPopMatrix();

    // Desenha a CADEIRA
    glPushMatrix();
    glTranslatef(0.0, -2.5, -4.0);  // Posiciona a cadeira ao lado da mesa
    glCallList(CADEIRA);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Projecao perspectiva
    gluPerspective(zoom, (GLfloat)w / (GLfloat)h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':  // Gira a camera para a esquerda
            angle = ((angle <= 0) ? MAX_ANGLE_RADIANS : angle - 0.1);
            break;
        case 'd':  // Gira a camera para a direita
            angle = ((angle >= MAX_ANGLE_RADIANS) ? 0 : angle + 0.1);
            break;
        case 'w':  // Sobe a camera
            cameraHeight += 0.5;
            break;
        case 's':  // Desce a camera
            cameraHeight -= 0.5;
            break;
        case 'z':  // Zoom in
            zoom = fmax(zoom - 5.0, 5.0);
            break;
        case 'x':  // Zoom out
            zoom = fmin(zoom + 5.0, 175.0);
            break;
    }
    glutPostRedisplay();
    glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}