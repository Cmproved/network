#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

#ifndef _NETWORK_H_
    #define _NETWORK_H_
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <limits.h>
    #include <stddef.h>
    #include <signal.h>
    #include <uuid/uuid.h>
    #include "network_define.h"

typedef struct server_s server_t;

struct socket_s {
    int fd;
    struct sockaddr_in sock_in;
};

typedef struct client_s {
    struct socket_s socket;
    size_t id;
    int to_del;
    void *a_buf;
    size_t a_size;
    int (*received)(struct server_s *serv, size_t id, const \
            void *buff, size_t size, void *context);
} client_t;

typedef struct server_s {
    int port;
    struct socket_s sock;
    fd_set r_fds;
    fd_set w_fds;
    struct client_s **clients;
    int is_running;
    struct timeval tv;
    void *context;

    int (*const init)(struct server_s *serv);
    int (*const start)(struct server_s *serv);
    void (*const stop)(struct server_s *serv, int stat);
    void (*const kick)(struct server_s *serv, size_t id);

    void (*const setup_send)(struct server_s *serv, \
            void (*)(struct server_s *serv, size_t id, void *data, \
            size_t size));
    void (*const setup_receive)(struct server_s *, \
            int (*)(struct server_s *serv, size_t id, \
                const void *buff, size_t size, void *context));
    void (*const setup_receive_client)(struct server_s *, \
            int (*)(struct server_s *serv, size_t id, \
                const void *buff, size_t size, void *context), size_t id);
    void (*const setup_client_connected)(struct server_s *, \
            void (*)(struct server_s *serv, size_t id));
    void (*const setup_client_disconnected)(struct server_s *, \
            void (*)(struct server_s *, size_t id));
    void (*const setup_timeout)(server_t *serv, time_t sec, suseconds_t usec);
    void (*const setup_timeout_func)(server_t *serv, \
            void (*)(struct server_s *serv, void *context));
    void (*const setup_context)(server_t *serv, void *context);

    void (*send)(struct server_s *serv, size_t id, void *data, size_t size);
    int (*receive)(struct server_s *serv, size_t id,\
            const void *buff, size_t size, void *context);
    void (*client_connected)(struct server_s *serv, size_t id);
    void (*client_disconnected)(struct server_s *serv, size_t id);
    void (*timeout)(struct server_s *serv, void *context);
} server_t;

/*
   Backup the pointer of the server for destroy
   */
server_t *server_backup(server_t *serv);

/*
   create a server object that will listen on port given as parametter
   */
server_t *create_server(int port);

/*
   initialize the server bind the port and start listening
   */
int init_server(server_t *serv);

/*
   setup the sender function
   */
void setup_send(server_t *serv, \
    void (*)(server_t *serv, size_t id, void *data, size_t size));

/*
   setup the receiver function
   */
void setup_receive(server_t *serv, \
    int (*)(server_t *serv, size_t id, const void *buff, size_t size, \
    void *context));

/*
   setup the receive function for the client
   */
void setup_receive_client(server_t *, \
    int (*)(server_t *serv, size_t id, const void *buff,\
    size_t size, void *context), size_t id);

/*
   setup what to do when client connected
   */
void setup_client_connected(server_t *serv, \
    void (*)(server_t *serv, size_t id));

/*
   setup what to do when client connected
   */
void setup_client_disconnected(server_t *serv, \
    void (*)(server_t *serv, size_t id));

/*
    setup timeout of select and so manage time
    */
void setup_timeout(server_t *serv, time_t sec, suseconds_t  usec);

/*
    setup function call when timeout happend
    */
void setup_timeout_func(server_t *serv, void (*func)(server_t *serv,\
    void *context));

/*
    setup context as context
    */
void setup_context(server_t *serv, void *context);

/*
   start the server logic as itself and loop into select
   */
int start_server(server_t *serv);

/*
   accept for the client
   */
int server_accept(server_t *serv);

/*
   Loop for all client in order to know what to do
   */
void client_actions(server_t *serv);

/*
   Search ID client so we can get the FD
   */
client_t *search_client(server_t *serv, size_t id);

/*
   client array size
   */
size_t client_tab_arr(void *arr);

/*
   Delete client from array
   */
void client_del(client_t *cli);

/*
   clear all deleted client from client array
   */
void clear_client(server_t *serv);

/*
   default send a buffer of data to a client
   */
void default_send(server_t *serv, size_t id_rcv, void *data, size_t size);

/*
   default receive data buffer from a client
   */
int default_receive(server_t *serv, size_t id_snd, const void *buff,\
    size_t size, void *context);

/*
   kick a user from the server
   */
void kick_it(server_t *serv, size_t id);

/*
   default client connected function
   */
void default_client_connected(server_t *serv, size_t id);

/*
   default client disconncted
   */
void default_client_disconnected(server_t *serv, size_t id);

/*
   default timeout function
   */
void default_timeout(server_t *serv, void *context);

/*
   stop the server clear connection and lead the server to able to destroy state
   */
void stop_server(server_t *serv, int status);

/*
   destroy the server and try to free every elements left inside
   */
void destroy_server(void);
#endif // !_NETWORK_H_
