// GameSpy Chat SDK -- chatHandlers.c, 2007 release.
// Retail command dispatch table proves UTM -> 0086D0F0 and ATM -> 0086D1C0.
// The former NOTICE/UTM labels were shifted; callback types remain 3/4.

typedef void *CHAT;
typedef int CHATBool;

enum
{
	CHAT_MESSAGE,
	CHAT_ACTION,
	CHAT_NOTICE = 2,
	CHAT_UTM = 3,
	CHAT_ATM = 4
};

enum
{
	CHAT_LEFT,
	CHAT_QUIT,
	CHAT_KILLED = 3
};

enum
{
	CALLBACK_PRIVATE_MESSAGE = 2,
	CALLBACK_CHANNEL_MESSAGE = 4,
	CALLBACK_USER_PARTED = 7,
	CALLBACK_USER_LIST_UPDATED = 12
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

typedef struct ciCallbackUserPartedParams
{
	const char *channel;
	const char *user;
	int why;
	const char *reason;
	const char *kicker;
} ciCallbackUserPartedParams;

typedef struct ciCallbackUserListUpdatedParams
{
	const char *channel;
} ciCallbackUserListUpdatedParams;

unsigned int __cdecl strlen(const char *string);
int __cdecl strcmp(const char *left, const char *right);
__declspec(dllimport) int __cdecl strcasecmp(const char *left,
	const char *right);
__declspec(dllimport) char * __cdecl strchr(const char *string, int character);
chatChannelCallbacks *ciGetChannelCallbacks(CHAT chat, const char *channel);
void ciUserLeftChannel(CHAT chat, const char *user, const char *channel);
CHATBool ciWasJoinCallbackCalled(CHAT chat, const char *channel);
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

void ciATMHandler(CHAT chat, const ciServerMessage *message)
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
			params.type = CHAT_ATM;
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
			params.type = CHAT_ATM;
			ciAddCallback_(chat, CALLBACK_CHANNEL_MESSAGE,
				callbacks->channelMessage, &params, callbacks->param,
				0, target, sizeof(params));
		}
	}
}

void ciPartHandler(CHAT chat, const ciServerMessage *message)
{
	char *nick;
	char *channel;
	char *reason;
	chatChannelCallbacks *callbacks;
	ciConnection *connection = (ciConnection *)chat;

	nick = message->nick;
	channel = message->params[0];
	if (message->numParams > 1)
		reason = message->params[1];
	else
		reason = "";

	if (strcmp(nick, connection->nick) != 0)
	{
		ciUserLeftChannel(chat, nick, channel);
		if (ciWasJoinCallbackCalled(chat, channel))
		{
			callbacks = ciGetChannelCallbacks(chat, channel);
			if (callbacks != 0)
			{
				if (callbacks->userParted != 0)
				{
					ciCallbackUserPartedParams params;
					params.channel = channel;
					params.user = nick;
					params.why = 0;
					params.reason = reason;
					params.kicker = 0;
					ciAddCallback_(chat, CALLBACK_USER_PARTED,
						callbacks->userParted, &params, callbacks->param,
						0, channel, sizeof(params));
				}

				if (callbacks->userListUpdated != 0)
				{
					ciCallbackUserListUpdatedParams params;
					params.channel = channel;
					ciAddCallback_(chat, CALLBACK_USER_LIST_UPDATED,
						callbacks->userListUpdated, &params, callbacks->param,
						0, channel, sizeof(params));
				}
			}
		}
	}
}

void ciQuitEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *reason)
{
	chatChannelCallbacks *callbacks;

	ciUserLeftChannel(chat, user, channel);
	if (ciWasJoinCallbackCalled(chat, channel))
	{
		callbacks = ciGetChannelCallbacks(chat, channel);
		if (callbacks != 0)
		{
			if (callbacks->userParted != 0)
			{
				ciCallbackUserPartedParams params;
				params.channel = channel;
				params.user = user;
				params.why = CHAT_QUIT;
				params.reason = (char *)reason;
				params.kicker = 0;
				ciAddCallback_(chat, CALLBACK_USER_PARTED,
					callbacks->userParted, &params, callbacks->param,
					0, (void *)channel, sizeof(params));
			}

			if (callbacks->userListUpdated != 0)
			{
				ciCallbackUserListUpdatedParams params;
				params.channel = channel;
				ciAddCallback_(chat, CALLBACK_USER_LIST_UPDATED,
					callbacks->userListUpdated, &params, callbacks->param,
					0, (void *)channel, sizeof(params));
			}
		}
	}
}

void ciKillEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *param)
{
	chatChannelCallbacks *callbacks;
	char *reason = (char *)param;

	ciUserLeftChannel(chat, user, channel);
	if (ciWasJoinCallbackCalled(chat, channel))
	{
		callbacks = ciGetChannelCallbacks(chat, channel);
		if (callbacks != 0)
		{
			if (callbacks->userParted != 0)
			{
				ciCallbackUserPartedParams params;
				params.channel = channel;
				params.user = user;
				params.why = CHAT_KILLED;
				params.reason = reason;
				params.kicker = 0;
				ciAddCallback_(chat, CALLBACK_USER_PARTED,
					callbacks->userParted, &params, callbacks->param,
					0, (void *)channel, sizeof(params));
			}

			if (callbacks->userListUpdated != 0)
			{
				ciCallbackUserListUpdatedParams params;
				params.channel = channel;
				ciAddCallback_(chat, CALLBACK_USER_LIST_UPDATED,
					callbacks->userListUpdated, &params, callbacks->param,
					0, (void *)channel, sizeof(params));
			}
		}
	}
}
