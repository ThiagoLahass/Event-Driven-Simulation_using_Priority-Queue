#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "PQ.h"

#define greater(A, B)   (compare(A, B) > 0)
#define exch(A, B)      { Event *t = A; A = B; B = t; }

// TODO: Aqui você deve implementar uma fila com prioridade mínima para
//       ordenar os eventos por tempo, isto é, o evento com o menor tempo tem
//       a maior prioridade. Veja as funções definidas em 'event.h' para
//       a manipulação das estruturas de evento. A princípio, as funções já
//       existentes em 'event.h' são suficientes para implementar a simulação,
//       isto é, você não precisa implementar mais nada lá.
//
//       Você é livre para implementar a fila com prioridade da forma que quiser
//       mas é recomendado usar um min-heap para obter um bom desempenho. As
//       simulações maiores geram uma quantidade grande de eventos: um
//       limite superior frouxo (mas seguro) para o número máximo simultâneo de
//       eventos é N^3, aonde N é o número de partículas.

struct pq {
    Event** events; //min-heap
    int size;       //numero de elementos atual
    int N;          //numero MAX de elementos
};


/*
 * Cria uma nova fila de prioridade mínima com o limite de elementos informado.
 */
PQ* PQ_create(int max_N) {
    PQ* pq = malloc(sizeof *pq);

    pq->N = max_N+1;
    pq->events = calloc(pq->N, sizeof(Event*));
    pq->size = 0;

    return pq;
}

/*
 * Libera a memória da fila.
 */
void PQ_destroy(PQ *pq) {
    for( int i = 1; i <= pq->size; i++ ){
        destroy_event(pq->events[i]);
    }
    free(pq->events);
    free(pq);
}

static void fix_up( PQ* pq, int k ){
    Event** a = pq->events;
    while (k > 1 && greater(a[k/2],a[k])) {
        exch(a[k/2], a[k]);
        k = k/2;
    }
}

static void fix_down( PQ* pq, int k ){
    Event** a = pq->events;
    while ( 2*k < pq->size ){
        int j = 2*k;
        if ( j < pq->size && greater( a[j], a[j+1])){
            j++;
        }
        if(!greater(a[k], a[j])){
            break;
        }
        exch(a[k], a[j]);
        k = j;
    } 
}

/*
 * Insere o evento na fila segundo o seu tempo.
 */
void PQ_insert(PQ *pq, Event *e) {
    if( pq->size == pq->N ){
        fprintf(stderr, "ERRO: Queue is full (%d)!\n", pq->size);
        exit(EXIT_FAILURE);
    }
    pq->size++;
    pq->events[pq->size] = e;
    fix_up(pq, pq->size);
}

/*
 * Remove e retorna o evento mais próximo.
 */
Event* PQ_delmin(PQ *pq) {
    if(pq->size == 0 ){
        fprintf(stderr, "ERRO: Queue is empty!\n");
    }
    Event* e = pq->events[1];
    pq->events[1] = pq->events[pq->size];
    pq->events[pq->size] = NULL;
    pq->size--;
    fix_down(pq, 1);
    return e;
}

/*
 * Testa se a fila está vazia.
 */
bool PQ_is_empty(PQ *pq) {
    return pq->size == 0;
}

/*
 * Retorna o tamanho da fila.
 */
int PQ_size(PQ *pq) {
    return pq->size;
}
