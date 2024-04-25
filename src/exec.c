/* Built-in commands */
#include "cd.h"
#include "exit.h"
#include "help.h"
#include "values.h"
/* Stuff */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

/* Array de strings que indican los comandos disponibles.
 * Por simpicidad, los pongo en orden alfabético.
 */
char *builtin_commands[] = {"cd", "exit", "help"};

/* ARRAY DE PUNTEROS DE FUNCIONES. Buena idea o una cagada? No sé.
 * IMPORTANTE: Las funciones se tienen que poner en el mismo orden que los
 * comandos correspondientes en *builtin_commands[].
 */
int (*builtin_functions[])(char **) = {&shell_builtin_cd, &shell_builtin_exit,
                                       &shell_builtin_help};

/* Cantidad de funciones disponibles */
int builtins() { return sizeof(builtin_commands) / sizeof(char *); }

bool shell_run_program(char **args) {
    pid_t child_pid;
    pid_t wait_pid;
    int exec_flag;
    int status;

    child_pid = fork();
    if (child_pid < 0) {
        // No pudo forkear
        perror("shell_run_program()");
    }
    if (child_pid == 0) {
        // Entra si es el hijo recién creado
        // execvp recibe los argumentos a través de un array de arrays
        // de chars. Muy conveniente.
        exec_flag = execvp(args[0], args);
        if (exec_flag) {
            // Si exec funca, no va a llegar al if.
            // Por eso chequeo por cualquier valor
            perror("shell_run_program()");
            exit(1);
        }
    } else {
        // Acá entra el padre
        do {
            /* waitpid pude volver por cualquier motivo, así que lo volvemos
             * a llamar hasta que retorne en las condiciones que queremos
             */
            wait_pid = waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return true; // Solo para indicar que podemos pedir input de nuevo
}

bool shell_exec(char **args) {
    if (args[0] == NULL)
        return true;

    /* Revisamos en las builtin */
    for (int i = 0; i < builtins(); ++i) {
        if (strcmp(args[0], builtin_commands[i]) == 0) {
            switch ((*builtin_functions[i])(args)) {
            case FUNCTION_OK:
                return true;
            case FUNCTION_ERROR:
                perror(builtin_commands[i]);
                return true;
            case EXIT_SIGNAL:
                return false;
            case SYSTEM_ERROR:
                perror(builtin_commands[i]);
                return false;
            }
        }
    }

    /* Si no, llamamos exec() */
    return shell_run_program(args);
}
