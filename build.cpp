#include <core.h>
#include <string>
#include <filesystem>
#include <stdlib.h>

extern "C" void build(const struct kernel_version *kver) {
    std::string user_home = getenv("HOME");
    std::string linux_path;

    if (kver->minor == MINOR_VERSION_NOT_SPECIFIED)
        linux_path = user_home + "/" + kver->str_version + ".0";
    else
        linux_path = user_home + "/" + kver->
    
}