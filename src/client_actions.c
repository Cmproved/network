/*
** EPITECH PROJECT, 2023
** cstd_network
** File description:
** client_actions
*/

#include "../include/network.h"

int client_actions(server_t *serv)
{
    int status = 0;
    for (int fd = 0; fd < FD_SETSIZE; fd++)
        if (FD_ISSET(fd, &serv->client_fds))
            printf("Client [%d] is in a Read or Write state\n", fd);
    return (status);
}
