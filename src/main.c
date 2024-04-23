#include "exec.h"
#include "utils.h"
#include "values.h"
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *home_dir;
char current_dir[STR_SIZE];

bool shell_setup() {
    /* Agarramos el directorio del usuario */
    home_dir = get_home();
    if (!home_dir)
        return false; // O nos vamos si no quiere funcar

    /* Nos cambiamos para ahí */
    strcpy(current_dir, home_dir);
    if (chdir(current_dir) != 0) {
        perror("shell_setup(): ");
        return false;
    }

    return true;
}

void shell_loop() {
    char *line;
    char *promt;
    bool running = true;

    while (running) {
        promt = get_promt();
        line = readline(promt);
        running = shell_exec(split_line(line));
    }

    free(line);
    free(promt);
}

int main(int argc, char **argv) {
    /* setup */
    if (!shell_setup()) {
        fprintf(stderr, "Error - Failure to initialize. Stopping...\n");
        exit(EXIT_FAILURE);
    }

    /* loop */
    shell_loop();

    /* cleanup */
    /* por ahora nada :^) */
    return 0;
}
