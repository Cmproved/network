#include "../include/network.h"

size_t client_tab_arr(void *arr)
{
    char **byte_tab = arr;
    size_t i = 0;

    if (arr == NULL)
        return (0);
    for (; byte_tab[i]; i++);
    return (i);
}
