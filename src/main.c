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
    if (compile_status != 0) {
        fprintf(stderr, "Error to compile the regex pattern");
        exit(EXIT_FAILURE);
    }
//

    const char *str = version; // create a new pointer that points to the version string, since we'll do operations with offsets

// Search for the patterns on the version string and validate if the version was written correct
    int exec_status = regexec(&compiled_regex, str, 4, match, 0);
    if (exec_status == REG_NOMATCH) {
        fprintf(stderr, "Invalid version of the kernel\n");
        regfree(&compiled_regex);
        exit(EXIT_FAILURE);
    }
//


    kversion.major = (int) str[match[1].rm_so] - '0'; // Major Version has only 1 digit, so we can just go the the first index

    int converted_number = 0;   
    char buffer[9] = {0}; // Buffer to hold the number characters
    snprintf(buffer, 3, "%.*s", match[2].rm_eo - match[2].rm_so, str + match[2].rm_so);
    converted_number = atoi(buffer);
    kversion.middle = converted_number;
    memset(buffer, sizeof(char), 0); // Clear buffer for the next number


    snprintf(buffer, 4, "%.*s", match[3].rm_eo - match[3].rm_so, str + match[3].rm_so);
    converted_number = atoi(buffer);
    kversion.minor = converted_number;

    regfree(&compiled_regex); // Free the regex allocated stuff
    return kversion;
}


int main(int argc, char *argv[])
{
    return parse_args(argc, argv);
}
