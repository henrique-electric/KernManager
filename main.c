#include <argp.h>
#include <regex.h>

struct argp_option options[] = {
    {.key = 'd', .name = "download", .arg = "VERSION", .doc = "Downloads a new kernel source from kernel.org"},
    {.key = 'b', .name = "build", .arg = "VERSION", .doc = "Builds the given version kernel"},
    {NULL},
};

int main(int argc, char const *argv[])
{
    
    return 0;
}
