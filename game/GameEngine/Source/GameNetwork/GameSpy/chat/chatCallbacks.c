// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Chat SDK -- small helpers from chatCallbacks.c, reconstructed
   from the retail bytes rather than from the SDK text: the declarations here
   are local for the same reason chatMain.c's are, and the connection layout is
   read off the offsets these bodies touch.

     0x0086C310  ciGetNextID           38 bytes
     0x0086C340  ciCheckFiltersForID   39 bytes
     0x008702C0  ciInitCallbacks       40 bytes
     0x008715E0  ciGetCallbackIndexByID 73 bytes
     0x00871630  ciCheckCallbacksForID 30 bytes
     0x008717B0  ciInitChannels       100 bytes
     0x00871820  ciCleanupChannels     45 bytes

   The connection is the CHAT handle itself -- every one of them indexes
   straight off the incoming pointer with no adjustment -- and carries the
   channel table at +0x80C, the channel array at +0x810, the filter list at
   +0x814, the next ID at +0x81C and the callback array at +0x820. A filter carries its ID at +0x20 and its next link at +0x24. */

#include <limits.h>

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef struct ciFilter
{
	unsigned char pad0[0x20];
	int ID;						/* +0x20 */
	struct ciFilter *next;				/* +0x24 */
} ciFilter;

typedef struct ciConnection
{
	unsigned char pad0[0x80c];
	void *channelTable;				/* +0x80C */
	void *channelList;				/* +0x810 */
	ciFilter *filterList;				/* +0x814 */
	unsigned char pad818[0x81c - 0x818];
	int nextID;					/* +0x81C */
	void *callbackList;				/* +0x820 */
} ciConnection;

/* the callback array element; only its size reaches this file */
typedef struct ciCallback
{
	unsigned char pad0[0x10];
	int ID;
	unsigned char pad14[0x18 - 0x14];
} ciCallback;

/* likewise the channel element */
typedef struct ciChannel
{
	unsigned char pad0[0x1e4];
} ciChannel;

void *ArrayNew(int elemsize, int initialcount, void (*elemfreefn)(void *elem));
void ArrayFree(void *array);
int ArrayLength(void *array);
void *ArrayNth(void *array, int index);
void *TableNew2(int elemsize, int nbuckets, int nchains, void *hashfn, void *comparefn, void *elemfreefn);
void TableFree(void *table);

/* the channel table's three hooks; only their addresses reach this file */
void ciChannelHash(void);
void ciChannelCompare(void);
void ciChannelFree(void);
void ciCallbackFree(void *elem);

int ciGetNextID(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	ID = connection->nextID;
	if(ID == INT_MAX)
		connection->nextID = 1;
	else
		connection->nextID = ID + 1;

	return ID;
}

CHATBool ciCheckFiltersForID(CHAT chat, int ID)
{
	ciConnection *connection = (ciConnection *)chat;
	ciFilter *filter;

	for(filter = connection->filterList ; filter ; filter = filter->next)
		if(filter->ID == ID)
			return CHATTrue;

	return CHATFalse;
}

static int ciGetCallbackIndexByID(CHAT chat, int ID)
{
	ciConnection *connection = (ciConnection *)chat;
	ciCallback *data;
	int i;
	int len;

	len = ArrayLength(connection->callbackList);
	for(i = 0 ; i < len ; i++)
	{
		data = (ciCallback *)ArrayNth(connection->callbackList, i);
		if(data->ID == ID)
			return i;
	}

	return -1;
}

CHATBool ciCheckCallbacksForID(CHAT chat, int ID)
{
	if(ciGetCallbackIndexByID(chat, ID) == -1)
		return CHATFalse;

	return CHATTrue;
}

CHATBool ciInitCallbacks(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	connection->callbackList = ArrayNew(sizeof(ciCallback), 128, ciCallbackFree);

	return (CHATBool)(connection->callbackList != 0);
}

void ciCleanupChannels(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	if(connection->channelTable)
		TableFree(connection->channelTable);

	if(connection->channelList)
		ArrayFree(connection->channelList);
}

CHATBool ciInitChannels(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	connection->channelTable = TableNew2(sizeof(ciChannel), 7, 2, ciChannelHash,
		ciChannelCompare, ciChannelFree);
	if(!connection->channelTable)
		return CHATFalse;

	connection->channelList = ArrayNew(sizeof(ciChannel), 0, 0);
	if(!connection->channelList)
	{
		TableFree(connection->channelTable);
		return CHATFalse;
	}

	return CHATTrue;
}
