/* Built-in commands */
#include "cd.h"
#include "exit.h"
#include "help.h"
/* Stuff */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Array de strings que indican los comandos disponibles.
 * Por simpicidad, los pongo en orden alfabético.
 */
char *builtin_commands[] = {"cd", "exit", "help"};

/* ARRAY DE PUNTEROS DE FUNCIONES. Buena idea o una cagada? No sé.
 * IMPORTANTE: Las funciones se tienen que poner en el mismo orden que los
 * comandos correspondientes en *builtin_commands[].
 */
bool (*builtin_functions[])(char **) = {&shell_builtin_cd, &shell_builtin_exit,
                                        &shell_builtin_help};

/* Cantidad de funciones disponibles */
int builtins() { return sizeof(builtin_commands) / sizeof(char *); }

bool shell_exec(char **args) {
    if (args[0] == NULL)
        return true;

    /* Revisamos en las builtin */
    for (int i = 0; i < builtins(); ++i) {
        if (strcmp(args[0], builtin_commands[i]) == 0) {
            return (*builtin_functions[i])(args);
        }
    }

    /* Si no, llamamos exec() */
    /* PLACEHOLDER */
    return true;
}
