#include <core.h>
#include <regex.h>

#define ERROR_HANDLE_LINK -1

const char *kernel_url = "https://cdn.kernel.org/pub/linux/kernel/";
int handle_link(const struct kernel_version *kversion) {
    if(!kversion)
        return ERROR_HANDLE_LINK;

    size_t kernel_url_len = strlen(kernel_url) + 1;
    size_t version_path_len = strlen("vx.x/") + 1; // x will be replaced with the major number
    size_t linux_prefix_len = strlen("linux-x") + 1;
    size_t linux_suffix_len = strlen(".tar.xz") + 1;

    size_t middle_version_len = 0;
    size_t minor_version_len = 0;
    size_t full_url_len = 0;

    char *full_url = NULL;

// Allocate a buffer to put the version path ex.: v6/. v5/ ...
    char *version_buff = (char*) malloc(version_path_len);
    memset(version_buff, 0, version_path_len);
    snprintf(version_buff, version_path_len, "v%d.x/", kversion->major);
//

    if (kversion->middle < 10)
        middle_version_len = 1;
    else
        middle_version_len = 2;

    if (kversion->minor < 10)
        minor_version_len = 1;
    else if (kversion->minor < 100)
        minor_version_len = 2;
    else
        minor_version_len = 3;

    size_t linux_tarball_file_name_len = linux_prefix_len + middle_version_len + minor_version_len + linux_suffix_len + 1;
    
// Alloc a buffer to hold the whole path
    full_url_len = kernel_url_len + version_path_len + linux_tarball_file_name_len + 1;
    full_url = (char *) malloc(full_url_len);
    memset(full_url, 0, full_url_len);
//
    snprintf(full_url, kernel_url_len, kernel_url); // Moves the kernel url "https://cdn.kernel.org/pub/linux/kernel/" to the buffer

    char *kernel_url_eo = full_url + kernel_url_len - 1; // Moves to the end of the kernel url inside the string
    snprintf(kernel_url_eo, version_path_len, version_buff); // Moves the version path to the buffer "vx/"

    kernel_url_eo = kernel_url_eo + version_path_len - 1; // Moves to the end of the version path inside inside the string
    
    if (kversion->minor != MINOR_VERSION_NOT_SPECIFIED)
        snprintf(kernel_url_eo, linux_tarball_file_name_len, "linux-%d.%d.%d.tar.xz", kversion->major, kversion->middle, kversion->minor); // Moves the linux tarball name at the end "linux-x.xx.xxx.tar.xz"

    else
        snprintf(kernel_url_eo, linux_tarball_file_name_len, "linux-%d.%d.tar.xz", kversion->major, kversion->middle);

    download_kernel(full_url);

    // Free up all malloc memory and set pointers to NULL to avoid UAF
    kernel_url_eo = NULL;
    free(version_buff);
    free(full_url);
    version_buff = NULL;
    full_url = NULL;
    return SUCCESS_HANDLE_LINK;
}

int download_kernel(char *link) {
    if(!link)
        return ERROR_DOWNLOAD_KERNEL;

    size_t command_len = strlen("wget ") + 1;
    size_t link_len = strlen(link) + 1;
    size_t command_args = strlen(" -q --tries=1 --read-timeout=4") + 1;
    size_t total_len_used = command_len + link_len + command_args;

    char *shell_command_buff = (char *) malloc(total_len_used);
    memset(shell_command_buff, 0, total_len_used);
    snprintf(shell_command_buff, total_len_used, "%s%s%s", "wget ", link, " -q --tries=1 --read-timeout=6");

    if (system(shell_command_buff) != 0) {
        free(shell_command_buff);
        fprintf(stderr ,"kernel version not found\n");
        exit(EXIT_FAILURE);
    }
    
    free(shell_command_buff);
    
    return SUCCESS_DOWNLOAD_KERNEL;
}

int unzip_kernel(const struct kernel_version *version) {
    //TODO Add NULL handler

    size_t file_name_len = strlen("linux-x.xx.xxx.tar.xz");
    size_t command_len = strlen("tar xf ");
    size_t total_buff_len = file_name_len + command_len + 1;
    char *command_buff = (char *) malloc(total_buff_len);
    memset(command_buff, 0, total_buff_len);

    if (version->minor != MINOR_VERSION_NOT_SPECIFIED)
        snprintf(command_buff, total_buff_len, "tar xf linux-%d.%d.%d.tar.xz", version->major, version->middle, version->minor);
    else
        snprintf(command_buff, total_buff_len, "tar xf linux-%d.%d.tar.xz", version->major, version->middle);

    if (system(command_buff) != 0) {
        free(command_buff);
        fprintf(stderr, "Error unziping the kernel tarball");
        exit(EXIT_FAILURE);
    }

    puts("Kernel tarball unzipped successfully");

    free(command_buff);
    command_buff = NULL;
    return 0;
}