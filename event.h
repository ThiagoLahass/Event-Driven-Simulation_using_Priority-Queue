#ifndef EVENT_T
#define EVENT_T

#include <stdbool.h>
#include "particle.h"

typedef struct event Event;

/*
 * Cria um novo evento que ocorrerá no tempo 't', envolvendo 'a' e 'b'.
 * Os ponteiros podem ser nulos. Convenção para representar diferentes tipos
 * de eventos:
 * - Se (a != NULL) && (b != NULL): colisão entre as partículas 'a' e 'b'.
 * - Se (a != NULL) && (b == NULL): colisão de 'a' com uma parede vertical.
 * - Se (a == NULL) && (b != NULL): colisão de 'b' com uma parede horizontal.
 * - Se (a == NULL) && (b == NULL): evento especial de redraw do canvas.
 */
Event* create_event(double t, Particle *a, Particle *b);

/*
 * Libera a memória ocupada por esse evento, sem desalocar as partículas.
 */
void destroy_event(Event *e);

/*
 * Retorna a primeira partícula do evento, se houver.
 */
Particle* get_A(Event *e);

/*
 * Retorna a segunda partícula do evento, se houver.
 */
Particle* get_B(Event *e);

/*
 * Retorna o instante de tempo em que o evento deve ocorrer.
 */
double get_time(Event *e);

/*
 * Compara dois eventos pelos os seus tempos.
 * Retorna um valor negativo se e.time < f.time.
 * Retorna um valor positivo se e.time < f.time.
 * Retorna zero se e.time == f.time.
 */
int compare(Event *e, Event *f);

/*
 * Testa se alguma colisão ocorreu entre a criação do evento e agora.
 * Se sim, o evento é inválido.
 */
bool is_valid(Event *e);

#endif
