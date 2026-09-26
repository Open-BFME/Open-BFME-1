// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Chat SDK -- chatDisconnect, retail 0x008603F0, 116 bytes,
   reconstructed from the retail bytes.

   Tear the connection down in order: drop the filters, tell the disconnect
   callback directly if it has not already been told, send the QUIT and close
   the socket if the connection is still up, then free the channels, the
   callbacks and the socket, free the handle itself through the imported free,
   and tail into the library's own cleanup.

   The callback is called here rather than queued, with an empty reason -- the
   queue is about to be freed. The connection is the CHAT handle itself, with
   the connected flag its first word, the chat socket its +0x1C, and the
   disconnect callback and parameter at +0x7FC and +0x808. */

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef void (*ciDisconnectedCallback)(CHAT chat, const char *reason, void *param);

typedef struct ciConnection
{
	int connected;					/* +0x00 */
	CHATBool connecting;				/* +0x04 */
	CHATBool disconnected;				/* +0x08 */
	unsigned char pad0c[0x1c - 0x0c];
	unsigned char chatSocket;			/* +0x1C */
	unsigned char pad1d[0x7fc - 0x1d];
	ciDisconnectedCallback disconnectedCallback;	/* +0x7FC */
	unsigned char pad800[0x808 - 0x800];
	void *disconnectedParam;			/* +0x808 */
} ciConnection;

extern __declspec(dllimport) void __cdecl free(void *block);

void ciFilterCleanup(CHAT chat);
void ciSocketSend(void *chatSocket, const char *buffer);
void ciSocketFlush(void *chatSocket);
void ciSocketDisconnect(void *chatSocket);
void ciCleanupChannels(CHAT chat);
void ciCleanupCallbacks(CHAT chat);
void ciCleanup(void);

void chatDisconnect(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	ciFilterCleanup(chat);

	if(!connection->disconnected && connection->disconnectedCallback)
		connection->disconnectedCallback(chat, "", connection->disconnectedParam);

	if(connection->connected)
	{
		ciSocketSend(&connection->chatSocket, "QUIT :Later!");
		ciSocketFlush(&connection->chatSocket);
	}

	ciCleanupChannels(chat);
	ciCleanupCallbacks(chat);
	ciSocketDisconnect(&connection->chatSocket);

	free(chat);

	ciCleanup();
}
