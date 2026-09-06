// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK control handlers, ported to BFME's 2004 layout.
   Identity: retail command table RVA00EC8930, PING/ERROR/401/708 entries.
   Algorithm reference: GameSpy chatHandlers.c; retail is the layout oracle. */
typedef void *CHAT;
typedef struct ciServerMessage {
    char beforeParam[0x1c];
    char *param;
    char **params;
    int numParams;
} ciServerMessage;
typedef void (*chatConnectCallback)(CHAT, int, int, void *);
typedef struct ciConnection {
    int connected;
    int connecting;
    char reserved08[0x14 - 8];
    chatConnectCallback connectCallback;
    void *connectParam;
    int chatSocket;
} ciConnection;
void ciSocketSendf(void *, const char *, ...);
void ciHandleDisconnect(CHAT, const char *);
void ciPingHandler(CHAT chat, const ciServerMessage *message) {
    ciConnection *connection = (ciConnection *)chat;
    ciSocketSendf(&connection->chatSocket, "PONG %s", message->param);
}
void ciErrorHandler(CHAT chat, const ciServerMessage *message) {
    if (message->numParams != 1) return;
    ciHandleDisconnect(chat, message->params[0]);
}
void ciErrNoSuchNickHandler(CHAT chat, const ciServerMessage *message) {
    (void)chat;
    (void)message;
}
void ciErrLoginFailedHandler(CHAT chat, const ciServerMessage *message) {
    ciConnection *connection = (ciConnection *)chat;
    if (connection->connecting) {
        connection->connecting = 0;
        if (connection->connectCallback)
            connection->connectCallback(chat, 0, 2, connection->connectParam);
    }
    (void)message;
}
