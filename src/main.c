#include "exec.h"
#include "utils.h"
#include <pwd.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool shell_setup() {
    /* Agarramos el directorio del usuario */
    char *HOME = getpwuid(getuid())->pw_dir;
    if (HOME == NULL)
        goto failure; // Esperemos que lo haya agarrado

    /* Vamos para ahí */
    if (chdir(HOME) != 0)
        goto failure;

    /* Cambiamos las variables de entorno para refeljar dónde estamos */
    if (setenv("HOME", HOME, 1) == 0 && setenv("PWD", HOME, 1) == 0)
        return true;

    /* Buena idea? */
failure:
    perror("shell_setup()");
    return false;
}

void shell_loop() {
    char *line;
    char **args;
    char *promt;
    bool running = true;

    while (running) {
        /* MUY importante que cada cosito sea su propia variable y no quede
         * func1(func2(fun3())) => Después queda memoria boyando por todos
         * lados.
         */
        promt = get_promt();
        line = readline(promt);
        args = split_line(line);
        running = shell_exec(args);

        free(line);
        free(args);
        free(promt);
    }
}

int main(int argc, char **argv) {
    /* setup */
    if (!shell_setup()) {
        fprintf(stderr, "Error - Failure to initialize. Stopping...\n");
        exit(EXIT_FAILURE);
    }

    /* loop principal */
    shell_loop();

    /* cleanup */
    /* por ahora nada :^) */
    return 0;
}
