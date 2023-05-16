#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "canvas.h"
#include "particle.h"

struct particle {
    double rx, ry;      // Posição
    double vx, vy;      // Velocidade
    double radius;      // Raio
    double mass;        // Massa
    int r, g, b;        // Cor
    int count;          // Número de colisões
};

/*
 * Inicializa uma partícula com os parâmetros fornecidos.
 */
Particle* create_particle(double rx, double ry, double vx, double vy,
                          double radius, double mass, int r, int g, int b) {
    Particle *p = malloc(sizeof *p);
    p->rx = rx;
    p->ry = ry;
    p->vx = vx;
    p->vy = vy;
    p->radius = radius;
    p->mass = mass;
    p->r = r;
    p->g = g;
    p->b = b;
    p->count = 0;
    return p;
}

/*
 * Inicializa uma partícula com posição e velocidades aleatórias.
 */
Particle* create_random_particle() {
    double rx = drand48();
    double ry = drand48();
    double vx = -0.005 + (drand48() / 100); // uniform(-0.005, 0.005);
    double vy = -0.005 + (drand48() / 100); // uniform(-0.005, 0.005);
    double radius = 0.01;
    double mass = 0.5;
    int r = 0;
    int g = 0;
    int b = 0;
    return create_particle(rx, ry, vx, vy, radius, mass, r, g, b);
}

/*
 * Libera a memória ocupada por essa partícula.
 */
void destroy_particle(Particle *p) {
    free(p);
}

/*
 * Retorna o número de colisões da partícula até o momento.
 */
int hit_count(Particle *p) {
    return p->count;
}

/*
 * Desenha a partícula no canvas.
 */
void draw_particle(Particle *p) {
    /*printf("PARTICLE: %lf %lf %lf %lf %lf %lf %d %d %d\n",
               p->rx, p->ry, p->vx, p->vy, p->radius, p->mass,
               p->r, p->g, p->b);*/
    filled_circle(p->rx, p->ry, p->radius, p->r, p->g, p->b);
}

/*
 * Move a partícula em uma linha reta (baseado na sua velocidade) pelo
 * período de tempo 'dt' especificado.
 */
void move_particle(Particle *p, double dt) {
    p->rx += p->vx * dt;
    p->ry += p->vy * dt;
}

/*
 * Retorna a quantidade de tempo que falta até que as partículas 'p' e 'q'
 * colidam, assumindo nenhuma interferência por outra colisão.
 * Se as partículas não vão colidir, retorna INFINITY.
 */
double time_to_hit(Particle *p, Particle *q) {
    if (p == q) return INFINITY;
    double dx = q->rx - p->rx;
    double dy = q->ry - p->ry;
    double dvx = q->vx - p->vx;
    double dvy = q->vy - p->vy;
    double dvdr = dx*dvx + dy*dvy;
    if (dvdr > 0) return INFINITY;
    double dvdv = dvx*dvx + dvy*dvy;
    if (dvdv == 0) return INFINITY;
    double drdr = dx*dx + dy*dy;
    double sigma = p->radius + q->radius;
    double d = (dvdr*dvdr) - dvdv * (drdr - sigma*sigma);
    if (d < 0) return INFINITY;
    return -(dvdr + sqrt(d)) / dvdv;
}

/*
 * Retorna a quantidade de tempo que falta até que a partícula 'p' colidir com
 * uma parede vertical, assumindo nenhuma interferência por outra colisão.
 * Se a partícula não vai colidir, retorna INFINITY.
 */
double time_to_hit_vertical_wall(Particle *p) {
    if      (p->vx > 0) return (1.0 - p->rx - p->radius) / p->vx;
    else if (p->vx < 0) return (p->radius - p->rx) / p->vx;
    else                return INFINITY;
}

/*
 * Retorna a quantidade de tempo que falta até que a partícula 'p' colidir com
 * uma parede horizontal, assumindo nenhuma interferência por outra colisão.
 * Se a partícula não vai colidir, retorna INFINITY.
 */
double time_to_hit_horizontal_wall(Particle *p) {
    if      (p->vy > 0) return (1.0 - p->ry - p->radius) / p->vy;
    else if (p->vy < 0) return (p->radius - p->ry) / p->vy;
    else                return INFINITY;
}

/*
 * Atualiza as velocidades das partículas 'p' e 'q' segundo as leis de colisão
 * elástica. Assume que as partículas estão colidindo nesse exato instante.
 */
void bounce_off(Particle *p, Particle *q) {
    double dx = q->rx - p->rx;
    double dy = q->ry - p->ry;
    double dvx = q->vx - p->vx;
    double dvy = q->vy - p->vy;
    double dvdr = dx*dvx + dy*dvy;
    // Distância entre os centros das partículas no momento da colisão.
    double dist = p->radius + q->radius;

    // Magnitude da força normal.
    double magnitude = 2 * p->mass * q->mass * dvdr /
                       ((p->mass + q->mass) * dist);
    // Força normal, nas direções x e y.
    double fx = magnitude * dx / dist;
    double fy = magnitude * dy / dist;

    // Atualiza as velocidades de acordo com a força normal.
    p->vx += fx / p->mass;
    p->vy += fy / p->mass;
    q->vx -= fx / q->mass;
    q->vy -= fy / q->mass;

    // Atualiza a contagem de colisões.
    p->count++;
    q->count++;
}

/*
 * Atualiza a velocidade da partícula 'p' devido a uma colisão com uma parede
 * vertical (refletindo a velocidade na direção x). Assume que a colisão está
 * acontecendo nesse exato instante.
 */
void bounce_off_vertical_wall(Particle *p) {
    p->vx = -(p->vx);
    p->count++;
}

/*
 * Atualiza a velocidade da partícula 'p' devido a uma colisão com uma parede
 * horizontal (refletindo a velocidade na direção x). Assume que a colisão está
 * acontecendo nesse exato instante.
 */

void bounce_off_horizontal_wall(Particle *p) {
    p->vy = -(p->vy);
    p->count++;
}
