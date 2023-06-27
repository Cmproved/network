#include "../include/network.h"

client_t *search_client(server_t *serv, size_t id)
{
    int i = 0;
    int max_client = client_tab_arr(serv->clients);
    for (; i < max_client; i++)
        if (serv->clients[i]->id == id)
            return (serv->clients[i]);
    return (NULL);
}
