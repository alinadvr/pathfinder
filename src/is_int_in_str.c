#include "pathfinder.h"

int is_int_in_str(char *str)
{
    while (*str != '\0')
    {
        if (*str >= 48 && *str <= 57) return 1;

        str++;
    }

    return 0;
}
