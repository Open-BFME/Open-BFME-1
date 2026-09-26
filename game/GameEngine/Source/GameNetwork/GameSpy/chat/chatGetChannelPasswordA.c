// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy

typedef void *CHAT;

typedef struct ciConnection
{
	int connected;
} ciConnection;

int ciInChannel(CHAT chat, const char *channel);
const char *ciGetChannelPassword(CHAT chat, const char *channel);
int ciGetNextID(CHAT chat);
int ciAddCallback_(CHAT chat, int type, void *callback, void *callbackParams,
	void *param, int ID, const char *channel, unsigned int callbackParamsSize);
void bfmeCiThinkFromEsi(int ID);
void msleep(unsigned int milliseconds);
int ciCheckFiltersForID(CHAT chat, int ID);
int ciCheckCallbacksForID(CHAT chat, int ID);

static int ciCheckForID(CHAT chat, int ID)
{
	return ciCheckFiltersForID(chat, ID) || ciCheckCallbacksForID(chat, ID);
}

void chatGetChannelPasswordA(CHAT chat, const char *channel, void *callback,
	void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	const char *password;
	int ID;
	struct
	{
		int success;
		const char *channel;
		int enabled;
		const char *password;
	} callbackParams;

	if (!chat || !connection->connected)
		return;

	if (!ciInChannel(chat, channel))
		return;

	password = ciGetChannelPassword(chat, channel);
	ID = ciGetNextID(chat);
	callbackParams.success = 1;
	callbackParams.enabled = 1;
	callbackParams.channel = channel;
	callbackParams.password = password;
	ciAddCallback_(chat, 18, callback, &callbackParams, param, ID,
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
