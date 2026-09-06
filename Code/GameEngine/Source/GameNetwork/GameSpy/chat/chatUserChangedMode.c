// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// GameSpy Chat SDK -- ciUserChangedMode from chatChannel.c.

#include <string.h>

#define MAX_CHANNEL 257
#define MAX_NAME 128

typedef void *CHAT;
typedef int CHATBool;

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

typedef struct ciCallbackUserModeChangedParams
{
	char *channel;
	char *user;
	int mode;
} ciCallbackUserModeChangedParams;

typedef struct ciConnection
{
	char reserved[0x80c];
	void *channelTable;
} ciConnection;

void *TableLookup(void *table, const void *elem);
void ciAddCallback_(CHAT chat, int type, void *callback, void *params,
	void *callbackParam, int ID, void *param2, int paramsSize);

void ciUserChangedMode(CHAT chat, const char *user, const char *channel,
	int mode, CHATBool enabled)
{
	ciChatChannel channelTemp;
	ciChatChannel *chatChannel;
	ciChatUser userTemp;
	ciChatUser *chatUser;
	ciCallbackUserModeChangedParams params;
	ciConnection *connection = (ciConnection *)chat;
	register char *(*copyString)(char *, const char *, unsigned int) = strncpy;

	copyString(channelTemp.name, channel, MAX_CHANNEL);
	channelTemp.name[MAX_CHANNEL - 1] = '\0';
	chatChannel = (ciChatChannel *)TableLookup(connection->channelTable,
		&channelTemp);
	if (chatChannel == 0)
		return;

	copyString(userTemp.name, user, MAX_NAME);
	userTemp.name[MAX_NAME - 1] = '\0';
	chatUser = (ciChatUser *)TableLookup(chatChannel->users, &userTemp);
	if (chatUser == 0)
		return;

	if (enabled)
		chatUser->mode |= mode;
	else
		chatUser->mode &= ~mode;

	if (chatChannel->callbacks.userModeChanged != 0)
	{
		params.channel = (char *)channel;
		params.user = (char *)user;
		params.mode = chatUser->mode;
		ciAddCallback_(chat, 11, chatChannel->callbacks.userModeChanged,
			&params, chatChannel->callbacks.param, 0, (void *)channel,
			sizeof(params));
	}
}
