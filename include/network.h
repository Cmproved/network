#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef _NETWORK_H_
    #define _NETWORK_H_
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <limits.h>
    #include <stddef.h>
typedef struct server_s server_t;
struct socket_s {
    int fd;
    struct sockaddr_in sock_in;
};

struct client_s {
    struct socket_s socket;
    void *buffer;
    void *(*received)(struct server_s *serv, int id, size_t size);
};

typedef struct server_s {
    int port;
    struct socket_s sock;
    struct client_s *client[10];//BUG: linked list maybe;
    //TODO: ID or UUID;
    int is_running;

    int (*const setup)(struct server_s *);
    int (*const start)(struct server_s *);
    void (*const stop)(struct server_s *, int stat);
    void (*const kick)(struct server_s *serv, int id);

    void (*const setup_send)(struct server_s *, void (*)(struct server_s *, int id, void *tosend, size_t size));
    void (*const setup_receive)(struct server_s *, void *(*)(struct server_s *, int id, size_t size));
    void (*const setup_receive_client)(struct server_s *, void *(*)(struct server_s *, int id, size_t size), int id);
    void (*const setup_client_connected)(struct server_s *, void (*)(struct server_s *, int id));
    void (*const setup_client_disconnected)(struct server_s *, void (*)(struct server_s *, int id));

    void (*send)(struct server_s *serv, int id, void *tosend, size_t size);
    void *(*receive)(struct server_s *serv, int id, size_t size);
    void (*client_connected)(struct server_s *serv, int id);
    void (*client_disconnected)(struct server_s *serv, int id);
} server_t;

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
void setup_send(server_t *serv, void (*)(server_t *serv, int id, void *tosend, size_t size));

/*
 setup the receiver function
*/
void setup_receive(server_t *serv, void *(*)(server_t *serv, int id, size_t size));

/*
 setup the receive function for the client
*/
void setup_receive_client(server_t *, void *(*)(server_t *serv, int id, size_t size), int id);

/*
 setup what to do when client connected
*/
void setup_client_connected(server_t *serv, void (*)(server_t *serv, int id));

/*
 setup what to do when client connected
*/
void setup_client_disconnected(server_t *serv, void (*)(server_t *serv, int id));

/*
 start the server logic as itself and loop into select
*/
int start_server(server_t *serv);

/*
 default send a buffer of data to a client
*/
void default_send(server_t *serv, int receiver, void *tosend, size_t size);

/*
 default receive data buffer from a client
*/
void *default_receive(server_t *serv, int id, size_t size);

/*
 kick a user from the server
*/
void kick_it(server_t *serv, int id);

/*
 default client connected function
*/
void default_client_connected(server_t *serv, int id);

/*
 default client disconncted
*/
void default_client_disconnected(server_t *serv, int id);

/*
 stop the server clear connection and lead the server to able to destroy state
*/
void stop_server(server_t *serv, int status);

/*
 destroy the server and try to free every elements left inside
*/
void destroy_server(server_t *server);
#endif // !_NETWORK_H_
