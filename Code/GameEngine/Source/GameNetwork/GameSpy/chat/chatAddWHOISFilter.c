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

typedef struct WHOISData
{
	char *user;
	char *name;
	char *address;
	int numChannels;
	char **channels;
} WHOISData;

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

static int ciAddFilter(CHAT chat, int type, const char *name,
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
