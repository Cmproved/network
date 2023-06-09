#include "../../include/network.h"

void default_send(server_t *serv, size_t id, void *data)
{
    serv = serv;
    printf("Send data %s >> to %ld\n",(char *)data, id);
}
