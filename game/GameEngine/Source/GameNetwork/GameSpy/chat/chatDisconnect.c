// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Chat SDK -- ciHandleDisconnect, retail 0x008601A0, 80 bytes,
   reconstructed from the retail bytes.

   The connection is the CHAT handle itself. Its first three words are the
   connected, connecting and disconnected flags -- chatMain.c already has the
   first two -- and the disconnect callback and its parameter sit at +0x7FC and
   +0x808.

   The three flags are written before the callback is tested, not inside the
   test, and the reason is handed over in a one-word parameter block whose size
   the call carries as its last argument. */

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef struct ciConnection
{
	int connected;					/* +0x00 */
	CHATBool connecting;				/* +0x04 */
	CHATBool disconnected;				/* +0x08 */
	unsigned char pad0c[0x7fc - 0x0c];
	void *disconnectedCallback;			/* +0x7FC */
	unsigned char pad800[0x808 - 0x800];
	void *disconnectedParam;			/* +0x808 */
} ciConnection;

typedef struct ciDisconnectedParams
{
	const char *reason;
} ciDisconnectedParams;

void ciAddCallback_(CHAT chat, int type, void *callback, void *params,
		void *callbackParam, int ID, void *param2, int paramsSize);
#define ciAddCallback(chat, type, callback, params, callbackParam, ID, param2) \
	ciAddCallback_(chat, type, callback, params, callbackParam, ID, param2, \
		sizeof(*(params)))

enum { CALLBACK_DISCONNECTED = 1 };

void ciHandleDisconnect(CHAT chat, const char *reason)
{
	ciConnection *connection = (ciConnection *)chat;
	ciDisconnectedParams params;

	if(connection->disconnected)
		return;

	connection->connected = 0;
	connection->connecting = CHATFalse;
	connection->disconnected = CHATTrue;

	if(connection->disconnectedCallback)
	{
		params.reason = reason;
		ciAddCallback(chat, CALLBACK_DISCONNECTED, connection->disconnectedCallback,
			&params, connection->disconnectedParam, 0, 0);
	}
}
