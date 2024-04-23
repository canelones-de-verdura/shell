#include "values.h"
#include "utils.h"
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

const char* home_dir;
char current_dir[STR_SIZE];

bool shell_setup() {
    /* Agarramos el directorio del usuario */
    if((home_dir = getenv("HOME")) == NULL)
        if((home_dir = getpwuid(getuid())->pw_dir) == NULL)
            return false;

    /* Nos cambiamos para ahí */
    strcpy(current_dir, home_dir);
    if (chdir(current_dir) != 0) {
        perror("shell_setup()");
        return false;
    }

    return true;
}

void shell_loop() {
    char *line;
    char *promt;

    while (true) {
        promt = get_promt();
        line = readline(promt);
        //status = shell_exec(split_line(line));
        // if (status == ...
    }

    free(line);
    free(promt);
}

int main(int argc, char **argv) {
    /* setup */
    if (!shell_setup()) {
        fprintf(stderr, "Error - Failure to initialize. Stopping...");
        exit(EXIT_FAILURE);
    }

    /* loop */
    shell_loop();

    /* cleanup */
    /* por ahora nada :^) */
    return 0;
}
