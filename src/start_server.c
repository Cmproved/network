/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** start_server
*/

#include "../include/network.h"

static void reset_fds(server_t *serv)
{
    FD_ZERO(&serv->client_fds);
    FD_SET(serv->sock.fd, &serv->client_fds);
    printf("I reset only server fd\n");
}//TODO: Is my client a linked list or an array


static void handle(int sig)
{
    if (sig != SIGINT)
        return;
    server_t *serv = server_backup(NULL);
    serv->stop(serv, CTRLC);
    server_backup(serv);
}

static void loop_server(server_t *serv)
{
    reset_fds(serv);
    if (select(FD_SETSIZE, &serv->client_fds, NULL, NULL, NULL) <= 0 && serv->is_running == 1) {
        //INFO: Add TimeOut ?
        perror("select");
        serv->stop(serv, SELECT_FAILED);
        return;
    }
    if (FD_ISSET(serv->sock.fd, &serv->client_fds))
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

    int status = 1;
    sig.sa_handler = &handle;
    sigaction(SIGINT, &sig, NULL);
    while (serv->is_running == 1)
        loop_server(serv);
    return (serv->is_running);
}
