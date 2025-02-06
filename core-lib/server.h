#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t port;
} ServerSettings_t;

typedef struct {
    ServerSettings_t settings;
} Server_t;


Server_t* server_alloc();
bool server_init(Server_t* server, ServerSettings_t* settings);
bool server_init_fromArgs(Server_t* server, uint16_t port)



