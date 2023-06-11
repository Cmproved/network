#include "../include/network.h"

int main(int argc, char *argv[])
{
    server_t *serv = create_server(8080);
    int ret = 0;
    if (!serv)
        return (2);
    if (serv->init(serv))
        return (3);
    ret = serv->start(serv);
    if (ret != 0 && ret != CTRLC)
        printf("fatal error\n");
    destroy_server();
    return EXIT_SUCCESS;
}
