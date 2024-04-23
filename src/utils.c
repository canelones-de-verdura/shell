#include "values.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Separamos líneas según los espacios en blanco
// TODO: Permitir espacios en blanco al usar "" o \ .
#define TOKEN_DELIMITER " \t\r\n\a"

/*
 * Recé un rosario antes de ponerme a manipular strings. Espero que sea suficiente
 */
char *get_promt() {
    char *home_in_current_dir = strstr(current_dir, home_dir);

    char *promt = malloc(STR_SIZE * sizeof(char));
    if (home_in_current_dir == NULL) {
        strcpy(promt, current_dir);
    } else {
        promt[0] = '~';
        promt[1] = '\0';
        // Padre nuestro, que estás en el cielo...
        char* relative_path = current_dir + sizeof(home_dir) + 1;
        strcat(promt, relative_path);
    }
    
    strcat(promt, "> ");

    return promt;
}

char **split_line(char *line) {
    // Implementamos un array dinámico para ir guardando los argumentos
    char **t_array = malloc(STR_SIZE * sizeof(char *));
    int t_size = STR_SIZE;
    int t_tail = 0;
    char *token;

    // Reventamos todo si malloc se caga
    if (t_array == NULL) {
        fprintf(stderr, "msh_splitline: malloc se cagó\n");
        abort();
    }
    
    token = strtok(line, TOKEN_DELIMITER);
    while(token != NULL) {
        t_array[t_tail] = token;
        ++t_tail;

        if (t_tail > t_size) {
            t_size += STR_SIZE;
            t_array = realloc(t_array, t_size);
            // Reventamos todo si realloc se caga
            if (t_array == NULL) {
                fprintf(stderr, "msh_splitline: realloc se cagó\n");
                abort();
            }
        }
        // Al pasarle NULL sigue trabajando sobre el string anterior
        token = strtok(NULL, TOKEN_DELIMITER);
    }

    t_array[t_tail] = NULL; // Terminamos, todo pronto para ejecutar
    return t_array;
}
