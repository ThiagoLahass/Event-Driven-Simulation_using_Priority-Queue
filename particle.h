#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct particle Particle;

/*
 * Inicializa uma partícula com os parâmetros fornecidos.
 */
Particle* create_particle(double rx, double ry, double vx, double vy,
                          double radius, double mass, int r, int g, int b) ;

/*
 * Inicializa uma partícula com posição e velocidades aleatórias.
 */
Particle* create_random_particle();

/*
 * Libera a memória ocupada por essa partícula.
 */
void destroy_particle(Particle *p);

/*
 * Retorna o número de colisões da partícula até o momento.
 */
int hit_count(Particle *p);

/*
 * Desenha a partícula no canvas.
 */
void draw_particle(Particle *p);

/*
 * Move a partícula em uma linha reta (baseado na sua velocidade) pelo
 * período de tempo 'dt' especificado.
 */
void move_particle(Particle *p, double dt);

/*
 * Retorna a quantidade de tempo que falta até que as partículas 'p' e 'q'
 * colidam, assumindo nenhuma interferência por outra colisão.
 * Se as partículas não vão colidir, retorna INFINITY.
 */
double time_to_hit(Particle *p, Particle *q);

/*
 * Retorna a quantidade de tempo que falta até que a partícula 'p' colidir com
 * uma parede vertical, assumindo nenhuma interferência por outra colisão.
 * Se a partícula não vai colidir, retorna INFINITY.
 */
double time_to_hit_vertical_wall(Particle *p);

/*
 * Retorna a quantidade de tempo que falta até que a partícula 'p' colidir com
 * uma parede horizontal, assumindo nenhuma interferência por outra colisão.
 * Se a partícula não vai colidir, retorna INFINITY.
 */
double time_to_hit_horizontal_wall(Particle *p);

/*
 * Atualiza as velocidades das partículas 'p' e 'q' segundo as leis de colisão
 * elástica. Assume que as partículas estão colidindo nesse exato instante.
 */
void bounce_off(Particle *p, Particle *q);

/*
 * Atualiza a velocidade da partícula 'p' devido a uma colisão com uma parede
 * vertical (refletindo a velocidade na direção x). Assume que a colisão está
 * acontecendo nesse exato instante.
 */
void bounce_off_vertical_wall(Particle *p);

/*
 * Atualiza a velocidade da partícula 'p' devido a uma colisão com uma parede
 * horizontal (refletindo a velocidade na direção x). Assume que a colisão está
 * acontecendo nesse exato instante.
 */
void bounce_off_horizontal_wall(Particle *p);

#endif
