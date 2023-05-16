#include <stdlib.h>
#include "event.h"

struct event {
    double time; // Momento em que o evento está escalonado para ocorrer.
    Particle *a, *b; // Partículas envolvidas no evento. Podem ser nulas.
    int count_A, count_B; // Contadores de colisão na criação do evento.
};

/*
 * Cria um novo evento que ocorrerá no tempo 't', envolvendo 'a' e 'b'.
 * Os ponteiros podem ser nulos. Convenção para representar diferentes tipos
 * de eventos:
 * - Se (a != NULL) && (b != NULL): colisão entre as partículas 'a' e 'b'.
 * - Se (a != NULL) && (b == NULL): colisão de 'a' com uma parede vertical.
 * - Se (a == NULL) && (b != NULL): colisão de 'b' com uma parede horizontal.
 * - Se (a == NULL) && (b == NULL): evento especial de redraw do canvas.
 */
Event* create_event(double t, Particle *a, Particle *b) {
    Event *e = malloc(sizeof *e);

    e->time = t;
    e->a = a;
    e->b = b;
    if (a != NULL) e->count_A = hit_count(a);
    else           e->count_A = -1;
    if (b != NULL) e->count_B = hit_count(b);
    else           e->count_B = -1;

    return e;
}

/*
 * Libera a memória ocupada por esse evento, sem desalocar as partículas.
 */
void destroy_event(Event *e) {
    free(e);
}

/*
 * Retorna a primeira partícula do evento, se houver.
 */
Particle* get_A(Event *e) {
    return e->a;
}

/*
 * Retorna a segunda partícula do evento, se houver.
 */
Particle* get_B(Event *e) {
    return e->b;
}

/*
 * Retorna o instante de tempo em que o evento deve ocorrer.
 */
double get_time(Event *e) {
    return e->time;
}

/*
 * Compara dois eventos pelos os seus tempos.
 * Retorna um valor negativo se e.time < f.time.
 * Retorna um valor positivo se e.time < f.time.
 * Retorna zero se e.time == f.time.
 */
int compare(Event *e, Event *f) {
    return (int) (e->time - f->time);
}

/*
 * Testa se alguma colisão ocorreu entre a criação do evento e agora.
 * Se sim, o evento é inválido.
 */
bool is_valid(Event *e) {
    if (e->a != NULL && hit_count(e->a) != e->count_A) return false;
    if (e->b != NULL && hit_count(e->b) != e->count_B) return false;
    return true;
}
