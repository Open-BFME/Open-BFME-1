// GameSpy Chat SDK -- chatHandlers.c, 2007 release.

typedef void *CHAT;
typedef void (*chatEnumUsersCallback)(CHAT chat, int success,
	const char *channel, int numUsers, const char **users,
	const int *modes, void *param);

typedef struct NAMESData
{
	int len;
	int numUsers;
	char **users;
	int *modes;
} NAMESData;

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

int ciAddNAMESFilter(CHAT chat, const char *channel,
	chatEnumUsersCallback callback, void *param)
{
	NAMESData *data = (NAMESData *)malloc(sizeof(NAMESData));
	if (data == 0)
		return 0;

	memset(data, 0, sizeof(NAMESData));
	return ciAddFilter(chat, 3, channel, 0, (void *)callback, 0, param, data);
}
