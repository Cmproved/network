#include "../include/network.h"

static void read_client(server_t *serv, client_t *client)
{
    void *buff = alloca(READ_SIZE + 1);
    memset(buff, 0, READ_SIZE + 1);
    int readed = 0;
    readed = read(client->socket.fd, buff, READ_SIZE);
    if (readed <= 0) {
        client->to_del = 1;
        return;
    }
    if (client->received)
        client->received(serv, client->id, buff, readed + 1, serv->context);
    else
        serv->receive(serv, client->id, buff, readed + 1, serv->context);
    return;
}

static void write_client(server_t *serv, client_t *client)
{
    int writed = write(client->socket.fd, client->a_buf, client->a_size);
    if (writed < 0)
        client->to_del = 1;
    if ((size_t) writed == client->a_size) {
        free(client->a_buf);
        client->a_buf = NULL;
        client->a_size = 0;
    } else {
        client->a_size -= writed;
        void *new_data = realloc(client->a_buf, client->a_size);
        if (!new_data) {
            serv->stop(serv, MALLOC_FAILED);
            return;
        }
        client->a_buf = new_data;
    }
}

static void actions(server_t *serv, int i)
{
    if (FD_ISSET(serv->clients[i]->socket.fd, &serv->r_fds))
        read_client(serv, serv->clients[i]);
    if (FD_ISSET(serv->clients[i]->socket.fd, &serv->w_fds))
        write_client(serv, serv->clients[i]);
    return;
}

void client_actions(server_t *serv)
{
    for (int i = 0; serv->clients[i]; i++)
        actions(serv, i);
    return;
}
