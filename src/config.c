#include <core.h>

const char *get_home_dir(void) {
    return getenv("HOME");
}

void create_config_dir(void) {
    const char *home = get_home_dir(); // Get the user home directory path

    // ========= Allocate a buffer to store the whole command to be run ========
    size_t home_path_len = strlen(home); // Lenght of the user home directory
    size_t cmd_len = strlen("mkdir /.kern 2> /dev/null"); // Combined the lenth of the command + the args
    char *cmd_buff = (char *) malloc(cmd_len + home_path_len + 1);
    if (cmd_buff == NULL)
        exit(EXIT_FAILURE);

    memset(cmd_buff, 0, home_path_len + cmd_len + 1);
    snprintf(cmd_buff, cmd_len + home_path_len  + 1, "mkdir %s/.kern 2> /dev/null", home);
    // ========================================================================

    system(cmd_buff); //Run the mkdir command on the shell

    // Free the buffer used by malloc
    free(cmd_buff);
    cmd_buff = NULL;
}

int query_config_file(const struct kernel_version *kver) {
    if (kver == NULL)
        return CONFIG_FILE_DOESNT_EXIST;


}
