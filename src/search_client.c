#include "../include/network.h"

client_t *search_client(server_t *serv, size_t id)
{
    client_t *cli = NULL;
    size_t i = 0;
    for (; serv->clients[i]->id == id; i++);
    cli = serv->clients[i];
    return (cli);
}
