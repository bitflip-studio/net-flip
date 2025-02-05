#include "./server.h"
#include "./allocator.h"
#include <string.h>

Server_t* server_alloc() {
    return (Server_t*) allocator_allocate(1, sizeof(Server_t));
}

bool server_init(Server_t* server, ServerSettings_t* settings) {
    if(&(server->settings) == memcpy(&(server->settings), settings, sizeof(ServerSettings_t))) {
        return false;
    }
    return true;
}




