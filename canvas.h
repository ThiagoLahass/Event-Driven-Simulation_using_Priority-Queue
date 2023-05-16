#ifndef CANVAS_H
#define CANVAS_H

/*
 * Inicializa o canvas e já executa a função principal de simulação.
 * A função 'prepare' precisa ser chamada antes desta.
 */
void canvas_init();

/*
 * Limpa todo o canvas para ser redesenhado depois.
 */
void canvas_clear();

/*
 * Atualiza na tela as modificações que foram feitas no canvas.
 */
void canvas_show();

/*
 * Pausa a execução do programa por 't' milisegundos, para permitir a
 * visualização da animação.
 */
void canvas_pause(int t);

/*
 * Desenha a partícula com as informações dadas.
 */
void filled_circle(double rx, double ry, double radius, int r, int g, int b);

#endif
