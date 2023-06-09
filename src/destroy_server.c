#include "../include/network.h"

void stop_server(server_t *serv, int status)
{
    if (serv->is_running != 1 && serv->is_running != CTRLC) {
        dprintf(2, "[+]Server: forbidden double kill !\n");
        return;
    }
    if (status == 0 || status == CTRLC)
        dprintf(2, "[+]Server: kill or gracefully shutdown\n");
    else if (status == SELECT_FAILED && serv->is_running == CTRLC)
        return;
    else
        dprintf(2, "[+]Server: error %d occure\n", status);
    serv->is_running = status;
}

void destroy_server(void)
{
    server_t *server = server_backup(NULL);
    close(server->sock.fd);
    for (size_t i = 0; server->clients[i] != NULL; i++) {
        // client_del(server->clients[i]);
        free(server->clients[i]);
    }
    free(server->clients);
    free(server);
    dprintf(2, "[+]Server: Destroyed\n");
}
