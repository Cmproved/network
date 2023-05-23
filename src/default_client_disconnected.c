#include "../include/network.h"

void default_client_disconnected(server_t *serv, int id)
{
    printf("Client %d disconnected", id);
}
