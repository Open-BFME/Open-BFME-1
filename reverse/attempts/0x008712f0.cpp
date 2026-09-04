// _ciCallCallback
// partial score=0.62 date=2026-09-04
// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- ciFreeCallbackData + ciCleanupCallbacks +
   ciCallCallback + ciCallCallbacks, retail 0x0086FDA0 / 0x008702F0 /
   0x008712F0 / 0x008714F0.

   Reconstructed from the 2007 SDK (nitrocaster/GameSpy,
   src/GameSpy/Chat/chatCallbacks.c) in a NEW TU so the two file-static
   helpers keep MSVC 7.1's private register convention (EDI for
   ciFreeCallbackData, EAX+ESI for ciCallCallback) without touching the
   landed 3872B ciAddCallback_ body in chatAddCallback.c.

   CALLBACK_GET_UDPRELAY is a 2007 addition and is omitted so
   CALLBACK_AUTHENTICATE_CDKEY stays type 31; retail's two jump tables
   have 32 entries (types 0..31). */

#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#pragma warning(disable:4055)
#endif

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef enum
{
	CHATEnterSuccess,
	CHATBadChannelName,
	CHATChannelIsFull,
	CHATInviteOnlyChannel,
	CHATBannedFromChannel,
	CHATBadChannelPassword,
	CHATTooManyChannels,
	CHATEnterTimedOut,
	CHATBadChannelMask
} CHATEnterResult;

typedef struct CHATChannelMode
{
	CHATBool InviteOnly;
	CHATBool Private;
	CHATBool Secret;
	CHATBool Moderated;
	CHATBool NoExternalMessages;
	CHATBool OnlyOpsChangeTopic;
	CHATBool OpsObeyChannelLimit;
	int Limit;
} CHATChannelMode;

enum
{
	CALLBACK_RAW,
	CALLBACK_DISCONNECTED,
	CALLBACK_PRIVATE_MESSAGE,
	CALLBACK_INVITED,
	CALLBACK_CHANNEL_MESSAGE,
	CALLBACK_KICKED,
	CALLBACK_USER_JOINED,
	CALLBACK_USER_PARTED,
	CALLBACK_USER_CHANGED_NICK,
	CALLBACK_TOPIC_CHANGED,
	CALLBACK_CHANNEL_MODE_CHANGED,
	CALLBACK_USER_MODE_CHANGED,
	CALLBACK_USER_LIST_UPDATED,
	CALLBACK_ENUM_CHANNELS_EACH,
	CALLBACK_ENUM_CHANNELS_ALL,
	CALLBACK_ENTER_CHANNEL,
	CALLBACK_GET_CHANNEL_TOPIC,
	CALLBACK_GET_CHANNEL_MODE,
	CALLBACK_GET_CHANNEL_PASSWORD,
	CALLBACK_ENUM_USERS,
	CALLBACK_GET_USER_INFO,
	CALLBACK_GET_BASIC_USER_INFO,
	CALLBACK_GET_CHANNEL_BASIC_USER_INFO,
	CALLBACK_GET_USER_MODE,
	CALLBACK_ENUM_CHANNEL_BANS,
	CALLBACK_NICK_ERROR,
	CALLBACK_CHANGE_NICK,
	CALLBACK_NEW_USER_LIST,
	CALLBACK_BROADCAST_KEY_CHANGED,
	CALLBACK_GET_GLOBAL_KEYS,
	CALLBACK_GET_CHANNEL_KEYS,
	CALLBACK_AUTHENTICATE_CDKEY,
	CALLBACK_NUM
};

typedef struct ciCallbackData
{
	int type;
	void *callback;
	void *callbackParams;
	void *param;
	int ID;
	char *channel;
} ciCallbackData;

typedef struct ciConnection
{
	unsigned char pad0[0x820];
	void *callbackList;
} ciConnection;

typedef struct ciCallbackRawParams { char *raw; } ciCallbackRawParams;
typedef struct ciCallbackDisconnectedParams { char *reason; } ciCallbackDisconnectedParams;
typedef struct ciCallbackPrivateMessageParams { char *user; char *message; int type; } ciCallbackPrivateMessageParams;
typedef struct ciCallbackInvitedParams { char *channel; char *user; } ciCallbackInvitedParams;
typedef struct ciCallbackChannelMessageParams { char *channel; char *user; char *message; int type; } ciCallbackChannelMessageParams;
typedef struct ciCallbackKickedParams { char *channel; char *user; char *reason; } ciCallbackKickedParams;
typedef struct ciCallbackUserJoinedParams { char *channel; char *user; int mode; } ciCallbackUserJoinedParams;
typedef struct ciCallbackUserPartedParams { char *channel; char *user; int why; char *reason; char *kicker; } ciCallbackUserPartedParams;
typedef struct ciCallbackUserChangedNickParams { char *channel; char *oldNick; char *newNick; } ciCallbackUserChangedNickParams;
typedef struct ciCallbackTopicChangedParams { char *channel; char *topic; } ciCallbackTopicChangedParams;
typedef struct ciCallbackChannelModeChangedParams { char *channel; CHATChannelMode *mode; } ciCallbackChannelModeChangedParams;
typedef struct ciCallbackUserModeChangedParams { char *channel; char *user; int mode; } ciCallbackUserModeChangedParams;
typedef struct ciCallbackUserListUpdatedParams { char *channel; } ciCallbackUserListUpdatedParams;
typedef struct ciCallbackEnumChannelsEachParams { CHATBool success; int index; char *channel; char *topic; int numUsers; void *param; } ciCallbackEnumChannelsEachParams;
typedef struct ciCallbackEnumChannelsAllParams { CHATBool success; int numChannels; char **channels; char **topics; int *numUsers; } ciCallbackEnumChannelsAllParams;
typedef struct ciCallbackEnterChannelParams { CHATBool success; CHATEnterResult result; char *channel; } ciCallbackEnterChannelParams;
typedef struct ciCallbackGetChannelTopicParams { CHATBool success; char *channel; char *topic; } ciCallbackGetChannelTopicParams;
typedef struct ciCallbackGetChannelModeParams { CHATBool success; char *channel; CHATChannelMode *mode; } ciCallbackGetChannelModeParams;
typedef struct ciCallbackGetChannelPasswordParams { CHATBool success; char *channel; CHATBool enabled; char *password; } ciCallbackGetChannelPasswordParams;
typedef struct ciCallbackEnumUsersParams { CHATBool success; char *channel; int numUsers; char **users; int *modes; } ciCallbackEnumUsersParams;
typedef struct ciCallbackGetUserInfoParams { CHATBool success; char *nick; char *user; char *name; char *address; int numChannels; char **channels; } ciCallbackGetUserInfoParams;
typedef struct ciCallbackGetBasicUserInfoParams { CHATBool success; char *nick; char *user; char *address; } ciCallbackGetBasicUserInfoParams;
typedef struct ciCallbackGetChannelBasicUserInfoParams { CHATBool success; char *channel; char *nick; char *user; char *address; } ciCallbackGetChannelBasicUserInfoParams;
typedef struct ciCallbackGetUserModeParams { CHATBool success; char *channel; char *user; int mode; } ciCallbackGetUserModeParams;
typedef struct ciCallbackEnumChannelBansParams { CHATBool success; char *channel; int numBans; char **bans; } ciCallbackEnumChannelBansParams;
typedef struct ciCallbackNickErrorParams { int type; char *nick; int numSuggestedNicks; char **suggestedNicks; } ciCallbackNickErrorParams;
typedef struct ciCallbackChangeNickParams { CHATBool success; char *oldNick; char *newNick; } ciCallbackChangeNickParams;
typedef struct ciCallbackNewUserListParams { char *channel; int numUsers; char **users; int *modes; } ciCallbackNewUserListParams;
typedef struct ciCallbackBroadcastKeyChangedParams { char *channel; char *user; char *key; char *value; } ciCallbackBroadcastKeyChangedParams;
typedef struct ciCallbackGetGlobalKeysParams { CHATBool success; char *user; int num; char **keys; char **values; } ciCallbackGetGlobalKeysParams;
typedef struct ciCallbackGetChannelKeysParams { CHATBool success; char *channel; char *user; int num; char **keys; char **values; } ciCallbackGetChannelKeysParams;
typedef struct ciCallbackAuthenticateCDKeyParams { int result; char *message; } ciCallbackAuthenticateCDKeyParams;

typedef void (*chatRaw)(CHAT chat, const char *raw, void *param);
typedef void (*chatDisconnected)(CHAT chat, const char *reason, void *param);
typedef void (*chatPrivateMessage)(CHAT chat, const char *user, const char *message, int type, void *param);
typedef void (*chatInvited)(CHAT chat, const char *channel, const char *user, void *param);
typedef void (*chatChannelMessage)(CHAT chat, const char *channel, const char *user, const char *message, int type, void *param);
typedef void (*chatKicked)(CHAT chat, const char *channel, const char *user, const char *reason, void *param);
typedef void (*chatUserJoined)(CHAT chat, const char *channel, const char *user, int mode, void *param);
typedef void (*chatUserParted)(CHAT chat, const char *channel, const char *user, int why, const char *reason, const char *kicker, void *param);
typedef void (*chatUserChangedNick)(CHAT chat, const char *channel, const char *oldNick, const char *newNick, void *param);
typedef void (*chatTopicChanged)(CHAT chat, const char *channel, const char *topic, void *param);
typedef void (*chatChannelModeChanged)(CHAT chat, const char *channel, CHATChannelMode *mode, void *param);
typedef void (*chatUserModeChanged)(CHAT chat, const char *channel, const char *user, int mode, void *param);
typedef void (*chatUserListUpdated)(CHAT chat, const char *channel, void *param);
typedef void (*chatEnumChannelsCallbackEach)(CHAT chat, CHATBool success, int index, const char *channel, const char *topic, int numUsers, void *param);
typedef void (*chatEnumChannelsCallbackAll)(CHAT chat, CHATBool success, int numChannels, const char **channels, const char **topics, int *numUsers, void *param);
typedef void (*chatEnterChannelCallback)(CHAT chat, CHATBool success, CHATEnterResult result, const char *channel, void *param);
typedef void (*chatGetChannelTopicCallback)(CHAT chat, CHATBool success, const char *channel, const char *topic, void *param);
typedef void (*chatGetChannelModeCallback)(CHAT chat, CHATBool success, const char *channel, CHATChannelMode *mode, void *param);
typedef void (*chatGetChannelPasswordCallback)(CHAT chat, CHATBool success, const char *channel, CHATBool enabled, const char *password, void *param);
typedef void (*chatEnumUsersCallback)(CHAT chat, CHATBool success, const char *channel, int numUsers, const char **users, int *modes, void *param);
typedef void (*chatGetUserInfoCallback)(CHAT chat, CHATBool success, const char *nick, const char *user, const char *name, const char *address, int numChannels, const char **channels, void *param);
typedef void (*chatGetBasicUserInfoCallback)(CHAT chat, CHATBool success, const char *nick, const char *user, const char *address, void *param);
typedef void (*chatGetChannelBasicUserInfoCallback)(CHAT chat, CHATBool success, const char *channel, const char *nick, const char *user, const char *address, void *param);
typedef void (*chatGetUserModeCallback)(CHAT chat, CHATBool success, const char *channel, const char *user, int mode, void *param);
typedef void (*chatEnumChannelBansCallback)(CHAT chat, CHATBool success, const char *channel, int numBans, const char **bans, void *param);
typedef void (*chatNickErrorCallback)(CHAT chat, int type, const char *nick, int numSuggestedNicks, const char **suggestedNicks, void *param);
typedef void (*chatChangeNickCallback)(CHAT chat, CHATBool success, const char *oldNick, const char *newNick, void *param);
typedef void (*chatNewUserList)(CHAT chat, const char *channel, int num, const char **users, int *modes, void *param);
typedef void (*chatBroadcastKeyChanged)(CHAT chat, const char *channel, const char *user, const char *key, const char *value, void *param);
typedef void (*chatGetGlobalKeysCallback)(CHAT chat, CHATBool success, const char *user, int num, const char **keys, const char **values, void *param);
typedef void (*chatGetChannelKeysCallback)(CHAT chat, CHATBool success, const char *channel, const char *user, int num, const char **keys, const char **values, void *param);
typedef void (*chatAuthenticateCDKeyCallback)(CHAT chat, int result, const char *message, void *param);

#define gsimalloc malloc
#define gsifree free

#define RAW callbackParams->raw
#define REASON callbackParams->reason
#define USER callbackParams->user
#define MESSAGE callbackParams->message
#define TYPE callbackParams->type
#define CHANNEL callbackParams->channel
#define KICKER callbackParams->kicker
#define TOPIC callbackParams->topic
#define MODE callbackParams->mode
#define SUCCESS callbackParams->success
#define INDEX callbackParams->index
#define NUM_USERS callbackParams->numUsers
#define NUM_CHANNELS callbackParams->numChannels
#define CHANNELS callbackParams->channels
#define TOPICS callbackParams->topics
#define ENABLED callbackParams->enabled
#define PASSWORD callbackParams->password
#define USERS callbackParams->users
#define MODES callbackParams->modes
#define ADDRESS callbackParams->address
#define WHY callbackParams->why
#define OLD_NICK callbackParams->oldNick
#define NEW_NICK callbackParams->newNick
#define NUM_BANS callbackParams->numBans
#define BANS callbackParams->bans
#define NICK callbackParams->nick
#define NAME callbackParams->name
#define NUM callbackParams->num
#define KEY callbackParams->key
#define KEYS callbackParams->keys
#define VALUE callbackParams->value
#define VALUES callbackParams->values
#define RESULT callbackParams->result
#define NUM_SUGGESTED_NICKS callbackParams->numSuggestedNicks
#define SUGGESTED_NICKS callbackParams->suggestedNicks

int ArrayLength(void *array);
void *ArrayNth(void *array, int index);
void ArrayDeleteAt(void *array, int index);
void ArrayFree(void *array);
CHATBool ciInChannel(CHAT chat, const char *channel);
CHATBool ciWasJoinCallbackCalled(CHAT chat, const char *channel);
void ciJoinCallbackCalled(CHAT chat, const char *channel);

static void ciFreeCallbackData(ciCallbackData *data)
{
	switch(data->type)
	{
	case CALLBACK_RAW:
	{
		ciCallbackRawParams *callbackParams = (ciCallbackRawParams *)data->callbackParams;
		gsifree(RAW);
		break;
	}

	case CALLBACK_DISCONNECTED:
	{
		ciCallbackDisconnectedParams *callbackParams = (ciCallbackDisconnectedParams *)data->callbackParams;
		gsifree(REASON);
		break;
	}

	case CALLBACK_PRIVATE_MESSAGE:
	{
		ciCallbackPrivateMessageParams *callbackParams = (ciCallbackPrivateMessageParams *)data->callbackParams;
		gsifree(USER);
		gsifree(MESSAGE);
		break;
	}

	case CALLBACK_INVITED:
	{
		ciCallbackInvitedParams *callbackParams = (ciCallbackInvitedParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		break;
	}

	case CALLBACK_CHANNEL_MESSAGE:
	{
		ciCallbackChannelMessageParams *callbackParams = (ciCallbackChannelMessageParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		gsifree(MESSAGE);
		break;
	}

	case CALLBACK_KICKED:
	{
		ciCallbackKickedParams *callbackParams = (ciCallbackKickedParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		gsifree(REASON);
		break;
	}

	case CALLBACK_USER_JOINED:
	{
		ciCallbackUserJoinedParams *callbackParams = (ciCallbackUserJoinedParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		break;
	}

	case CALLBACK_USER_PARTED:
	{
		ciCallbackUserPartedParams *callbackParams = (ciCallbackUserPartedParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		gsifree(REASON);
		gsifree(KICKER);
		break;
	}

	case CALLBACK_USER_CHANGED_NICK:
	{
		ciCallbackUserChangedNickParams *callbackParams = (ciCallbackUserChangedNickParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(OLD_NICK);
		gsifree(NEW_NICK);
		break;
	}

	case CALLBACK_TOPIC_CHANGED:
	{
		ciCallbackTopicChangedParams *callbackParams = (ciCallbackTopicChangedParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(TOPIC);
		break;
	}

	case CALLBACK_CHANNEL_MODE_CHANGED:
	{
		ciCallbackChannelModeChangedParams *callbackParams = (ciCallbackChannelModeChangedParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(MODE);
		break;
	}

	case CALLBACK_USER_MODE_CHANGED:
	{
		ciCallbackUserModeChangedParams *callbackParams = (ciCallbackUserModeChangedParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		break;
	}

	case CALLBACK_USER_LIST_UPDATED:
	{
		ciCallbackUserListUpdatedParams *callbackParams = (ciCallbackUserListUpdatedParams *)data->callbackParams;
		gsifree(CHANNEL);
		break;
	}

	case CALLBACK_ENUM_CHANNELS_EACH:
	{
		ciCallbackEnumChannelsEachParams *callbackParams = (ciCallbackEnumChannelsEachParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(TOPIC);
		break;
	}

	case CALLBACK_ENUM_CHANNELS_ALL:
	{
		int i;
		ciCallbackEnumChannelsAllParams *callbackParams = (ciCallbackEnumChannelsAllParams *)data->callbackParams;
		for(i = 0 ; i < NUM_CHANNELS ; i++)
		{
			gsifree(CHANNELS[i]);
			gsifree(TOPICS[i]);
		}
		gsifree(CHANNELS);
		gsifree(TOPICS);
		gsifree(NUM_USERS);
		break;
	}

	case CALLBACK_ENTER_CHANNEL:
	{
		ciCallbackEnterChannelParams *callbackParams = (ciCallbackEnterChannelParams *)data->callbackParams;
		gsifree(CHANNEL);
		break;
	}

	case CALLBACK_GET_CHANNEL_TOPIC:
	{
		ciCallbackGetChannelTopicParams *callbackParams = (ciCallbackGetChannelTopicParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(TOPIC);
		break;
	}

	case CALLBACK_GET_CHANNEL_MODE:
	{
		ciCallbackGetChannelModeParams *callbackParams = (ciCallbackGetChannelModeParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(MODE);
		break;
	}

	case CALLBACK_GET_CHANNEL_PASSWORD:
	{
		ciCallbackGetChannelPasswordParams *callbackParams = (ciCallbackGetChannelPasswordParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(PASSWORD);
		break;
	}

	case CALLBACK_ENUM_USERS:
	{
		int i;
		ciCallbackEnumUsersParams *callbackParams = (ciCallbackEnumUsersParams *)data->callbackParams;
		gsifree(CHANNEL);
		for(i = 0 ; i < NUM_USERS ; i++)
			gsifree(USERS[i]);
		gsifree(USERS);
		gsifree(MODES);
		break;
	}

	case CALLBACK_GET_USER_INFO:
	{
		int i;
		ciCallbackGetUserInfoParams *callbackParams = (ciCallbackGetUserInfoParams *)data->callbackParams;
		gsifree(NICK);
		gsifree(USER);
		gsifree(NAME);
		gsifree(ADDRESS);
		for(i = 0 ; i < NUM_CHANNELS ; i++)
			gsifree(CHANNELS[i]);
		gsifree(CHANNELS);
		break;
	}

	case CALLBACK_GET_BASIC_USER_INFO:
	{
		ciCallbackGetBasicUserInfoParams *callbackParams = (ciCallbackGetBasicUserInfoParams *)data->callbackParams;
		gsifree(NICK);
		gsifree(USER);
		gsifree(ADDRESS);
		break;
	}

	case CALLBACK_GET_CHANNEL_BASIC_USER_INFO:
	{
		ciCallbackGetChannelBasicUserInfoParams *callbackParams = (ciCallbackGetChannelBasicUserInfoParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(NICK);
		gsifree(USER);
		gsifree(ADDRESS);
		break;
	}

	case CALLBACK_GET_USER_MODE:
	{
		ciCallbackGetUserModeParams *callbackParams = (ciCallbackGetUserModeParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		break;
	}

	case CALLBACK_ENUM_CHANNEL_BANS:
	{
		int i;
		ciCallbackEnumChannelBansParams *callbackParams = (ciCallbackEnumChannelBansParams *)data->callbackParams;
		gsifree(CHANNEL);
		for(i = 0 ; i < NUM_BANS ; i++)
			gsifree(BANS[i]);
		gsifree(BANS);
		break;
	}

	case CALLBACK_NICK_ERROR:
	{
		int i;
		ciCallbackNickErrorParams *callbackParams = (ciCallbackNickErrorParams *)data->callbackParams;
		gsifree(NICK);
		for(i = 0 ; i < NUM_SUGGESTED_NICKS ; i++)
			gsifree(SUGGESTED_NICKS[i]);
		gsifree(SUGGESTED_NICKS);
		break;
	}

	case CALLBACK_CHANGE_NICK:
	{
		ciCallbackChangeNickParams *callbackParams = (ciCallbackChangeNickParams *)data->callbackParams;
		gsifree(OLD_NICK);
		gsifree(NEW_NICK);
		break;
	}

	case CALLBACK_NEW_USER_LIST:
	{
		int i;
		ciCallbackNewUserListParams *callbackParams = (ciCallbackNewUserListParams *)data->callbackParams;
		gsifree(CHANNEL);
		for(i = 0 ; i < NUM_USERS ; i++)
			gsifree(USERS[i]);
		gsifree(USERS);
		gsifree(MODES);
		break;
	}

	case CALLBACK_BROADCAST_KEY_CHANGED:
	{
		ciCallbackBroadcastKeyChangedParams *callbackParams = (ciCallbackBroadcastKeyChangedParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		gsifree(KEY);
		gsifree(VALUE);
		break;
	}

	case CALLBACK_GET_GLOBAL_KEYS:
	{
		int i;
		ciCallbackGetGlobalKeysParams *callbackParams = (ciCallbackGetGlobalKeysParams *)data->callbackParams;
		gsifree(USER);
		for(i = 0 ; i < NUM ; i++)
		{
			gsifree(KEYS[i]);
			if(VALUES)
				gsifree(VALUES[i]);
		}
		gsifree(KEYS);
		gsifree(VALUES);
		break;
	}

	case CALLBACK_GET_CHANNEL_KEYS:
	{
		int i;
		ciCallbackGetChannelKeysParams *callbackParams = (ciCallbackGetChannelKeysParams *)data->callbackParams;
		gsifree(CHANNEL);
		gsifree(USER);
		for(i = 0 ; i < NUM ; i++)
		{
			gsifree(KEYS[i]);
			if(VALUES)
				gsifree(VALUES[i]);
		}
		gsifree(KEYS);
		gsifree(VALUES);
		break;
	}

	case CALLBACK_AUTHENTICATE_CDKEY:
	{
		ciCallbackAuthenticateCDKeyParams *callbackParams = (ciCallbackAuthenticateCDKeyParams *)data->callbackParams;
		gsifree(MESSAGE);
		break;
	}
	}

	gsifree(data->callbackParams);
}

void ciCleanupCallbacks(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	if(connection->callbackList != NULL)
	{
		ciCallbackData *data;
		int len;
		int i;

		len = ArrayLength(connection->callbackList);

		for(i = 0 ; i < len ; i++)
		{
			data = (ciCallbackData *)ArrayNth(connection->callbackList, i);
			ciFreeCallbackData(data);
		}

		ArrayFree(connection->callbackList);
	}
}

static void ciCallCallback(CHAT chat, ciCallbackData *data)
{
	void *param;

	param = data->param;

	switch(data->type)
	{
	case CALLBACK_RAW:
	{
		ciCallbackRawParams *callbackParams = (ciCallbackRawParams *)data->callbackParams;
		chatRaw callback = (chatRaw)data->callback;
		callback(chat, RAW, param);
		break;
	}

	case CALLBACK_DISCONNECTED:
	{
		ciCallbackDisconnectedParams *callbackParams = (ciCallbackDisconnectedParams *)data->callbackParams;
		chatDisconnected callback = (chatDisconnected)data->callback;
		callback(chat, REASON, param);
		break;
	}

	case CALLBACK_PRIVATE_MESSAGE:
	{
		ciCallbackPrivateMessageParams *callbackParams = (ciCallbackPrivateMessageParams *)data->callbackParams;
		chatPrivateMessage callback = (chatPrivateMessage)data->callback;
		callback(chat, USER, MESSAGE, TYPE, param);
		break;
	}

	case CALLBACK_INVITED:
	{
		ciCallbackInvitedParams *callbackParams = (ciCallbackInvitedParams *)data->callbackParams;
		chatInvited callback = (chatInvited)data->callback;
		callback(chat, CHANNEL, USER, param);
		break;
	}

	case CALLBACK_CHANNEL_MESSAGE:
	{
		ciCallbackChannelMessageParams *callbackParams = (ciCallbackChannelMessageParams *)data->callbackParams;
		chatChannelMessage callback = (chatChannelMessage)data->callback;
		callback(chat, CHANNEL, USER, MESSAGE, TYPE, param);
		break;
	}

	case CALLBACK_KICKED:
	{
		ciCallbackKickedParams *callbackParams = (ciCallbackKickedParams *)data->callbackParams;
		chatKicked callback = (chatKicked)data->callback;
		callback(chat, CHANNEL, USER, REASON, param);
		break;
	}

	case CALLBACK_USER_JOINED:
	{
		ciCallbackUserJoinedParams *callbackParams = (ciCallbackUserJoinedParams *)data->callbackParams;
		chatUserJoined callback = (chatUserJoined)data->callback;
		callback(chat, CHANNEL, USER, MODE, param);
		break;
	}

	case CALLBACK_USER_PARTED:
	{
		ciCallbackUserPartedParams *callbackParams = (ciCallbackUserPartedParams *)data->callbackParams;
		chatUserParted callback = (chatUserParted)data->callback;
		callback(chat, CHANNEL, USER, WHY, REASON, KICKER, param);
		break;
	}

	case CALLBACK_USER_CHANGED_NICK:
	{
		ciCallbackUserChangedNickParams *callbackParams = (ciCallbackUserChangedNickParams *)data->callbackParams;
		chatUserChangedNick callback = (chatUserChangedNick)data->callback;
		callback(chat, CHANNEL, OLD_NICK, NEW_NICK, param);
		break;
	}

	case CALLBACK_TOPIC_CHANGED:
	{
		ciCallbackTopicChangedParams *callbackParams = (ciCallbackTopicChangedParams *)data->callbackParams;
		chatTopicChanged callback = (chatTopicChanged)data->callback;
		callback(chat, CHANNEL, TOPIC, param);
		break;
	}

	case CALLBACK_CHANNEL_MODE_CHANGED:
	{
		ciCallbackChannelModeChangedParams *callbackParams = (ciCallbackChannelModeChangedParams *)data->callbackParams;
		chatChannelModeChanged callback = (chatChannelModeChanged)data->callback;
		callback(chat, CHANNEL, MODE, param);
		break;
	}

	case CALLBACK_USER_MODE_CHANGED:
	{
		ciCallbackUserModeChangedParams *callbackParams = (ciCallbackUserModeChangedParams *)data->callbackParams;
		chatUserModeChanged callback = (chatUserModeChanged)data->callback;
		callback(chat, CHANNEL, USER, MODE, param);
		break;
	}

	case CALLBACK_USER_LIST_UPDATED:
	{
		ciCallbackUserListUpdatedParams *callbackParams = (ciCallbackUserListUpdatedParams *)data->callbackParams;
		chatUserListUpdated callback = (chatUserListUpdated)data->callback;
		callback(chat, CHANNEL, param);
		break;
	}

	case CALLBACK_ENUM_CHANNELS_EACH:
	{
		ciCallbackEnumChannelsEachParams *callbackParams = (ciCallbackEnumChannelsEachParams *)data->callbackParams;
		chatEnumChannelsCallbackEach callback = (chatEnumChannelsCallbackEach)data->callback;
		callback(chat, SUCCESS, INDEX, CHANNEL, TOPIC, NUM_USERS, param);
		break;
	}

	case CALLBACK_ENUM_CHANNELS_ALL:
	{
		ciCallbackEnumChannelsAllParams *callbackParams = (ciCallbackEnumChannelsAllParams *)data->callbackParams;
		chatEnumChannelsCallbackAll callback = (chatEnumChannelsCallbackAll)data->callback;
		callback(chat, SUCCESS, NUM_CHANNELS, (const char **)CHANNELS, (const char **)TOPICS, NUM_USERS, param);
		break;
	}

	case CALLBACK_ENTER_CHANNEL:
	{
		ciCallbackEnterChannelParams *callbackParams = (ciCallbackEnterChannelParams *)data->callbackParams;
		chatEnterChannelCallback callback = (chatEnterChannelCallback)data->callback;
		ciJoinCallbackCalled(chat, CHANNEL);
		callback(chat, SUCCESS, RESULT, CHANNEL, param);
		break;
	}

	case CALLBACK_GET_CHANNEL_TOPIC:
	{
		ciCallbackGetChannelTopicParams *callbackParams = (ciCallbackGetChannelTopicParams *)data->callbackParams;
		chatGetChannelTopicCallback callback = (chatGetChannelTopicCallback)data->callback;
		callback(chat, SUCCESS, CHANNEL, TOPIC, param);
		break;
	}

	case CALLBACK_GET_CHANNEL_MODE:
	{
		ciCallbackGetChannelModeParams *callbackParams = (ciCallbackGetChannelModeParams *)data->callbackParams;
		chatGetChannelModeCallback callback = (chatGetChannelModeCallback)data->callback;
		callback(chat, SUCCESS, CHANNEL, MODE, param);
		break;
	}

	case CALLBACK_GET_CHANNEL_PASSWORD:
	{
		ciCallbackGetChannelPasswordParams *callbackParams = (ciCallbackGetChannelPasswordParams *)data->callbackParams;
		chatGetChannelPasswordCallback callback = (chatGetChannelPasswordCallback)data->callback;
		callback(chat, SUCCESS, CHANNEL, ENABLED, PASSWORD, param);
		break;
	}

	case CALLBACK_ENUM_USERS:
	{
		ciCallbackEnumUsersParams *callbackParams = (ciCallbackEnumUsersParams *)data->callbackParams;
		chatEnumUsersCallback callback = (chatEnumUsersCallback)data->callback;
		callback(chat, SUCCESS, CHANNEL, NUM_USERS, (const char **)USERS, MODES, param);
		break;
	}

	case CALLBACK_GET_USER_INFO:
	{
		ciCallbackGetUserInfoParams *callbackParams = (ciCallbackGetUserInfoParams *)data->callbackParams;
		chatGetUserInfoCallback callback = (chatGetUserInfoCallback)data->callback;
		callback(chat, SUCCESS, NICK, USER, NAME, ADDRESS, NUM_CHANNELS, (const char **)CHANNELS, param);
		break;
	}

	case CALLBACK_GET_BASIC_USER_INFO:
	{
		ciCallbackGetBasicUserInfoParams *callbackParams = (ciCallbackGetBasicUserInfoParams *)data->callbackParams;
		chatGetBasicUserInfoCallback callback = (chatGetBasicUserInfoCallback)data->callback;
		callback(chat, SUCCESS, NICK, USER, ADDRESS, param);
		break;
	}

	case CALLBACK_GET_CHANNEL_BASIC_USER_INFO:
	{
		ciCallbackGetChannelBasicUserInfoParams *callbackParams = (ciCallbackGetChannelBasicUserInfoParams *)data->callbackParams;
		chatGetChannelBasicUserInfoCallback callback = (chatGetChannelBasicUserInfoCallback)data->callback;
		callback(chat, SUCCESS, CHANNEL, NICK, USER, ADDRESS, param);
		break;
	}

	case CALLBACK_GET_USER_MODE:
	{
		ciCallbackGetUserModeParams *callbackParams = (ciCallbackGetUserModeParams *)data->callbackParams;
		chatGetUserModeCallback callback = (chatGetUserModeCallback)data->callback;
		callback(chat, SUCCESS, CHANNEL, USER, MODE, param);
		break;
	}

	case CALLBACK_ENUM_CHANNEL_BANS:
	{
		ciCallbackEnumChannelBansParams *callbackParams = (ciCallbackEnumChannelBansParams *)data->callbackParams;
		chatEnumChannelBansCallback callback = (chatEnumChannelBansCallback)data->callback;
		callback(chat, SUCCESS, CHANNEL, NUM_BANS, (const char **)BANS, param);
		break;
	}

	case CALLBACK_NICK_ERROR:
	{
		ciCallbackNickErrorParams *callbackParams = (ciCallbackNickErrorParams *)data->callbackParams;
		chatNickErrorCallback callback = (chatNickErrorCallback)data->callback;
		callback(chat, TYPE, NICK, NUM_SUGGESTED_NICKS, (const char **)SUGGESTED_NICKS, param);
		break;
	}

	case CALLBACK_CHANGE_NICK:
	{
		ciCallbackChangeNickParams *callbackParams = (ciCallbackChangeNickParams *)data->callbackParams;
		chatChangeNickCallback callback = (chatChangeNickCallback)data->callback;
		callback(chat, SUCCESS, OLD_NICK, NEW_NICK, param);
		break;
	}

	case CALLBACK_NEW_USER_LIST:
	{
		ciCallbackNewUserListParams *callbackParams = (ciCallbackNewUserListParams *)data->callbackParams;
		chatNewUserList callback = (chatNewUserList)data->callback;
		callback(chat, CHANNEL, NUM_USERS, (const char **)USERS, MODES, param);
		break;
	}

	case CALLBACK_BROADCAST_KEY_CHANGED:
	{
		ciCallbackBroadcastKeyChangedParams *callbackParams = (ciCallbackBroadcastKeyChangedParams *)data->callbackParams;
		chatBroadcastKeyChanged callback = (chatBroadcastKeyChanged)data->callback;
		callback(chat, CHANNEL, USER, KEY, VALUE, param);
		break;
	}

	case CALLBACK_GET_GLOBAL_KEYS:
	{
		ciCallbackGetGlobalKeysParams *callbackParams = (ciCallbackGetGlobalKeysParams *)data->callbackParams;
		chatGetGlobalKeysCallback callback = (chatGetGlobalKeysCallback)data->callback;
		callback(chat, SUCCESS, USER, NUM, (const char **)KEYS, (const char **)VALUES, param);
		break;
	}

	case CALLBACK_GET_CHANNEL_KEYS:
	{
		ciCallbackGetChannelKeysParams *callbackParams = (ciCallbackGetChannelKeysParams *)data->callbackParams;
		chatGetChannelKeysCallback callback = (chatGetChannelKeysCallback)data->callback;
		callback(chat, SUCCESS, CHANNEL, USER, NUM, (const char **)KEYS, (const char **)VALUES, param);
		break;
	}

	case CALLBACK_AUTHENTICATE_CDKEY:
	{
		ciCallbackAuthenticateCDKeyParams *callbackParams = (ciCallbackAuthenticateCDKeyParams *)data->callbackParams;
		chatAuthenticateCDKeyCallback callback = (chatAuthenticateCDKeyCallback)data->callback;
		callback(chat, RESULT, MESSAGE, param);
		break;
	}
	}

	ciFreeCallbackData(data);
}

void ciCallCallbacks(CHAT chat, int ID)
{
	ciCallbackData *data;
	ciCallbackData dataCopy;
	int skip;
	ciConnection *connection = (ciConnection *)chat;

	for(skip = 0 ; ArrayLength(connection->callbackList) > skip ; )
	{
		data = (ciCallbackData *)ArrayNth(connection->callbackList, skip);

		if((data->channel != NULL) && !ciInChannel(chat, data->channel))
		{
			ciFreeCallbackData(data);
			ArrayDeleteAt(connection->callbackList, skip);
		}
		else
		{
			if(((data->channel == NULL) || ciWasJoinCallbackCalled(chat, data->channel)) &&
				((ID == 0) || (data->ID == ID)))
			{
				dataCopy = *data;
				ArrayDeleteAt(connection->callbackList, skip);
				ciCallCallback(chat, &dataCopy);
				if(ID != 0)
					return;
			}
			else
			{
				skip++;
			}
		}
	}
}
