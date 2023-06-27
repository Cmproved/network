#include "../../include/network.h"

int default_receive(server_t *serv, size_t id, const void *buff,\
size_t size, void *context)
{
    serv = serv;
    buff = buff;
    size = size;
    printf("Client [%ld] is in a Read state\n", id);
    return (0);
}
