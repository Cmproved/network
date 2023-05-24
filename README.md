# cstd_network
provide a simple plug and play server in C

## Basic usage

With a correct usage, the library has no valgrind errors, nor memory leaks.

```c
#include "network.h"

int main(int ac, char **av)
{
    //TODO: exemple of how to use the lib
    return (0);
}
```

Output :
```bash
user@localhost~$ ./a.out
>> #the output of the code above
```

## The Object

### Values

| value | type | description |
|-------|------|-------------|
| `port` | `int` | the port where the server listent |
| `is_running` | `int` | the return status of the start function |
| `port` | `int` | the port where the server listent |

### Methods
Here are the methods of the object :

|name | return type | parameters | description |
|-----|-------------|------------|-------------|
| `setup` | `int` | `server_t *serv` | setup the server to listent on port given at constructor |
| `start` | `int` | `server_t *serv` | start the server and all the logic behind |
| `stop` | `void` | `server_t *serv, int status` | stop the server with given status, `0` on success, other on error (refered to network error header) accessible at the return of start methods |
| `kick` | `void` | `server_t *serv, int kick` | kick the `id` client from the server |
| `setup_send` | `void` | `server_t *serv, void(*)(server_t *serv, int id, void *data, size_t size)` | set the callback function for `send` (by default it's `default_send`)|
| `setup_receive` | `void` | `server_t *serv, void *(*)(server_t *serv, int id, size_t size)` | set the callback function for `receive` (by default it's `default_receive`)|
| `setup_receive_client` | `void` | `server_t *serv, void *(*)(server_t *serv, int id, size_t size), int client_id` | set the callback function for `receive` for a define client (by default it's `default_receive`) |
| `setup_client_connected` | `void` | `server_t *serv, void(*)(server_t *serv, int id)` | set the callback function for `client_connected` (by default it's `default_client_connected`)|
| `setup_client_disconnected` | `void` | `server_t *serv, void(*)(server_t *serv, int id)` | set the callback function for `client_disconnected` (by default it's `default_client_disconnected`)|
| `send` | `void` | `server_t *serv, int id, void *data, size_t size` | send `size of `data` to the `id` client`|
| `receive` | `void *` | `server_t *serv, int id, size_t size` | receive `data` from the `id` client`|
| `client_connected` | `void` | `server_t *serv, int id` | action to do when a client `id` is connected |
| `client_disconnected` | `void` | `server_t *serv, int id` | action to do when a client `id` is disconnected |

### External fonctions

| name | return type | parameters | description |
|------|-------------|------------|-------------|
| `create_server` | `server_t *` | `int port` | `create a server_t object that is ready to listent on the port given` |
| `destroy_server` | `void` | `void` | `set the server_t in a state to be destroy and clear so clear all memory allocated`| 
| `backup_server` | `server_t * \|\| NULL` | `server_t *` | `if a `server_t *` is given as parameter, the function store in a static way the pointer, if the parameter is `NULL`, the function return the `server_t *` stored`|

## Contributing
Contributions are greatly apreciated. Do not hesitate to pull request, or open issues !
Thanks !
