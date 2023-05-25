/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** init_server
*/

#include "../include/network.h"

int init_server(server_t *this)
{
    this->sock.sock_in.sin_family = AF_INET;
    this->sock.sock_in.sin_port = htons(this->port);
    this->sock.sock_in.sin_addr.s_addr = INADDR_ANY;

    if (bind(this->sock.fd, (struct sockaddr*)&this->sock.sock_in, \
                (socklen_t)sizeof(this->sock.sock_in)) == -1) {
        close(this->sock.fd);
        perror("bind");
        return (1);
    }
    if (listen(this->sock.fd, SOMAXCONN) == -1) {
        close(this->sock.fd);
        perror("listen");
        return (1);
    }
    dprintf(2, "[+]Server: listen on 0.0.0.0 :%d\n", this->port);
    return (0);
}
