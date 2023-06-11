#include "../../include/network.h"

void default_timeout(__attribute__ ((unused)) server_t *serv)
{
    static size_t time = 0;
    printf("Do what you wanna do in timeout \n time = %ld\n", time);
    serv->setup_timeout(serv, 1, 0);
    time += serv->tv.tv_sec;
}
