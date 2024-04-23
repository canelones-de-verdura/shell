#include "values.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool shell_builtin_cd(char **args) {
    if (args[1] == NULL)
        if (chdir(home_dir) != 0)
            perror("shell_cd(): ");

    if (chdir(args[1]) != 0) {
        perror("shell_cd(): ");
    } else {
        strcpy(current_dir, args[1]);
    }

    return true;
}
