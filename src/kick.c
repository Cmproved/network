#include "../include/network.h"

void kick_it(server_t *serv, size_t id)
{
    printf("Kick %ld client\n", id);
    client_t *cli = search_client(serv, id);
    cli->to_del = 1;
    return;
}
