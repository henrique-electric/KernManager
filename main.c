#include "core.h"

struct kernel_version parse_version(char *version) {
    size_t str_lenght = strlen(version);
    struct kernel_version kversion = {0};

    for (size_t i = 0; i < str_lenght; i++) {
        // Major number
        if (i == 0 && version[i + 1] == '.')
            kversion.major = (uint8_t) version[i] - '0';

        // Middel for model X.XX.X
        if (i == 1 && version[i + 3] == '.') {
            kversion.numbers_middle = 2;
            kversion.middle = (((int) version[i + 1] - '0') * 10) + ((int) version[i + 2] - '0');
        }
        // Middle for model X.X.X
        else if (i == 1 && version[i + 2] == '.') {
            kversion.numbers_middle = 1;
            kversion.middle = (int) version[i + 1] - '0';
        }

        // Minor version for model X.X.X
        if (i == 3 && kversion.numbers_middle == 1 && version[i + 2] == '\0'){
            kversion.minor = (int) version[i + 1] - '0';
        }
        // Model
        else if (i == 3) {

        }

    }
    return kversion;
}


int main(int argc, char *argv[])
{
    return parse_args(argc, argv);
}
