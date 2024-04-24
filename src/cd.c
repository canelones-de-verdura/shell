#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool shell_builtin_cd(char **args) {
    /* No recibió argumentos */
    if (args[1] == NULL) {
        if (chdir(getenv("HOME")) != 0)
            /* Falló el cambiazo */
            goto failure;

        if (setenv("PWD", getenv("HOME"), 1) == -1)
            goto failure;

        return true;
    }

    /* Recibió argumentos */
    if ((chdir(args[1]) == 0) && (setenv("PWD", args[1], 1) == 0))
        return true;

    /* Buena idea o asquerosidad? */
failure:
    perror("shell_cd()");
    return false;
}
