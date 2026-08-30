// _chatSendChannelMessageA
// partial score=0.94 date=2026-08-30
// cl: /DNDEBUG /MD
// Upstream: GameSpy Chat SDK chatMain.c, 2007 release.

typedef void *CHAT;

typedef struct ciConnection
{
	int connected;
	char reserved0[0x1C - 4];
	char chatSocket[1];
	char reserved1[0x36C - 0x1D];
	char nick[1];
	char reserved2[0x824 - 0x36D];
	int quiet;
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

typedef struct ciCallbackChannelMessageParams
{
	const char *channel;
	char *user;
	const char *message;
	int type;
} ciCallbackChannelMessageParams;

void ciSocketSendf(void *socket, const char *format, ...);
void ciClearAllUsers(CHAT chat);
void ciSetQuietModeEnumJoinedChannelsA(void);
void ciEnumJoinedChannels(CHAT chat, void *callback, void *param);
int ciAddLISTFilter(CHAT chat, void *callbackEach, void *callbackAll,
	void *param);
int ciAddJOINFilter(CHAT chat, const char *channel, void *callback,
	void *param, void *callbacks, const char *password);
void ciChannelEntering(CHAT chat, const char *channel);
int ciGetNextID(CHAT chat);
int ciAddCallback_(CHAT chat, int type, void *callback, void *callbackParams,
	void *param, int ID, const char *channel, unsigned int callbackParamsSize);
int ciAddCDKEYFilter(CHAT chat, void *callback, void *param);
void *ciGetChannelCallbacks(CHAT chat, const char *channel);
void bfmeCiThinkFromEsi(int ID);
void msleep(unsigned int milliseconds);
int ciCheckFiltersForID(CHAT chat, int ID);
int ciCheckCallbacksForID(CHAT chat, int ID);

static int ciCheckForID(CHAT chat, int ID)
{
	return ciCheckFiltersForID(chat, ID) || ciCheckCallbacksForID(chat, ID);
}

void chatSetQuietMode(CHAT chat, int quiet)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected)
		return;
	if (connection->quiet == quiet)
		return;

	if (quiet)
		ciSocketSendf(&connection->chatSocket, "MODE %s +q", connection->nick);
	else
		ciSocketSendf(&connection->chatSocket, "MODE %s -q", connection->nick);

	connection->quiet = quiet;
	if (!quiet)
	{
		ciClearAllUsers(chat);
		ciEnumJoinedChannels(chat, ciSetQuietModeEnumJoinedChannelsA, 0);
	}
}

void chatEnumChannelsA(CHAT chat, const char *filter, void *callbackEach,
	void *callbackAll, void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	if (!chat || !connection->connected)
		return;
	if (!filter)
		filter = "";

	ciSocketSendf(&connection->chatSocket, "LIST %s", filter);
	ID = ciAddLISTFilter(chat, callbackEach, callbackAll, param);

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

void chatEnterChannelA(CHAT chat, const char *channel, const char *password,
	void *callbacks, void *callback, void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	if (!chat || !connection->connected)
		return;
	if (!password)
		password = "";

	ciSocketSendf(&connection->chatSocket, "JOIN %s %s", channel, password);
	ID = ciAddJOINFilter(chat, channel, callback, param, callbacks, password);
	ciChannelEntering(chat, channel);

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

void chatAuthenticateCDKeyA(CHAT chat, const char *cdkey, void *callback,
	void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int success = 1;
	int ID;
	struct
	{
		int result;
		const char *message;
	} callbackParams;

	if (!chat || !connection->connected)
		return;
	if (!cdkey || !cdkey[0])
		success = 0;

	if (!success)
	{
		if (callback)
		{
			callbackParams.result = 0;
			callbackParams.message = "";
			ID = ciGetNextID(chat);
			ciAddCallback_(chat, 31, callback, &callbackParams, param, ID,
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
		return;
	}

	ciSocketSendf(&connection->chatSocket, "CDKEY %s", cdkey);
	ID = ciAddCDKEYFilter(chat, callback, param);
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

void chatSendChannelMessageA(CHAT chat, const char *channel,
	const char *message, int type)
{
	ciConnection *connection = (ciConnection *)chat;
	chatChannelCallbacks *callbacks;
	ciCallbackChannelMessageParams callbackParams;

	if (!chat || !connection->connected || !message || !message[0])
		return;

	if (type == 0)
		ciSocketSendf(&connection->chatSocket, "PRIVMSG %s :%s", channel, message);
	else if (type == 1)
		ciSocketSendf(&connection->chatSocket,
			"PRIVMSG %s :\001ACTION %s\001", channel, message);
	else if (type == 2)
		ciSocketSendf(&connection->chatSocket, "NOTICE %s :%s", channel, message);
	else if (type == 3)
		ciSocketSendf(&connection->chatSocket, "UTM %s :%s", channel, message);
	else if (type == 4)
		ciSocketSendf(&connection->chatSocket, "ATM %s :%s", channel, message);
	else
		return;

	callbacks = ciGetChannelCallbacks(chat, channel);
	if (callbacks)
	{
		callbackParams.channel = channel;
		callbackParams.user = connection->nick;
		callbackParams.message = message;
		callbackParams.type = type;
		ciAddCallback_(chat, 4, callbacks->channelMessage, &callbackParams,
			callbacks->param, 0, channel, sizeof(callbackParams));
	}
}
