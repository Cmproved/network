#include "../include/network.h"
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

static void init_socket(struct socket_s *sock)
{
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd == -1)
        perror("Socket creation failed");
    int opt_val = 1;
    if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &opt_val,\
        sizeof(int)) == -1) {
        perror("Setsockopt failed");
        close(sock->fd);
        sock->fd = -1;
    }
}
static const server_t server_template = {
    .is_running = 0,
    .sock = {0},
    .setup = init_server,
    .start = start_server,
    .stop = stop_server,
    .setup_send = setup_send,
    .setup_receive = setup_receive,
    .setup_receive_client = setup_receive_client,
    .setup_client_connected = setup_client_connected,
    .setup_client_disconnected = setup_client_disconnected,
    .send = default_send,
    .receive = default_receive,
    .kick = kick_it,
    .client_connected = default_client_connected,
    .client_disconnected = default_client_disconnected,
};

static void template_server(server_t *server)
{
    memcpy(server, (void *)&server_template, sizeof(server_t));
    dprintf(2, "[+]Server: initialized function.\n[+]Server: DONE\n");
}

server_t *create_server(int port)
{
    server_t* server = malloc(sizeof(server_t));

    if (!server)
        return (NULL);
    dprintf(2, "[+]Server: create server\n");
    template_server(server);
    init_socket(&server->sock);
    if (server->sock.fd == -1) {
        free(server);
        return (NULL);
    }
    dprintf(2, "[+]Server:  socket setup DONE\n");
    server->port = port;
    dprintf(2, "[+]Server: listen on 0.0.0.0 :%d\n", port);
    return server;
}
