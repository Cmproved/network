/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** start_server
*/

#include "../include/network.h"


static void reset_fds(server_t *serv)
{
    printf("I dont reset fds now It's WIP\n");
}//TODO: Is my client a linked list or an array


static void handle(int sig)
{
    if (sig != SIGINT)
        return;
    server_t *serv = server_backup(NULL);
    serv->stop(serv, CTRLC);
    server_backup(serv);
}

int loop_server(server_t *serv)
{
    int status = 1;
    reset_fds(serv);
    if (select(FD_SETSIZE, &serv->client_fds, NULL, NULL, NULL) <= 0) { //TODO: Add TO
        perror("Select failed");
        serv->stop(serv, SELECT_FAILED);
    }
    if (FD_ISSET(serv->sock.fd, &serv->client_fds))
        if (server_accept(serv) == -1)
            serv->stop(serv, MALLOC_FAILED);
    status = client_actions(serv);
    return status;
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
