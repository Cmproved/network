#include "../include/network.h"

static int reset_fds(server_t *serv)
{
    int fd = serv->sock.fd;
    clear_client(serv);
    FD_ZERO(&serv->r_fds);
    FD_ZERO(&serv->w_fds);
    FD_SET(serv->sock.fd, &serv->r_fds);
    for (int i = 0, tmp = 0; serv->clients[i]; i++) {
        tmp = serv->clients[i]->socket.fd;
        if (serv->clients[i]->socket.fd != -1)
            FD_SET(serv->clients[i]->socket.fd, &serv->r_fds);
        if (serv->clients[i]->socket.fd != -1 && serv->clients[i]->a_buf)
            FD_SET(serv->clients[i]->socket.fd, &serv->w_fds);
        if (fd < tmp)
            fd = tmp;
    }
    return (fd);
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
    int max_fd = reset_fds(serv);
    int select_ret = select(max_fd + 1, &serv->r_fds, &serv->w_fds, \
    NULL, &serv->tv);
    if (select_ret < 0) {
        perror("select");
        serv->stop(serv, SELECT_FAILED);
        return;
    }
    if (select_ret == 0) {
        serv->timeout(serv);
        return;
    }
    if (FD_ISSET(serv->sock.fd, &serv->r_fds))
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
