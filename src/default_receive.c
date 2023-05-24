/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** default_receive
*/

#include "../include/network.h"

void *default_receive(server_t *serv, int id, size_t size)
{
    serv = serv;
    char *buf = malloc(size + 1 * sizeof(char));
    read(id , buf, size);
    return (buf);
}
