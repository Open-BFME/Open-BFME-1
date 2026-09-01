// cl: /DNDEBUG /MD
/* GameSpy Chat SDK -- chatMain.c */

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef void (*chatEnumUsersCallback)(
	CHAT chat, CHATBool success, const char *channel, int numUsers,
	const char **users, int *modes, void *param);

typedef struct ciConnection
{
	int connected;
	char reserved0[0x1C - 4];
	char chatSocket[1];
} ciConnection;

void ciSocketSendf(void *socket, const char *format, ...);
int ciInChannel(CHAT chat, const char *channel);
void ciEnumUsersCallback(void);
void ciChannelListUsers(
	CHAT chat, const char *channel, void *callback, void *param);
int ciAddNAMESFilter(
	CHAT chat, const char *channel, void *callback, void *param);
void bfmeCiThinkFromEsi(int ID);
void msleep(unsigned int milliseconds);
int ciCheckFiltersForID(CHAT chat, int ID);
int ciCheckCallbacksForID(CHAT chat, int ID);

static int ciCheckForID(CHAT chat, int ID)
{
	return ciCheckFiltersForID(chat, ID) || ciCheckCallbacksForID(chat, ID);
}

void chatEnumUsersA(
	CHAT chat, const char *channel, chatEnumUsersCallback callback,
	void *param, CHATBool blocking)
{
	register const char *channelHandle;
	register CHAT chatHandle = chat;
	ciConnection *connection = (ciConnection *)chatHandle;
	struct
	{
		chatEnumUsersCallback callback;
		void *param;
	} data;
	int ID;

	if (!chatHandle || !connection->connected)
		return;
	channelHandle = channel;
	if (!channelHandle)
		channelHandle = "";

	if (channelHandle[0] && ciInChannel(chatHandle, channelHandle)) {
		data.callback = callback;
		data.param = param;
		ciChannelListUsers(chatHandle, channelHandle, ciEnumUsersCallback, &data);
		return;
	}

	ciSocketSendf(&connection->chatSocket, "NAMES %s", channelHandle);
	if (!channelHandle[0])
		channelHandle = 0;
	ID = ciAddNAMESFilter(chatHandle, channelHandle, callback, param);

	if (blocking) {
		do {
			bfmeCiThinkFromEsi(ID);
			msleep(10);
		} while (ciCheckForID(chatHandle, ID));
	}
}
