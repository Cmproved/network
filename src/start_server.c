#include "../include/network.h"

int start_server(server_t *serv)
{
    serv->is_running = 1;
    while (serv->is_running == 1) {
        printf("This server is going to be shutdown\n");
        serv->stop(serv, 15);
    }
    printf("This server is now down\n");
    return (serv->is_running);
}
