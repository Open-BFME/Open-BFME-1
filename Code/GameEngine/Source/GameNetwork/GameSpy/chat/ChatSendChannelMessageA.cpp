// _chatSendChannelMessageA
// cl: /DNDEBUG /MD
// GameSpy Chat SDK chatMain.c body, ported as a C++ ABI slice.

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

extern "C" void ciSocketSendf(void *socket, const char *format, ...);
extern "C" int ciAddCallback_(CHAT chat, int type, void *callback, void *callbackParams,
	void *param, int ID, const char *channel, unsigned int callbackParamsSize);
extern "C" chatChannelCallbacks *ciGetChannelCallbacks(CHAT chat, const char *channel);

extern "C" void chatSendChannelMessageA(CHAT chat, const char *channel,
	const char *message, int type)
{
	ciConnection *connection = (ciConnection *)chat;
	chatChannelCallbacks *callbacks;

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
		void *callbackParam = callbacks->param;
		void *callback = callbacks->channelMessage;
		ciCallbackChannelMessageParams callbackParams;
		callbackParams.channel = channel;
		callbackParams.user = connection->nick;
		callbackParams.message = message;
		callbackParams.type = type;
		ciAddCallback_(chat, 4, callback, &callbackParams,
			callbackParam, 0, channel, sizeof(callbackParams));
	}
}
