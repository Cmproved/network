/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** default_send
*/

#include "../include/network.h"

void default_send(server_t *serv, int receiver, void *tosend, size_t size)
{
    serv = serv;
    receiver =receiver;
    size = size;
    printf("Send %s\n", (char*)tosend);
}
