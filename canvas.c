#include <GL/freeglut.h>
#include <stdio.h>
#include <unistd.h>
#include "canvas.h"
#include "colsys.h"

// Tamanho do canvas em pixels.
#define H 800
#define V 600

/*
 * Inicializa o canvas e já executa a função principal de simulação.
 * A função 'prepare' precisa ser chamada antes desta.
 */
void canvas_init() {
    int argc = 1;
    char* argv[1] = {" "};
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(H, V);
    glutCreateWindow("Particle Simulation");

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                  GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    glViewport(0, 0, H, V);
    glOrtho(0, 1.0, 0, 1.0, -1.0, 1.0);

    glClearColor(1, 1, 1, 0);
    glutDisplayFunc(simulate);
    glutMainLoop();
}

/*
 * Limpa todo o canvas para ser redesenhado depois.
 */
void canvas_clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*
 * Atualiza na tela as modificações que foram feitas no canvas.
 */
void canvas_show() {
    glutSwapBuffers();
}

/*
 * Pausa a execução do programa por 't' milisegundos, para permitir a
 * visualização da animação.
 */
void canvas_pause(int t) {
    sleep(t / 1000);
}

/*
 * Desenha a partícula com as informações dadas.
 */
void filled_circle(double rx, double ry, double radius, int r, int g, int b) {
    glColor3f(r / 255.0, g / 255.0 , b / 255.0);
    glPushMatrix();
        glTranslated(rx, ry, 0);
        glutSolidSphere(radius, 50, 50);
    glPopMatrix();
}
