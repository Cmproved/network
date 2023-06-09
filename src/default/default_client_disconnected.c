#include "../../include/network.h"

void default_client_disconnected(__attribute__((unused))\
    server_t *serv, size_t id)
{
    printf("[%ld] disconnected\n", id);
}
