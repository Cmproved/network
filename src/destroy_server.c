/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** destroy_server
*/

#include "../include/network.h"

void stop_server(server_t *serv, int status)
{
    if (serv->is_running != 1) {
        dprintf(2, "[+]Server: forbidden double kill !\n");
        return;
    }
    serv->is_running = status;
    if (status == 0)
        dprintf(2, "[+]Server: kill or gracefully shutdown\n");
    else
        dprintf(2, "[+]Server: error %d occure\n", status);
}

void destroy_server(void)
{
    server_t *server = server_backup(NULL);
    close(server->sock.fd);
    free(server);
    dprintf(2, "[+]Server: Destroyed\n");
}
