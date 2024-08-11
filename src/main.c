// # *------------------------------------------------------+
// # |            Trabalho de Computação Gráfica            |
// # |         Gabriel De Paula e Guilherme Francis         |
// # +------------------------------------------------------+

#include <GL/glut.h>

#include "../include/cena.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cena");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
