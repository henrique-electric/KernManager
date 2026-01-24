#include "core.h"
#include <regex.h>
#include <assert.h>

struct kernel_version parse_version(char *version) {
    struct kernel_version kversion = {0};

// Stuff used by regex.h functions
    regex_t compiled_regex;
    regmatch_t match[4];
    const char *pattern = "^([0-9])\\.([0-9]{1,2})\\.([0-9]{1,3})$"; // Regex pattern used on the kernel version
//

//  Compile the regex
    int compile_status = regcomp(&compiled_regex, pattern, REG_EXTENDED);
    assert(compile_status == 0);
//

    const char *str = version; // create a new pointer that points to the version string, since we'll do operations with offsets

// Search for the patterns on the version string and validate if the version was written correct
    int exec_status = regexec(&compiled_regex, str, 4, match, 0);
    if (exec_status == REG_NOMATCH) {
        fprintf(stderr, "Invalid version of the kernel\n");
        exit(EXIT_FAILURE);
    }
//

    kversion.major = (int) str[match[1].rm_so] - '0';

    int converted_number = 0;   // Variable that will be used when converting the strings to integers;

    // Run throught the matches
    for (size_t i=2; i < 4; i++) {
        size_t offset = match[i].rm_eo - match[i].rm_so; // Offset between the first digit to the last digit of the string match

        // If the offset is two, we copy the two digits into a buffer with and then convert to an integer
        if (offset == 2) {
            char buff[3] = {0};
            snprintf(buff, 3,"%.*s", offset, str + match[i].rm_so);
            converted_number = atoi(buff);

            // Since both the middle and minor number can have two digits we'll handle both cases
            if (i == 2)
                kversion.middle = converted_number;
            else
                kversion.minor = converted_number;
        }

        if (offset == 3) {
            char buff[4] = {0};
            snprintf(buff, 4, "%.*s", offset, str + match[i].rm_so);
            converted_number = atoi(buff);
            kversion.minor = converted_number;
        }
    }

    
    regfree(&compiled_regex); // Free the regex allocated stuff
    return kversion;
}


int main(int argc, char *argv[])
{
    return parse_args(argc, argv);
}
