#include "../include/network.h"

void *default_receive(server_t *serv, int id, size_t size)
{
    char *buf = malloc(1024 + 1 * sizeof(char));
    read(id , buf, 1024);
    return (buf);
}
