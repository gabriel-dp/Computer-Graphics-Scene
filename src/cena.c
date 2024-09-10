#include "../include/cena.h"

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "../include/objeto_cadeira.h"
#include "../include/objeto_chao.h"
#include "../include/objeto_mesa.h"
#include "../include/objeto_taca.h"

#define MAX_ANGLE_RADIANS 6.1

float angle = 0.0;          // Ângulo de rotacao da câmera
float cameraHeight = 10.0;  // Altura inicial da câmera
float zoom = 45.0;          // Campo de visão inicial (zoom)

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Cor de fundo
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Inicia todos os objetos
    initMesa();
    initCadeira();
    initChao();
    initTaca();
}

void light(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  // Luz spot para iluminar toda a cena de cima
    glEnable(GL_LIGHT1);  // Luz pontual vermelha um pouco acima da mesa, de baixa distancia de alcance

    // Propriedades luz spot
    GLfloat luzAmbienteSpot[4] = {0.5f, 0.5f, 0.5f, 1};
    GLfloat luzDifusaSpot[4] = {0.4f, 0.4f, 0.4f, 1};
    GLfloat luzEspecularSpot[4] = {1, 1, 1, 1};
    GLfloat posicaoLuzSpot[4] = {0, 12, 0, 1};
    GLfloat direcaoSpot[4] = {0, -1, 0};
    GLfloat aberturaSpot = 45.0f;

    // Inicia todas as propriedades da luz spot
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteSpot);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbienteSpot);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusaSpot);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecularSpot);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuzSpot);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcaoSpot);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, aberturaSpot);

    // Propriedades luz pontual
    GLfloat posicaoLuzPontual[4] = {0, 4, 0, 1};
    GLfloat luzAmbientePontual[4] = {0.5f, 0.5f, 0.5f, 1};
    GLfloat luzDifusaPontual[4] = {1.0f, 0.4f, 0.4f, 1.0f};
    GLfloat luzEspecularPontual[4] = {1, 1, 1, 1};

    // Inicia todas as propriedades da luz pontual
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuzPontual);
    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbientePontual);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusaPontual);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecularPontual);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.05f);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Cor dos materiais
    glEnable(GL_COLOR_MATERIAL);

    // Iluminacao
    light();

    // Profundidade
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);  // Smooth = Gouraud

    glColor3f(1.0, 1.0, 1.0);  // Cor das linhas
    glLoadIdentity();

    // Define a posicao da câmera com rotacao
    gluLookAt(10.0 * cos(angle), cameraHeight, 6.0 * sin(angle),  // Posicao da câmera
              0.0, -2, 0.0,                                       // Ponto central da visão
              0.0, 1.0, 0.0);                                     // Vetor Up

    // Desenha a MESA
    glPushMatrix();
    glCallList(MESA);
    glPopMatrix();

    // Desenha a CADEIRA
    glPushMatrix();
    glTranslatef(0.0, -2.5, -3.7);   // Ao lado da mesa
    glRotatef(45.0, 0.0, 1.0, 0.0);  // Girada
    glCallList(CADEIRA);
    glPopMatrix();

    // Desenha o CHAO
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);  // Centro da cena
    glCallList(CHAO);
    glPopMatrix();

    // Desenha a TACA
    glPushMatrix();
    glTranslatef(0, 0.75, 0);  // Acima da mesa
    glRotatef(71, 1, 0, 0);    // Derrubada
    glRotatef(55, 0, 0, 1);    // Inclinada
    glTranslatef(-1, 0, 0);    // Perto da cadeira
    glCallList(TACA);
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