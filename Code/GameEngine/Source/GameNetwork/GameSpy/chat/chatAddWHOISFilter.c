// GameSpy Chat SDK -- chatHandlers.c, 2007 release.

typedef void *CHAT;
typedef void (*chatGetUserInfoCallback)(CHAT chat, int success,
	const char *nick, const char *user, const char *name,
	const char *address, int numChannels, const char **channels, void *param);
typedef void (*chatGetBasicUserInfoCallback)(CHAT chat, int success,
	const char *nick, const char *user, const char *address, void *param);
typedef void (*chatGetChannelBasicUserInfoCallback)(CHAT chat, int success,
	const char *channel, const char *nick, const char *user,
	const char *address, void *param);
typedef void (*chatGetChannelModeCallback)(CHAT chat, int success,
	const char *channel, const void *mode, void *param);
typedef void (*chatEnumChannelBansCallback)(CHAT chat, int success,
	const char *channel, int numBans, const char **bans, void *param);
typedef void (*chatChangeNickCallback)(CHAT chat, int success,
	const char *oldNick, const char *newNick, void *param);
typedef void (*chatAuthenticateCDKeyCallback)(CHAT chat, int result,
	const char *message, void *param);

typedef struct WHOISData
{
	char *user;
	char *name;
	char *address;
	int numChannels;
	char **channels;
} WHOISData;

typedef struct BANData
{
	char *channel;
} BANData;

typedef struct GETBANData
{
	int numBans;
	char **bans;
} GETBANData;

typedef struct ciServerMessageFilter
{
	int type;
	unsigned int timeout;
	char *name;
	char *name2;
	void *callback;
	void *callback2;
	void *param;
	void *data;
	int ID;
	struct ciServerMessageFilter *pnext;
} ciServerMessageFilter;

typedef struct ciConnection
{
	char reserved[0x814];
	ciServerMessageFilter *filterList;
	ciServerMessageFilter *lastFilter;
	int nextID;
} ciConnection;

__declspec(dllimport) void * __cdecl malloc(unsigned int size);
__declspec(dllimport) void __cdecl free(void *memory);
void * __cdecl memset(void *dest, int value, unsigned int count);
unsigned int current_time(void);
char *goastrdup(const char *source);
int ciGetNextID(CHAT chat);

static __declspec(noinline) int ciAddFilter(CHAT chat, int type, const char *name,
	const char *name2, void *callback, void *callback2, void *param, void *data)
{
	ciServerMessageFilter *filter;
	ciConnection *connection = (ciConnection *)chat;

	filter = (ciServerMessageFilter *)malloc(sizeof(ciServerMessageFilter));
	if (filter == 0)
		return 0;

	memset(filter, 0, sizeof(ciServerMessageFilter));
	filter->type = type;
	filter->timeout = current_time() + 60000;
	filter->callback = callback;
	filter->callback2 = callback2;
	filter->param = param;
	filter->data = data;
	filter->name = name ? goastrdup(name) : 0;
	filter->name2 = name2 ? goastrdup(name2) : 0;
	filter->ID = ciGetNextID(chat);

	if (connection->filterList == 0)
		connection->filterList = filter;
	else
		connection->lastFilter->pnext = filter;
	connection->lastFilter = filter;

	return filter->ID;
}

int ciAddWHOISFilter(CHAT chat, const char *user,
	chatGetUserInfoCallback callback, void *param)
{
	int rcode;
	WHOISData *data = (WHOISData *)malloc(sizeof(WHOISData));
	if (data == 0)
		return 0;

	memset(data, 0, sizeof(WHOISData));
	rcode = ciAddFilter(chat, 4, user, 0, (void *)callback, 0, param, data);
	if (rcode == 0)
		free(data);
	return rcode;
}

int ciAddWHOFilter(CHAT chat, const char *user,
	chatGetBasicUserInfoCallback callback, void *param)
{
	return ciAddFilter(chat, 10, user, 0, (void *)callback, 0, param, 0);
}

int ciAddCWHOFilter(CHAT chat, const char *channel,
	chatGetChannelBasicUserInfoCallback callback, void *param)
{
	return ciAddFilter(chat, 11, channel, 0, (void *)callback, 0, param, 0);
}

int ciAddCMODEFilter(CHAT chat, const char *channel,
	chatGetChannelModeCallback callback, void *param)
{
	return ciAddFilter(chat, 5, channel, 0, (void *)callback, 0, param, 0);
}

int ciAddBANFilter(CHAT chat, const char *user, const char *channel)
{
	BANData *data = (BANData *)malloc(sizeof(BANData));
	if (data == 0)
		return 0;

	memset(data, 0, sizeof(BANData));
	data->channel = goastrdup(channel);
	if (data->channel == 0)
	{
		free(data);
		return 0;
	}

	return ciAddFilter(chat, 7, user, 0, 0, 0, 0, data);
}

int ciAddGETBANFilter(CHAT chat, const char *channel,
	chatEnumChannelBansCallback callback, void *param)
{
	GETBANData *data = (GETBANData *)malloc(sizeof(GETBANData));
	if (data == 0)
		return 0;

	memset(data, 0, sizeof(GETBANData));
	return ciAddFilter(chat, 8, channel, 0, (void *)callback, 0, param, data);
}

int ciAddNICKFilter(CHAT chat, const char *oldNick, const char *newNick,
	chatChangeNickCallback callback, void *param)
{
	return ciAddFilter(chat, 9, oldNick, newNick, (void *)callback, 0, param, 0);
}

int ciAddCDKEYFilter(CHAT chat, chatAuthenticateCDKeyCallback callback,
	void *param)
{
	return ciAddFilter(chat, 16, 0, 0, (void *)callback, 0, param, 0);
}
