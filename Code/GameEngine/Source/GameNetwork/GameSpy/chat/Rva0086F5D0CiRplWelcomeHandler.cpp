// cl: /DNDEBUG /MD
// GameSpy Chat SDK ciRplWelcomeHandler, retail RVA 0x0086F5D0.

typedef void *CHAT;
typedef int CHATBool;

enum
{
    CHATFalse,
    CHATTrue
};

typedef void (__cdecl *ciConnectCallback)(CHAT chat, CHATBool success,
    int failureReason, void *param);

struct ciServerMessage
{
    unsigned char pad00[0x20];
    char **params;
    int numParams;
};

struct ciConnection
{
    int connected;
    CHATBool connecting;
    CHATBool disconnected;
    void *nickErrorCallback;
    unsigned char pad10[4];
    ciConnectCallback connectCallback;
    void *connectParam;
    unsigned char chatSocket;
    unsigned char pad1d[0x36c - 0x1d];
    char nick[64];
};

extern "C" __declspec(dllimport) int __cdecl strcmp(const char *, const char *);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *, const char *,
    unsigned int);

extern "C" void ciRplWelcomeHandler(CHAT chat,
    const ciServerMessage *message)
{
    char *nick;
    ciConnection *connection = (ciConnection *)chat;

    if (message->numParams != 2)
        return;

    nick = message->params[0];

    if (strcmp(connection->nick, nick) != 0)
    {
        strncpy(connection->nick, nick, 64);
        connection->nick[63] = '\0';
    }

    connection->connecting = CHATFalse;
    connection->connected = CHATTrue;

    if (connection->connectCallback != 0)
        connection->connectCallback(chat, CHATTrue, 0,
            connection->connectParam);
}
