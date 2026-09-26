// cl: /O2 /DNDEBUG /MD
// Retail's surviving identity evidence is the REGISTERNICK command and the
// four-field ciConnection layout used by this body.  No owning SDK symbol is
// asserted here, so the address-derived name is intentional.

extern "C" int __cdecl ciSocketSendf(void *socket, const char *format, ...);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *, const char *, unsigned int);

struct Rva00860380Connection;
typedef void (__cdecl *Rva00860380Callback)(void *, const char *, int, void *);

struct Rva00860380Connection
{
    int connected;
    const char *registeredNick;
    unsigned char padding08[0x0c];
    Rva00860380Callback callback;
    void *callbackData;
    unsigned char socket;
    unsigned char padding1d[0x4f3];
    char nickCopy[0x40];
};

extern "C" void __cdecl Rva00860380(
    void *chat,
    int sessionKey,
    const char *nick,
    const char *secondNick)
{
    Rva00860380Connection *connection =
        reinterpret_cast<Rva00860380Connection *>(chat);
    if (connection->connected != 0)
        return;

    if (nick == 0)
    {
        Rva00860380Callback callback = connection->callback;
        connection->registeredNick = nick;
        if (callback == 0)
            return;
        callback(chat, nick, 1, connection->callbackData);
        return;
    }

    if (secondNick == 0)
        secondNick = "";
    ciSocketSendf(
        &connection->socket,
        "REGISTERNICK %d %s %s",
        sessionKey,
        nick,
        secondNick);
    strncpy(connection->nickCopy, nick, 0x40);
    connection->nickCopy[0x3f] = 0;
}
