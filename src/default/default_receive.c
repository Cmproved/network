#include "../../include/network.h"

int default_receive(server_t *serv, size_t id, const void *buff, size_t size)
{
    int readval = 0;
    client_t *client = search_client(serv, id);
    printf("Client [%ld] is in a Read state\n", id);
    char *buf = malloc(READ_SIZE + 1 * sizeof(char));
    if (!buf)
        return (-MALLOC_FAILED);
    readval = read(client->socket.fd, buf, READ_SIZE);
    if (readval == -1)
        return (-1);
    return (readval);
}
