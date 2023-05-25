/*
** EPITECH PROJECT, 2023
** cstd_network
** File description:
** client_actions
*/

#include "../include/network.h"

static int read_client(server_t *serv, int cli_fd)
{
    for (size_t i = 0; serv->clients[i]; i++)
        if (serv->clients[i] != NULL && serv->clients[i]->socket.fd == cli_fd)
            printf("Client [%d] is in a Read state\n", cli_fd);
    return (0);
}

static int write_client(server_t *serv, int cli_fd)
{
    for (size_t i = 0; serv->clients[i]; i++)
        if (serv->clients[i] != NULL && serv->clients[i]->socket.fd == cli_fd)
            printf("Client [%d] is in a Write state\n", cli_fd);
    return (0);
}

void client_actions(server_t *serv)
{
    for (int fd = 0; fd < FD_SETSIZE; fd++) {
        if (FD_ISSET(fd, &serv->read_fds))
            read_client(serv, fd);
            // printf("Read event of client %d\n", fd);
            // serv->receive(serv, fd, READ_SIZE);
        if (FD_ISSET(fd, &serv->write_fds))
            write_client(serv, fd);
            // printf("write event from client %d\n", fd);
            // serv->send(serv, fd, serv);
    }
    return;
}
