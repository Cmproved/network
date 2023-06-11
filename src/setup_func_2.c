#include "../include/network.h"

void setup_timeout(server_t *serv, time_t sec, suseconds_t usec)
{
    serv->tv.tv_sec = sec;
    serv->tv.tv_usec = usec;
}

void setup_timeout_func(server_t *serv, void (*func)(server_t *serv))
{
    serv->timeout = func;
}
