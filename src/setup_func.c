/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** setup_func
*/

#include "../include/network.h"

void setup_send(server_t *serv, void (*func)(server_t *, int, void *, size_t))
{
    serv->send = func;
}

void setup_receive(server_t *serv, void *(*func)(server_t *, int, size_t))
{
    serv->receive = func;
}

void setup_receive_client(server_t *serv, void* (*func)(server_t *serv, \
            int id, size_t size), int id)
{
    serv->client[id]->received = func;
}

void setup_client_connected(server_t *serv, void (*func)(server_t *, int))
{
    serv->client_connected = func;
}

void setup_client_disconnected(server_t *serv, void (*func)(server_t *, int))
{
    serv->client_disconnected = func;
}
