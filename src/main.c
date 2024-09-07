// # *------------------------------------------------------+
// # |            Trabalho de Computação Gráfica            |
// # |                  Gabriel De Paula                    |
// # +------------------------------------------------------+

#include <GL/glut.h>

#include "../include/cena.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
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
