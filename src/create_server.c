#include "../include/network.h"

static const server_t server_template = {
    .is_running = 0,
    .sock = {-2,{0}},
    .clients = NULL,
    .tv = {0, 0},
    .init = init_server,
    .start = start_server,
    .stop = stop_server,
    .setup_send = setup_send,
    .setup_receive = setup_receive,
    .setup_receive_client = setup_receive_client,
    .setup_client_connected = setup_client_connected,
    .setup_client_disconnected = setup_client_disconnected,
    .setup_timeout = setup_timeout,
    .setup_timeout_func = setup_timeout_func,
    .setup_context = setup_context,
    .send = default_send,
    .receive = default_receive,
    .kick = kick_it,
    .timeout = default_timeout,
    .client_connected = default_client_connected,
    .client_disconnected = default_client_disconnected,
};

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

static void template_server(server_t *server)
{
    dprintf(2, "[+]Server: initialized function.\n");
    memcpy(server, (const void *)&server_template, sizeof(server_t));
    dprintf(2, "[+]Server: DONE\n");
}

static void init_client(server_t *serv)
{
    serv->clients = malloc(sizeof(client_t *) * (FD_SETSIZE + 1));
    if (!serv->clients) {
        close(serv->sock.fd);
        free(serv);
        serv = NULL;
        return;
    }
    memset(serv->clients, 0, sizeof(client_t *) * (FD_SETSIZE + 1));
}

server_t *create_server(int port)
{
    if (port < 0)
        return (NULL);
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
    dprintf(2, "[+]Server: socket setup DONE\n");
    server->port = port;
    init_client(server);
    return (server);
}
