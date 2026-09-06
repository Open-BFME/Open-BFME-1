// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// GameSpy Chat SDK -- channel entry bookkeeping.

#include <stdlib.h>
#include <string.h>

#define MAX_CHANNEL 257
#define MAX_TOPIC 128
#define MAX_NAME 128
#define MAX_CACHED_USER 24
#define MAX_CACHED_ADDRESS 64

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

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

typedef struct CHATChannelMode
{
	CHATBool InviteOnly;
	CHATBool Private;
	CHATBool Secret;
	CHATBool Moderated;
	CHATBool NoExternalMessages;
	CHATBool OnlyOpsChangeTopic;
	int Limit;
	char *Ops;
} CHATChannelMode;

typedef struct ciChatChannel
{
	char name[MAX_CHANNEL];
	chatChannelCallbacks callbacks;
	void *users;
	CHATChannelMode mode;
	CHATBool gotMode;
	char *password;
	CHATBool joinCallbackCalled;
	char topic[MAX_TOPIC];
} ciChatChannel;

typedef struct ciChatUser
{
	char name[MAX_NAME];
	char user[MAX_CACHED_USER];
	char address[MAX_CACHED_ADDRESS];
	CHATBool gotUserAndAddress;
	int mode;
} ciChatUser;

typedef struct ciConnection
{
	unsigned char pad0[0x80c];
	void *channelTable;
	void *enteringChannelList;
} ciConnection;

void *TableNew2(int elemSize, int nBuckets, int nChains,
	void *hashFn, void *compareFn, void *freeFn);
int ArraySearch(void *array, const void *elem, void *comparator,
	int fromIndex, int isSorted);
void ArrayRemoveAt(void *array, int index);
void TableEnter(void *table, const void *newElem);

int ciUserHash(const void *elem, int numBuckets);
int ciEnteringChannelComparator(const void *param1, const void *param2);
void ciUserCompare(void);
void ciUserFree(void);

void ciChannelEntered(CHAT chat, const char *channel,
	chatChannelCallbacks *callbacks)
{
	ciChatChannel chatChannel;
	char *password;
	int index;
	ciConnection *connection = (ciConnection *)chat;

	password = (char *)malloc(2);
	if(password == NULL)
		return;
	password[0] = 0;

	memset(&chatChannel, 0, sizeof(ciChatChannel));
	chatChannel.callbacks = *callbacks;
	strncpy(chatChannel.name, channel, MAX_CHANNEL);
	chatChannel.name[MAX_CHANNEL - 1] = '\0';
	chatChannel.users = TableNew2(sizeof(ciChatUser), 61, 2, ciUserHash,
		ciUserCompare, ciUserFree);
	if(chatChannel.users == NULL)
		return;
	chatChannel.gotMode = CHATFalse;
	chatChannel.password = password;
	chatChannel.joinCallbackCalled = CHATFalse;
	chatChannel.topic[0] = '\0';

	index = ArraySearch(connection->enteringChannelList, &chatChannel,
		ciEnteringChannelComparator, 0, 0);
	if(index != -1)
		ArrayRemoveAt(connection->enteringChannelList, index);

	TableEnter(connection->channelTable, &chatChannel);
}
