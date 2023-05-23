#include "../include/network.h"

void default_send(server_t *serv, int receiver, void *tosend, size_t size)
{
    printf("Send %s\n", (char*)tosend);
}
