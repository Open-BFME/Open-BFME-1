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

void ciSocketSendf(void *socket, const char *format, ...);
void ciClearAllUsers(CHAT chat);
void ciSetQuietModeEnumJoinedChannelsA(void);
void ciEnumJoinedChannels(CHAT chat, void *callback, void *param);
int ciAddLISTFilter(CHAT chat, void *callbackEach, void *callbackAll,
	void *param);
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
