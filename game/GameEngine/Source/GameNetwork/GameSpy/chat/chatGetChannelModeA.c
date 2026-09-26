// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
// GameSpy Chat SDK 2007 chatGetChannelModeA, retail 0x00860D10.

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef struct CHATChannelMode
{
	CHATBool InviteOnly;
	CHATBool Private;
	CHATBool Secret;
	CHATBool Moderated;
	CHATBool NoExternalMessages;
	CHATBool OnlyOpsChangeTopic;
	int Limit;
	char *Ops;
} CHATChannelMode;

typedef struct ciConnection
{
	int connected;
	char reserved0[0x1c - 4];
	char chatSocket[1];
} ciConnection;

void ciSocketSendf(void *socket, const char *format, ...);
int ciInChannel(CHAT chat, const char *channel);
int ciGetChannelMode(CHAT chat, const char *channel, CHATChannelMode *mode);
int ciGetNextID(CHAT chat);
int ciAddCallback_(CHAT chat, int type, void *callback, void *callbackParams,
	void *param, int ID, const char *channel, unsigned int callbackParamsSize);
int ciAddCMODEFilter(CHAT chat, const char *channel, void *callback, void *param);
void bfmeCiThinkFromEsi(int ID);
void msleep(unsigned int milliseconds);
int ciCheckFiltersForID(CHAT chat, int ID);
int ciCheckCallbacksForID(CHAT chat, int ID);

static int ciCheckForID(CHAT chat, int ID)
{
	return ciCheckFiltersForID(chat, ID) || ciCheckCallbacksForID(chat, ID);
}

void chatGetChannelModeA(CHAT chat, const char *channel, void *callback,
	void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	CHATChannelMode mode;
	int ID;
	struct
	{
		int success;
		const char *channel;
		CHATChannelMode *mode;
	} callbackParams;

	if (!chat || !connection->connected)
		return;

	if (ciInChannel(chat, channel) && ciGetChannelMode(chat, channel, &mode))
	{
		ID = ciGetNextID(chat);
		callbackParams.success = 1;
		callbackParams.channel = channel;
		callbackParams.mode = &mode;
		ciAddCallback_(chat, 17, callback, &callbackParams, param, ID,
			0, sizeof(callbackParams));

		if (blocking)
		{
			do
			{
				bfmeCiThinkFromEsi(ID);
				msleep(10);
			}
			while (ciCheckForID(chat, ID));
		}
	}
	else
	{
		ciSocketSendf(&connection->chatSocket, "MODE %s", channel);
		ID = ciAddCMODEFilter(chat, channel, callback, param);
		if (blocking)
		{
			do
			{
				bfmeCiThinkFromEsi(ID);
				msleep(10);
			}
			while (ciCheckForID(chat, ID));
		}
	}
}
