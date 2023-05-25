/*
** EPITECH PROJECT, 2023
** cstd_network
** File description:
** client_del
*/

#include "../include/network.h"

static void free_client(client_t *cli)
{
    close(cli->socket.fd);
    free(cli->buffer);
    free(cli);
}

void client_del(client_t *client)
{
    server_t *serv = server_backup(NULL);
    unsigned int i = 0;
    unsigned int len = client_tab_arr(serv->clients);

    free_client(client);
    for (; i < len; i++) {
        if (serv->clients[i] == client) {
            free(serv->clients[i]);
            serv->clients[i] = NULL;
            break;
        }
    }
    for (; i < len; i++) {
        serv->clients[i] = serv->clients[i + 1];
        serv->clients[i + 1] = NULL;
    }
}
