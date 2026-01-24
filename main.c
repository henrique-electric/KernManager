#include <argp.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

struct argp_option options[] = {
    {.key = 'd', .name = "download", .arg = "VERSION", .doc = "Downloads a new kernel source from kernel.org"},
    {.key = 'b', .name = "build", .arg = "VERSION", .doc = "Builds the given version kernel"},
    {NULL},
};

error_t parser(int key, char *arg, struct argp_state *state) {

    if (state->argc == 1) {
        argp_help(state->root_argp, stdout, ARGP_HELP_STD_HELP, "KernManager");
        exit(EXIT_FAILURE);
    }
    
    switch (key)
    {
    case 'd':
        ;
        break;
    
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

struct argp argp_struct = {
    .options = options,
    .parser = parser
};

int main(int argc, char *argv[])
{
    return argp_parse(&argp_struct, argc, argv, 0, 0, 0);;
}
