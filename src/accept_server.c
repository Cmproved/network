#include "../include/network.h"

static int accept_client(client_t *client, int server_fd)
{
    socklen_t sockaddr_client_size = sizeof(struct sockaddr_in);
    client->socket.fd = accept(server_fd, (struct sockaddr *)\
    &client->socket.sock_in, &sockaddr_client_size);
    if (client->socket.fd == -1) {
        perror("Accept failed");
        free(client);
        return (1);
    }
    return (0);
}

static client_t *create_client(int server_fd, size_t id)
{
    client_t *client = malloc(sizeof(struct client_s));
    printf("New client %p\n", client);
    if (!client)
        return (NULL);
    if (accept_client(client, server_fd)) {
        free(client);
        return (NULL);
    }
    client->a_buf = NULL;
    client->id = id;
    client->to_del = 0;
    return (client);
}

static size_t get_client_id(server_t *serv)
{
    size_t id = 1;
    if (!serv->clients[0])
        return (1);
    for (int i = 0; serv->clients[i]; i++) {
        if (serv->clients[i]->id == id) {
            id++;
            i = -1;
        }
    }
    return (id);
}

int server_accept(server_t *serv)
{
    size_t id = get_client_id(serv);
    client_t *client = create_client(serv->sock.fd, id);
    int nb_clients = client_tab_arr(serv->clients);
    if (!client)
        return (MALLOC_FAILED);
    if (nb_clients < FD_SETSIZE) {
        serv->clients[nb_clients] = client;
    } else {
        close(client->socket.fd);
        free(client);
        return (ACCEPT_FAILED);
    }
    serv->client_connected(serv, serv->clients[nb_clients]->id);
    return (0);
}
