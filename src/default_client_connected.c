#include "../include/network.h"

void default_client_connected(server_t *serv, int id)
{
    printf("Client %d connected", id);
}
