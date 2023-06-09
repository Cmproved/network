#include "../../include/network.h"

void default_client_connected(__attribute__((unused)) server_t *serv, size_t id)
{
    printf("[%ld] is connected\n", id);
}
