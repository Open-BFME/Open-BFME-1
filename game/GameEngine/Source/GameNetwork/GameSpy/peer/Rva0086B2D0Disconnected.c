// cl: /DNDEBUG /MD

typedef struct Rva0086B2D0Connection
{
    char pad[0x1F04];
    int disconnected;
} Rva0086B2D0Connection;

void piAddDisconnectedCallback(void *peer, const char *reason);

void Rva0086B2D0Disconnected(void *unused, const char *reason,
    Rva0086B2D0Connection *connection)
{
    connection->disconnected = 1;
    piAddDisconnectedCallback(connection, reason);
}
