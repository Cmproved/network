#include "../include/network.h"

void stop_server(server_t *serv, int status)
{
    serv->is_running = status;
}

void destroy_server(server_t *server)
{
    close(server->sock.fd);
    free(server);
}
