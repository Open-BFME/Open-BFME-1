// GameSpy Chat SDK -- chatHandlers.c, 2007 release.

typedef void *CHAT;
typedef int (*chatEnterChannelCallback)(CHAT chat, int success,
	int failureReason, void *param);
typedef void (*chatEnumChannelsCallbackEach)(CHAT chat, int success,
	int index, const char *channel, const char *topic, int numUsers,
	void *param);
typedef void (*chatEnumChannelsCallbackAll)(CHAT chat, int success,
	int numChannels, const char **channels, const char **topics,
	const int *numUsers, void *param);

typedef struct LISTData
{
	int gotStart;
	int numChannels;
	char **channels;
	int *numUsers;
	char **topics;
} LISTData;

typedef struct chatChannelCallbacks
{
	void *callbacks[12];
} chatChannelCallbacks;

typedef struct JOINData
{
	chatChannelCallbacks callbacks;
	int joined;
	char password[32];
} JOINData;

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
__declspec(dllimport) char * __cdecl strncpy(char *dest, const char *source,
	unsigned int count);
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

int ciAddLISTFilter(CHAT chat, chatEnumChannelsCallbackEach callbackEach,
	chatEnumChannelsCallbackAll callbackAll, void *param)
{
	LISTData *data = (LISTData *)malloc(sizeof(LISTData));
	if (data == 0)
		return 0;

	memset(data, 0, sizeof(LISTData));
	return ciAddFilter(chat, 0, 0, 0, (void *)callbackEach,
		(void *)callbackAll, param, data);
}

int ciAddJOINFilter(CHAT chat, const char *channel,
	chatEnterChannelCallback callback, void *param,
	chatChannelCallbacks *callbacks, const char *password)
{
	int rcode;
	JOINData *data;

	data = (JOINData *)malloc(sizeof(JOINData));
	if (data == 0)
		return 0;

	memset(data, 0, sizeof(JOINData));
	data->callbacks = *callbacks;
	strncpy(data->password, password, sizeof(data->password));
	data->password[sizeof(data->password) - 1] = '\0';

	rcode = ciAddFilter(chat, 1, channel, 0, (void *)callback, 0, param, data);
	if (rcode == 0)
		free(data);

	return rcode;
}
