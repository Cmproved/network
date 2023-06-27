#include "../../include/network.h"

void default_send(server_t *serv, size_t id, void *data, size_t size)
{
    serv = serv;
    printf("Send data %s >> to %ld\n",(char *)data, id);
}
