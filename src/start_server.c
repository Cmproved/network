/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** start_server
*/

#include "../include/network.h"

static void reset_fds(server_t *serv)
{
    FD_ZERO(&serv->read_fds);
    FD_ZERO(&serv->write_fds);
    FD_SET(serv->sock.fd, &serv->read_fds);
    FD_SET(serv->sock.fd, &serv->write_fds);
    for (size_t i = 0; serv->clients[i]; i++)
        if (serv->clients[i]->socket.fd) {
            FD_SET(serv->clients[i]->socket.fd, &serv->read_fds);
            FD_SET(serv->clients[i]->socket.fd, &serv->write_fds);
        }
}

static void handle(int sig)
{
    if (sig != SIGINT)
        return;
    server_t *serv = server_backup(NULL);
    serv->stop(serv, CTRLC);
}

static void loop_server(server_t *serv)
{
    reset_fds(serv);
    if (select(FD_SETSIZE + 1, &serv->read_fds, &serv->write_fds, NULL, NULL) <= 0) {
        perror("select");
        serv->stop(serv, SELECT_FAILED);
        return;
    }
    if (FD_ISSET(serv->sock.fd, &serv->read_fds))
        if (server_accept(serv) == -1) {
            serv->stop(serv, MALLOC_FAILED);
            return;
        }
    client_actions(serv);
}

int start_server(server_t *serv)
{
    server_backup(serv);
    serv->is_running = 1;
    struct sigaction sig = {0};

    sig.sa_handler = &handle;
    sigaction(SIGINT, &sig, NULL);
    while (serv->is_running == 1)
        loop_server(serv);
    return (serv->is_running);
}
