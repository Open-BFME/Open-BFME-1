// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Chat SDK -- ciInviteHandler, retail RVA 0x0086DAE0.
   The command table identifies this as the INVITE handler.  Only the
   connection prefix through the global callback block is modeled here; the
   callback order and the +0x804 invited slot are established by the sibling
   chat handlers and the retail callback block. */

#include <assert.h>
#include <stddef.h>

typedef void *CHAT;

typedef struct ciServerMessage
{
	unsigned char reserved0[8];
	char *nick;
	unsigned char reserved0c[0x20 - 0x0c];
	char **params;
	int numParams;
} ciServerMessage;

typedef struct chatGlobalCallbacks
{
	void *privateMessage;
	void *invited;
	void *param;
} chatGlobalCallbacks;

typedef struct ciInviteConnection
{
	unsigned char beforeGlobalCallbacks[0x800];
	chatGlobalCallbacks globalCallbacks;
} ciInviteConnection;

typedef struct ciCallbackInvitedParams
{
	char *channel;
	char *user;
} ciCallbackInvitedParams;

enum { CALLBACK_INVITED = 3 };

void ciAddCallback_(CHAT chat, int type, void *callback, void *params,
	void *callbackParam, int ID, void *param2, int paramsSize);

#define ciAddCallback(chat, type, callback, params, callbackParam, ID, param2) \
	ciAddCallback_(chat, type, callback, params, callbackParam, ID, param2, \
		sizeof(*(params)))

void ciInviteHandler(CHAT chat, const ciServerMessage *message)
{
	char *nick;
	char *channel;
	ciInviteConnection *connection = (ciInviteConnection *)chat;

	assert(message->numParams == 2);
	if (message->numParams != 2)
		return;

	nick = message->nick;
	channel = message->params[1];

	if (connection->globalCallbacks.invited != NULL)
	{
		ciCallbackInvitedParams params;
		params.channel = channel;
		params.user = nick;
		ciAddCallback(chat, CALLBACK_INVITED,
			connection->globalCallbacks.invited, &params,
			connection->globalCallbacks.param, 0, NULL);
	}
}
