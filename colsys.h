#ifndef COLSYS_H
#define COLSYS_H

#include <stdbool.h>

/*
 * Inicializa a simulação com o número dado de partículas e o tempo máximo.
 */
void system_init(int max_N, double max_limit, bool use_gui);

/*
 * Termina a simulação, liberando a memória usada.
 */
void system_finish();

/*
 * Carrega as informações das partículas do arquivo dado.
 */
void load_particles(char *file_name);

/*
 * Cria um conjunto de partículas com características aleatórias.
 */
void create_random_particles();

/*
 * Prepara a simulação para ser iniciada.
 */
void prepare();

/*
 * Simula o sistema de partículas pelo período de tempo especificado.
 */
void simulate();

#endif
