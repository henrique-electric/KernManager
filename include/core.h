#ifndef CORE_H
#define CORE_H
#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <string.h>
#include <stdint.h>

#define ERROR_HANDLE_LINK -1
#define SUCCESS_HANDLE_LINK 0

#define ERROR_DOWNLOAD_KERNEL -1
#define SUCCESS_DOWNLOAD_KERNEL 0

struct kernel_version {
    int major;
    int middle;
    int minor;

    int numbers_middle; // how many numbers there is on the middle ex.: 6.18.7 ---> X.18.X ---> 2
};

struct kernel_version parse_version(char *version);
error_t parser(int key, char *arg, struct argp_state *state);
error_t parse_args(int argc, char *argv[]);
int handle_link(const struct kernel_version *kversion);
int download_kernel(char *link);

extern struct argp_option options[];
extern struct argp argp_struct;
extern const char *kernel_url;

#endif