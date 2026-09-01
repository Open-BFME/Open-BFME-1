// GameSpy Chat SDK -- chatHandlers.c, 2007 release.

typedef void *CHAT;
typedef int CHATBool;

enum
{
	CHAT_MESSAGE,
	CHAT_ACTION,
	CHAT_NOTICE = 3,
	CHAT_UTM = 4
};

enum
{
	CALLBACK_PRIVATE_MESSAGE = 2,
	CALLBACK_CHANNEL_MESSAGE = 4
};

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
	void *reserved04;
	void *param;
} chatGlobalCallbacks;

typedef struct ciConnection
{
	unsigned char reserved0[0x36c];
	char nick[1];
	unsigned char reserved36d[0x800 - 0x36d];
	chatGlobalCallbacks globalCallbacks;
} ciConnection;

typedef struct chatChannelCallbacks
{
	void *channelMessage;
	void *kicked;
	void *userJoined;
	void *userParted;
	void *userChangedNick;
	void *topicChanged;
	void *channelModeChanged;
	void *userModeChanged;
	void *userListUpdated;
	void *newUserList;
	void *broadcastKeyChanged;
	void *param;
} chatChannelCallbacks;

typedef struct ciCallbackPrivateMessageParams
{
	const char *user;
	const char *message;
	int type;
} ciCallbackPrivateMessageParams;

typedef struct ciCallbackChannelMessageParams
{
	const char *channel;
	const char *user;
	const char *message;
	int type;
} ciCallbackChannelMessageParams;

unsigned int __cdecl strlen(const char *string);
int __cdecl strcmp(const char *left, const char *right);
__declspec(dllimport) int __cdecl strcasecmp(const char *left,
	const char *right);
__declspec(dllimport) char * __cdecl strchr(const char *string, int character);
chatChannelCallbacks *ciGetChannelCallbacks(CHAT chat, const char *channel);
void ciAddCallback_(CHAT chat, int type, void *callback, void *params,
	void *callbackParam, int ID, void *param2, int paramsSize);

void ciPrivmsgHandler(CHAT chat, const ciServerMessage *message)
{
	char *ctcp;
	char *target;
	char *from;
	CHATBool action = 0;
	char *msg;
	int len;
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams != 2)
		return;

	target = message->params[0];
	msg = message->params[1];
	from = message->nick;

	len = (int)strlen(msg);
	ctcp = "";
	if ((msg[0] == '\001') &&
		(((msg[1] >= 'A') && (msg[1] <= 'Z')) ||
		 ((msg[1] >= 'a') && (msg[1] <= 'z'))) &&
		(msg[len - 1] == '\001'))
	{
		char *str;
		msg[len - 1] = '\0';
		str = strchr(msg, ' ');
		if (str != 0)
		{
			ctcp = &msg[1];
			*str = '\0';
			msg = str + 1;
		}
	}

	if (strcmp(ctcp, "ACTION") == 0)
		action = 1;
	else if (ctcp[0] != '\0')
		return;

	if (strcasecmp(target, connection->nick) == 0)
	{
		if (connection->globalCallbacks.privateMessage != 0)
		{
			ciCallbackPrivateMessageParams params;
			params.user = from;
			params.message = msg;
			params.type = action ? CHAT_ACTION : CHAT_MESSAGE;
			ciAddCallback_(chat, CALLBACK_PRIVATE_MESSAGE,
				connection->globalCallbacks.privateMessage, &params,
				connection->globalCallbacks.param, 0, 0, sizeof(params));
		}
	}
	else
	{
		chatChannelCallbacks *callbacks =
			ciGetChannelCallbacks(chat, target);
		if (callbacks != 0 && callbacks->channelMessage != 0)
		{
			ciCallbackChannelMessageParams params;
			params.channel = target;
			params.user = from;
			params.message = msg;
			params.type = action ? CHAT_ACTION : CHAT_MESSAGE;
			ciAddCallback_(chat, CALLBACK_CHANNEL_MESSAGE,
				callbacks->channelMessage, &params, callbacks->param,
				0, target, sizeof(params));
		}
	}
}

void ciNoticeHandler(CHAT chat, const ciServerMessage *message)
{
	char *target;
	char *msg;
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams != 2)
		return;

	target = message->params[0];
	msg = message->params[1];

	if (strcasecmp(target, connection->nick) == 0)
	{
		if (connection->globalCallbacks.privateMessage != 0)
		{
			ciCallbackPrivateMessageParams params;
			params.user = message->nick ? message->nick : 0;
			params.message = msg;
			params.type = CHAT_NOTICE;
			ciAddCallback_(chat, CALLBACK_PRIVATE_MESSAGE,
				connection->globalCallbacks.privateMessage, &params,
				connection->globalCallbacks.param, 0, 0, sizeof(params));
		}
	}
	else
	{
		chatChannelCallbacks *callbacks =
			ciGetChannelCallbacks(chat, target);
		if (callbacks != 0 && callbacks->channelMessage != 0)
		{
			ciCallbackChannelMessageParams params;
			params.channel = target;
			params.user = message->nick ? message->nick : 0;
			params.message = msg;
			params.type = CHAT_NOTICE;
			ciAddCallback_(chat, CALLBACK_CHANNEL_MESSAGE,
				callbacks->channelMessage, &params, callbacks->param,
				0, target, sizeof(params));
		}
	}
}

void ciUTMHandler(CHAT chat, const ciServerMessage *message)
{
	char *target;
	char *msg;
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams != 2)
		return;

	target = message->params[0];
	msg = message->params[1];

	if (strcasecmp(target, connection->nick) == 0)
	{
		if (connection->globalCallbacks.privateMessage != 0)
		{
			ciCallbackPrivateMessageParams params;
			params.user = message->nick ? message->nick : 0;
			params.message = msg;
			params.type = CHAT_UTM;
			ciAddCallback_(chat, CALLBACK_PRIVATE_MESSAGE,
				connection->globalCallbacks.privateMessage, &params,
				connection->globalCallbacks.param, 0, 0, sizeof(params));
		}
	}
	else
	{
		chatChannelCallbacks *callbacks =
			ciGetChannelCallbacks(chat, target);
		if (callbacks != 0 && callbacks->channelMessage != 0)
		{
			ciCallbackChannelMessageParams params;
			params.channel = target;
			params.user = message->nick ? message->nick : 0;
			params.message = msg;
			params.type = CHAT_UTM;
			ciAddCallback_(chat, CALLBACK_CHANNEL_MESSAGE,
				callbacks->channelMessage, &params, callbacks->param,
				0, target, sizeof(params));
		}
	}
}
