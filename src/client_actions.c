#include "../include/network.h"

static void read_client(server_t *serv, client_t *client)
{
    //TODO:
    //Read -> buff;
    //serv->receive(serv, id_cli_sender, buff, size_buf)
    //si erreur fd -> -1;
    void *buff = alloca(READ_SIZE);
    memset(buff, 0, READ_SIZE);
    int readed = 0;
    readed = read(client->socket.fd, buff, READ_SIZE);
    if (readed <= 0)
        client->to_del = 1;
    if (strlen(buff) != 0)
        printf("%s", (char *)buff);
    return;
}

static void write_client(server_t *serv, client_t *client)
{
    //TODO:
    //write the a_buff, on client_id of size_t buf
    //move data if needed
    int writed = write(client->socket.fd, client->a_buf, client->a_size);
    if (writed < 0)
        client->to_del = 1;
    return;
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
