// #*-------------------------------------------------------+
// #|          Trabalho de Computação Gráfica               |
// #|				                 		                |
// #| Implementado por Gabriel De Paula e Guilherme Francis |
// #|					      		                        |
// #+-------------------------------------------------------+ 

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h> 

#define MESA 1
#define CADEIRA 2

float angle = 0.0;       // Ângulo de rotacao da câmera
float cameraHeight = 10.0; // Altura inicial da câmera
float zoom = 45.0;       // Campo de visão inicial (zoom)


void initMesa(void) {
    glNewList(MESA, GL_COMPILE);

    // Tampo da mesa
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0); 
    glScalef(6.0, 0.33, 3.5); // Proporcao da tampa
    glutWireCube(1.0);
    glPopMatrix();

    // Pernas da mesa 
    float posX = 2.2; // Posicao X das pernas 
    float posZ = 1.3; // Posicao Z das pernas 
    float legHeight = 2.5; // Altura das pernas
    float legThickness = 0.33; // Espessura das pernas

    // Perna frontal esquerda
    glPushMatrix();
    glTranslatef(-posX, -legHeight/2, posZ);
    glScalef(legThickness, legHeight, legThickness);
    glutWireCube(1.0);
    glPopMatrix();

    // Perna frontal direita
    glPushMatrix();
    glTranslatef(posX, -legHeight/2, posZ);
    glScalef(legThickness, legHeight, legThickness);
    glutWireCube(1.0);
    glPopMatrix();

    // Perna traseira esquerda
    glPushMatrix();
    glTranslatef(-posX, -legHeight/2, -posZ);
    glScalef(legThickness, legHeight, legThickness);
    glutWireCube(1.0);
    glPopMatrix();

    // Perna traseira direita
    glPushMatrix();
    glTranslatef(posX, -legHeight/2, -posZ);
    glScalef(legThickness, legHeight, legThickness);
    glutWireCube(1.0);
    glPopMatrix();

    glEndList();
}

void initCadeira(void) {
    glNewList(CADEIRA, GL_COMPILE);

    // Assento da cadeira
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0); // Posicao do assento
    glScalef(1.5, 0.15, 1.5);    // Dimensoes para o assento
    glutWireCube(1.0);
    glPopMatrix();

    // Pernas da cadeira
    float legHeight = 1.0;       // Altura para as pernas
    float legThickness = 0.15;   // Espessura para as pernas
    float offset = 0.7;          // Posicionamento das pernas
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * offset, legHeight / 2, j * offset);        // Mesma forma para fazer os pes da mesa so que em forma de laço
            glScalef(legThickness, legHeight, legThickness);
            glutWireCube(1.0);
            glPopMatrix();
        }
    }

    // Encosto da cadeira
    glPushMatrix();
    glTranslatef(0.0, 1.8, -0.75); // Posicao do encosto
    glScalef(1.5, 1.5, 0.1);      // Dimensoes para o encosto
    glutWireCube(1.0);
    glPopMatrix();

    glEndList();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    initMesa();
    initCadeira();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();

    // Define a posicao da câmera com rotacao
    gluLookAt(10.0 * cos(angle), cameraHeight, 10.0 * sin(angle),  // Posicao da câmera
              0.0, 0.0, 0.0,   // Ponto central da visão
              0.0, 1.0, 0.0);  // Vetor Up

    // Desenha a MESA
    glPushMatrix();
    glCallList(MESA);
    glPopMatrix();

    // Desenha a CADEIRA
    glPushMatrix();
    glTranslatef(0.0, -2.5, -4.0); // Posiciona a cadeira ao lado da mesa
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
    gluLookAt(10.0 * cos(angle), cameraHeight, 10.0 * sin(angle),  // Posicao da camera
              0.0, 0.0, 0.0,   // Ponto central da visão
              0.0, 1.0, 0.0);  // Vetor Up
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'a': // Gira a camera para a esquerda
            angle -= 0.1; 
            glutPostRedisplay();
            break;
        case 'd': // Gira a camera para a direita
            angle += 0.1; 
            glutPostRedisplay();
            break;
        case 'w': // Sobe a camera
            cameraHeight += 0.5; 
            glutPostRedisplay();
            break;
        case 's': // Desce a camera
            cameraHeight -= 0.5; 
            glutPostRedisplay();
            break;
        case 'z': // Zoom in
            zoom = fmax(zoom - 5.0, 5.0); 
            glutPostRedisplay();
            break;
        case 'x': // Zoom out
            zoom = fmin(zoom + 5.0, 175.0); 
            glutPostRedisplay();
            break;

    }
    glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mesa");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
