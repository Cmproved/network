/*
** EPITECH PROJECT, 2023
** cstd_network
** File description:
** accept_server
*/

#include "../include/network.h"

char* uuid(char out[UUID_STR_LEN]){
  uuid_t b;
  uuid_generate(b);
  uuid_unparse_lower(b, out);
  return out;
}

static int accept_client(client_t *client, int server_fd)
{
    socklen_t sockaddr_client_size = sizeof(struct sockaddr_in);
    client->socket.fd = accept(server_fd, (struct sockaddr *)\
    &client->socket.sock_in,&sockaddr_client_size);
    if (client->socket.fd == -1) {
        perror("Accept failed");
        free(client);
        return (1);
    }
    uuid(client->id);
    return (0);
}

static client_t *create_client(int server_fd)
{
    client_t *client = malloc(sizeof(struct client_s));
    if (!client)
        return (NULL);
    if (accept_client(client, server_fd))
        return (NULL);
    client->buffer = NULL;
    return client;
}

int server_accept(server_t *serv)
{
    client_t *client = create_client(serv->sock.fd);
    int nb_clients = client_tab_arr(serv->clients);

    if (!client)
        return (-1);
    if (nb_clients < FD_SETSIZE) {
        printf("nb client %d\n", nb_clients);
        serv->clients[nb_clients] = client;
        serv->client_connected(serv, nb_clients);
    } else {
        close(client->socket.fd);
        free(client);
    }
    return (0);
}
