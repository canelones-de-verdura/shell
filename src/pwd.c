#include "values.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int shell_builtin_pwd(char **args) {
    char *pwd = NULL;

    if (args[1] == NULL) {
        goto DEFAULT;
    }

    if (strcmp(args[1], "-P") == 0) {
        if ((pwd = getcwd(pwd, 0)) == NULL)
            return SYSTEM_ERROR;

        puts(pwd);
        free(pwd);
        return FUNCTION_OK;
    }

DEFAULT:
    if ((pwd = getenv("PWD")) == NULL)
        return SYSTEM_ERROR;
    puts(pwd);
    return FUNCTION_OK;
}
