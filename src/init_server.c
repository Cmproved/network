#include "../include/network.h"

int init_server(server_t *this)
{
    this->sock.sock_in.sin_family = AF_INET;
    this->sock.sock_in.sin_port = htons(this->port);
    this->sock.sock_in.sin_addr.s_addr = INADDR_ANY;

    if (bind(this->sock.fd, (struct sockaddr*)&this->sock.sock_in, (socklen_t)sizeof(this->sock.sock_in)) == -1) {
        close(this->sock.fd);
        perror("Erreur lors de la liaison du socket");
        return (1);
    }
    if (listen(this->sock.fd, SOMAXCONN) == -1) {
        close(this->sock.fd);
        perror("Erreur lors de l'écoute du socket");
        return (1);
    }
    return (0);
}
