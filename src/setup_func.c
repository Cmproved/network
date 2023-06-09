#include "../include/network.h"

void setup_send(server_t *serv, void (*func)(server_t *serv, size_t id,\
void *data))
{
    serv->send = func;
}

void setup_receive(\
server_t *serv, int (*func)(server_t *serv, size_t id, const void *buff,\
size_t size))
{
    serv->receive = func;
}

void setup_receive_client(\
server_t *serv, int (*func)(server_t *serv, size_t id,\
const void *buff, size_t size), size_t id)
{
    for (int i = 0; serv->clients[i]; i++)
        if (serv->clients[i]->id == id)
            serv->clients[i]->received = func;
}

void setup_client_connected(\
server_t *serv, void (*func)(server_t *serv, size_t id))
{
    serv->client_connected = func;
}

void setup_client_disconnected(\
server_t *serv, void (*func)(server_t *serv, size_t id))
{
    serv->client_disconnected = func;
}
