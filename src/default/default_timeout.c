#include "../../include/network.h"

void default_timeout(server_t *serv, void *context)
{
    static size_t time = 0;
    printf("Do what you wanna do in timeout \n time = %ld\n", time);
    serv->setup_timeout(serv, 1, 0);
    time += serv->tv.tv_sec;
}
