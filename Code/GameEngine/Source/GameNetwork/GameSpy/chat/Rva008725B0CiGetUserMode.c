// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// GameSpy Chat SDK -- ciGetUserMode from chatChannel.c.

#include <string.h>

#define MAX_CHANNEL 257
#define MAX_NAME 128

typedef void *CHAT;

typedef struct ciChatChannel
{
	char name[MAX_CHANNEL];
	unsigned char padName[3];
	void *callbacks[12];
	void *users;
	unsigned char mode[0x20];
	int gotMode;
	char *password;
	int joinCallbackCalled;
	char topic[128];
} ciChatChannel;

typedef struct ciChatUser
{
	char name[MAX_NAME];
	char user[24];
	char address[64];
	int gotUserAndAddress;
	int mode;
} ciChatUser;

typedef struct ciConnection
{
	unsigned char pad0[0x80c];
	void *channelTable;
} ciConnection;

void *TableLookup(void *table, const void *elem);

static ciChatChannel *ciGetChannel(ciConnection *connection,
	const char *channel)
{
	ciChatChannel channelTemp;

	strncpy(channelTemp.name, channel, MAX_CHANNEL);
	channelTemp.name[MAX_CHANNEL - 1] = '\0';
	return (ciChatChannel *)TableLookup(connection->channelTable,
		&channelTemp);
}

int ciGetUserMode(CHAT chat, const char *channel, const char *user)
{
	ciChatChannel *chatChannel;
	ciChatUser userTemp;
	ciChatUser *chatUser;
	ciConnection *connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == 0)
		return -1;

	strncpy(userTemp.name, user, MAX_NAME);
	userTemp.name[MAX_NAME - 1] = '\0';
	chatUser = (ciChatUser *)TableLookup(chatChannel->users, &userTemp);
	if(chatUser == 0)
		return -1;

	return chatUser->mode;
}
