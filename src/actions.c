#include <core.h>

const char *kernel_url = "https://cdn.kernel.org/pub/linux/kernel/";
int download_kernel(const struct kernel_version *kversion) {

    size_t kernel_url_len = strlen(kernel_url) + 1;
    size_t version_path_len = strlen("vx/") + 1; // x will be replaced with the major number
    size_t linux_prefix_len = strlen("linux-x") + 1;
    size_t linux_suffix_len = strlen(".tar.xz") + 1;

    size_t middle_version_len = 0;
    size_t minor_version_len = 0;
    size_t full_url_len = 0;
    char *url_buff = (char*) malloc(version_path_len);
    char *full_url = NULL;
    memset(url_buff, version_path_len, 0);

    snprintf(url_buff, version_path_len, "v%d/", kversion->major);

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
    
    full_url_len = kernel_url_len + version_path_len + middle_version_len + minor_version_len + 1;
    full_url = (char *) malloc(full_url_len);
    memset(full_url, full_url_len, 0);
    snprintf(full_url, kernel_url_len, kernel_url);
    printf("%s\n", full_url);

    free(url_buff);
    free(full_url);
    url_buff = NULL;
    full_url = NULL;

    return 0;

}