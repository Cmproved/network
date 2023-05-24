/*
** EPITECH PROJECT, 2023
** cstd_network
** File description:
** backup_server
*/

#include "../include/network.h"

server_t *server_backup(server_t *serv)
{
    static server_t *backup = NULL;

    if (serv == NULL)
        return backup;
    backup = serv;
    return serv;
}
