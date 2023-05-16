#include <stdlib.h>
#include "canvas.h"
#include "colsys.h"

#define MAX_SIM_TIME 10000
#define GUI 1                // Modifique para 0 se não quiser a janela.

int main(int argc, char* argv[]) {
    system_init(atoi(argv[1]), MAX_SIM_TIME, GUI);

    if (argc == 3) {
        load_particles(argv[2]);
    } else {
        create_random_particles();
    }

    prepare();

    if (GUI) {
        canvas_init(); // Já chama simulate().
    } else {
        simulate();
    }

    system_finish();
}
