// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- ciGetUserBasicInfoA from chatChannel.c. */

#include <string.h>

#define MAX_NAME 128
#define MAX_CACHED_USER 24
#define MAX_CACHED_ADDRESS 64

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef struct ciChatUser
{
	char name[MAX_NAME];
	char user[MAX_CACHED_USER];
	char address[MAX_CACHED_ADDRESS];
	CHATBool gotUserAndAddress;
	int mode;
} ciChatUser;

typedef struct ciGetUserBasicInfoData
{
	CHATBool found;
	ciChatUser *chatUser;
	char *user;
	char *address;
} ciGetUserBasicInfoData;

typedef struct ciConnection
{
	unsigned char pad00[0x80C];
	void *channelTable;
} ciConnection;

void TableMap(void *table, void (*map)(void *, void *), void *clientData);
void ciGetUserBasicInfoMap(void *elem, void *clientData);

static void strzcpy(char *dest, const char *source, unsigned int len)
{
	strncpy(dest, source, len);
	dest[len - 1] = '\0';
}

CHATBool ciGetUserBasicInfoA(CHAT chat, const char *nick,
	const char **user, const char **address)
{
	ciChatUser chatUser;
	ciGetUserBasicInfoData data;
	ciConnection *connection = (ciConnection *)chat;

	strzcpy(chatUser.name, nick, MAX_NAME);
	data.chatUser = &chatUser;
	data.found = CHATFalse;

	TableMap(connection->channelTable, ciGetUserBasicInfoMap, &data);

	if (!data.found)
		return CHATFalse;

	if (user)
		*user = data.user;
	if (address)
		*address = data.address;

	return CHATTrue;
}
