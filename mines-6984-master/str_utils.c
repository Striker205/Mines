#include <ctype.h>
#include "str_utils.h"

/** Remove all spaces from a string. */
void str_remove_spaces(char *str) {
    const char *character = str;
    do {
        while (isspace(*character)) {
            ++character;
        }
    } while ((*str++ = *character++));
}