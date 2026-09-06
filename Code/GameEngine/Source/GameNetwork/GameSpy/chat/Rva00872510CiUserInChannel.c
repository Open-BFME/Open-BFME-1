// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// GameSpy Chat SDK -- ciUserInChannel from chatChannel.c.

#include <string.h>

#define MAX_CHANNEL 257
#define MAX_NAME 128

typedef void *CHAT;
typedef int CHATBool;

enum
{
	CHATFalse,
	CHATTrue
};

typedef struct ciChatChannel
{
	char name[MAX_CHANNEL];
	unsigned char padName[3];
	void *callbacks[12];
	void *users;
	unsigned char mode[0x20];
	CHATBool gotMode;
	char *password;
	CHATBool joinCallbackCalled;
	char topic[128];
} ciChatChannel;

typedef struct ciChatUser
{
	char name[MAX_NAME];
	char user[24];
	char address[64];
	CHATBool gotUserAndAddress;
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

CHATBool ciUserInChannel(CHAT chat, const char *channel, const char *user)
{
	ciChatChannel *chatChannel;
	ciChatUser chatUser;
	ciConnection *connection = (ciConnection *)chat;

	chatChannel = ciGetChannel(connection, channel);
	if(chatChannel == 0)
		return CHATFalse;

	strncpy(chatUser.name, user, MAX_NAME);
	chatUser.name[MAX_NAME - 1] = '\0';
	if(TableLookup(chatChannel->users, &chatUser) == 0)
		return CHATFalse;

	return CHATTrue;
}
