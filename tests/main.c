#include "../include/network.h"

int main(int argc, char *argv[])
{
    server_t *serv = create_server(8080);
    if (!serv)
        return (2);
    if (serv->setup(serv))
        return (3);
    if (serv->start(serv) != 0)
        printf("fatal error\n");
    destroy_server();
    return EXIT_SUCCESS;
}
