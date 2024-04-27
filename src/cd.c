#include "values.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int shell_builtin_cd(char **args) {
    /* No recibió argumentos, volvemos a home */
    if (args[1] == NULL) {
        if ((chdir(getenv("HOME")) != 0) ||
            (setenv("PWD", getenv("HOME"), 1) != 0))
            return SYSTEM_ERROR;

        return FUNCTION_OK;
    }

    /* Recibió argumentos */
    if (chdir(args[1]) != 0)
        /* Antes de hacer cosas raras, verificamos que es una ruta válida */
        return FUNCTION_ERROR;

    /* Actualizamos PWD */
    // Si tiene '/' al final, lo sacamos
    char *dir_ptr = &args[1][strlen(args[1]) - 1];
    if (*dir_ptr == '/')
        *dir_ptr = '\0';

    if (args[1][0] == '/') {
        /* Recibió una ruta absoluta */
        if (setenv("PWD", args[1], 1) != 0)
            return SYSTEM_ERROR;

        return FUNCTION_OK;
    }

    /* Recibió una ruta relativa */
    dir_ptr = malloc(sizeof(char) * STR_LENGTH); // Reutilizo el puntero
    strcpy(dir_ptr, getenv("PWD")); // Copiamos PWD

    // Le concatenamos la ruta rel. que recibió de parámetro.
    strcat(dir_ptr, "/");
    strcat(dir_ptr, args[1]);

    if (setenv("PWD", dir_ptr, 1) != 0)
        return SYSTEM_ERROR;

    // Limpiamos
    free(dir_ptr);

    return FUNCTION_OK;
}
