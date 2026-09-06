// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- chatChannel.c */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHANNEL 257
#define MAX_TOPIC 128

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
	char * Ops;
} CHATChannelMode;

typedef struct ciChatChannel
{
	char name[MAX_CHANNEL];
	unsigned char pad_101[3];
	chatChannelCallbacks callbacks;
	void * users;
	CHATChannelMode mode;
	CHATBool gotMode;
	char * password;
	CHATBool joinCallbackCalled;
	char topic[MAX_TOPIC];
} ciChatChannel;

typedef struct ciConnection
{
	int connected;					/* +0x00 */
	unsigned char pad4[0x1c - 0x04];
	unsigned char chatSocket;			/* +0x1C */
	unsigned char pad1d[0x80c - 0x1d];
	void *channelTable;				/* +0x80C */
	void *enteringChannelList;			/* +0x810 */
} ciConnection;

void ciSocketSendf(void *chatSocket, const char *format, ...);
void ArrayAppend(void *array, const void *elem);
int ArraySearch(void *array, const void *elem, void *comparator, int fromIndex, int isSorted);
void ArrayRemoveAt(void *array, int index);
void *TableLookup(void *table, const void *elem);
void TableRemove(void *table, const void *elem);
void TableFree(void *table);
int TableCount(void *table);
int ciEnteringChannelComparator(const void *param1, const void *param2);
void ciChannelLeft(CHAT chat, const char *channel);

void chatLeaveChannel(CHAT chat, const char *channel, const char *reason)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!chat)
		return;

	if(!connection->connected)
		return;

	if(!reason)
		reason = "";

	ciSocketSendf(&connection->chatSocket, "PART %s :%s", channel, reason);

	ciChannelLeft(chat, channel);
}

void ciChannelEntering(CHAT chat, const char *channel)
{
	ciChatChannel chatChannel;
	ciConnection *connection = (ciConnection *)chat;

	memset(&chatChannel, 0, sizeof(ciChatChannel));
	strncpy(chatChannel.name, channel, MAX_CHANNEL);
	chatChannel.name[MAX_CHANNEL - 1] = '\0';
	ArrayAppend(connection->enteringChannelList, &chatChannel);
}

void ciChannelLeft(CHAT chat, const char *channel)
{
	ciChatChannel chatChannel;
	int index;
	ciConnection *connection = (ciConnection *)chat;

	strncpy(chatChannel.name, channel, MAX_CHANNEL);
	chatChannel.name[MAX_CHANNEL - 1] = '\0';

	index = ArraySearch(connection->enteringChannelList, &chatChannel, ciEnteringChannelComparator, 0, 0);
	if(index != -1)
	{
		ArrayRemoveAt(connection->enteringChannelList, index);
	}
	else
	{
		TableRemove(connection->channelTable, &chatChannel);
	}
}

static ciChatChannel * ciGetChannel(ciConnection * connection, const char * channel)
{
	ciChatChannel * chatChannel;
	ciChatChannel channelTemp;

	strncpy(channelTemp.name, channel, MAX_CHANNEL);
	channelTemp.name[MAX_CHANNEL - 1] = '\0';
	chatChannel = (ciChatChannel *)TableLookup(connection->channelTable, &channelTemp);

	return chatChannel;
}

chatChannelCallbacks * ciGetChannelCallbacks(CHAT chat, const char * channel)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return NULL;

	return &chatChannel->callbacks;
}

CHATBool ciInChannel(CHAT chat, const char * channel)
{
	ciConnection * connection = (ciConnection *)chat;

	if(ciGetChannel(connection, channel) == NULL)
		return CHATFalse;

	return CHATTrue;
}

CHATBool ciGetChannelMode(CHAT chat, const char * channel, CHATChannelMode * mode)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return CHATFalse;

	if(!chatChannel->gotMode)
		return CHATFalse;

	memcpy(mode, &chatChannel->mode, sizeof(CHATChannelMode));

	return CHATTrue;
}

void ciSetChannelMode(CHAT chat, const char * channel, CHATChannelMode * mode)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return;

	chatChannel->gotMode = CHATTrue;
	memcpy(&chatChannel->mode, mode, sizeof(CHATChannelMode));
}

void ciSetChannelPassword(CHAT chat, const char * channel, const char * password)
{
	int len;
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return;

	free(chatChannel->password);

	if(password == NULL)
		password = "";
	len = (int)(strlen(password) + 1);
	chatChannel->password = (char *)malloc((unsigned int)len);
	if(chatChannel->password == NULL)
		return;
	memcpy(chatChannel->password, password, (unsigned int)len);
}

const char * ciGetChannelPassword(CHAT chat, const char * channel)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return NULL;

	return chatChannel->password;
}

void ciJoinCallbackCalled(CHAT chat, const char * channel)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return;

	chatChannel->joinCallbackCalled = CHATTrue;
}

CHATBool ciWasJoinCallbackCalled(CHAT chat, const char * channel)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return CHATFalse;

	return chatChannel->joinCallbackCalled;
}

void ciSetChannelTopic(CHAT chat, const char * channel, const char * topic)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return;

	strncpy(chatChannel->topic, topic, MAX_TOPIC);
	chatChannel->topic[MAX_TOPIC - 1] = '\0';
}

const char * ciGetChannelTopic(CHAT chat, const char * channel)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return NULL;

	return chatChannel->topic;
}

int ciGetChannelNumUsers(CHAT chat, const char * channel)
{
	ciChatChannel * chatChannel;
	ciConnection * connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == NULL)
		return -1;

	return TableCount(chatChannel->users);
}

/* Three channel commands that go straight out on the socket.  Each one is
   identified by the format literal retail hands ciSocketSendf, and each is
   referenced from exactly one body.

   chatSetChannelPasswordA reads oddly and is right: retail passes ONE
   argument to a two-%s format.  The second comes from the incoming argument
   block, which the tail call reuses in place -- both branches share a single
   call site with only the format pointer differing.  That is VC7.1 merging
   TWO calls, not one call with a chosen format: spelled as a ternary the
   format lands in a register and the body is two bytes short. */

void chatSetChannelTopicA(CHAT chat, const char *channel, const char *topic)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!chat)
		return;

	if(!connection->connected)
		return;

	if(!topic)
		topic = "";

	ciSocketSendf(&connection->chatSocket, "TOPIC %s :%s", channel, topic);
}

void chatSetChannelPasswordA(CHAT chat, const char *channel, CHATBool enable,
		const char *password)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!chat)
		return;

	if(!connection->connected)
		return;

	if(enable)
		ciSocketSendf(&connection->chatSocket, "MODE %s +k %s", channel, password);
	else
		ciSocketSendf(&connection->chatSocket, "MODE %s -k %s", channel, password);
}

void chatSetChannelLimitA(CHAT chat, const char *channel, int limit)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!chat)
		return;

	if(!connection->connected)
		return;

	if(limit)
		ciSocketSendf(&connection->chatSocket, "MODE %s +l %d", channel, limit);
	else
		ciSocketSendf(&connection->chatSocket, "MODE %s -l", channel);
}

/* The two hash hooks and the channel table's free hook.  Which is which is
   not read off the shapes -- the two hashes are byte-for-byte identical --
   but off their install sites: ciInitChannels at 0x008717B0 passes 0x008716D0
   as the CHANNEL table's hash alongside 0x00871720 as its free, and the
   per-channel user table built at 0x00871930 passes 0x00871750 as its hash.
   Retail keeps both copies rather than folding them, so both are written.

   Each hashes the string at the START of the element -- ciChatChannel's name
   and the user's nick are both the first member -- and sums tolower of every
   byte, so the table is case-insensitive.  The sum is signed and the modulus
   is idiv, not a mask.

   The loop cost two builds and both lessons are in its spelling.  It tests
   the PROMOTED value, not the char -- written `while(*name)` the test is on
   al and the sign extension moves to the call.  And the increment comes
   BEFORE the accumulate: written after it, VC7.1 reloads through [esi+1] and
   increments afterwards, which is the same work one byte longer.

   ciChannelFree frees the password before the user table, and only frees the
   table when there is one; the password goes to free unguarded. */

int ciChannelHash(const void *elem, int numBuckets)
{
	const char *name = (const char *)elem;
	int hash = 0;
	int c;

	while((c = *name) != 0)
	{
		name++;
		hash += tolower(c);
	}

	return (hash % numBuckets);
}

void ciChannelFree(void *elem)
{
	ciChatChannel *channel = (ciChatChannel *)elem;

	free(channel->password);

	if(channel->users)
		TableFree(channel->users);
}

int ciUserHash(const void *elem, int numBuckets)
{
	const char *nick = (const char *)elem;
	int hash = 0;
	int c;

	while((c = *nick) != 0)
	{
		nick++;
		hash += tolower(c);
	}

	return (hash % numBuckets);
}

typedef struct ciChatUser
{
	char name[128];
	char user[24];
	char address[64];
	CHATBool gotUserAndAddress;
	int mode;
} ciChatUser;

void ciUserLeftChannel(CHAT chat, const char *user, const char *channel)
{
	ciChatChannel chatChannel;
	ciChatUser chatUser;
	ciChatChannel *channelData;
	ciConnection *connection = (ciConnection *)chat;

	strncpy(chatChannel.name, channel, MAX_CHANNEL);
	chatChannel.name[MAX_CHANNEL - 1] = '\0';
	channelData = (ciChatChannel *)TableLookup(connection->channelTable,
		&chatChannel);
	if(channelData == NULL)
		return;

	strncpy(chatUser.name, user, 128);
	chatUser.name[127] = '\0';
	TableRemove(channelData->users, &chatUser);
}
