// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- chatChannel.c */

#include <stdlib.h>
#include <string.h>

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
