#include "values.h"
#include <stdbool.h>
#include <stdio.h>

int shell_builtin_help(char **args) {
    printf("Attempt at a *NIX shell - ");
    printf("Recieves commands and does what it can.\n");
    printf("\nThe following commands are available:\n");
    printf("\t- help (This one!!)\n");
    printf("\t- cd\n");
    printf("\t- pwd\n");
    printf("\t- exit\n");
    return FUNCTION_OK;
}
