// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- ciAddCallback_, retail 0x00870350.
   Reconstructed from the 2007 SDK (nitrocaster/GameSpy,
   src/GameSpy/Chat/chatCallbacks.c).  The 2004 Chat headers are not in
   hand; see ../PROVENANCE.txt.  Retail's jump table at 0x00871270 has
   32 entries (types 0..31); CALLBACK_GET_UDPRELAY is a 2007 addition
   and is omitted so CALLBACK_AUTHENTICATE_CDKEY stays type 31. */

#include <stdlib.h>
#include <string.h>

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

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
typedef struct ciCallbackEnterChannelParams { CHATBool success; int result; char *channel; } ciCallbackEnterChannelParams;
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

#define gsimalloc malloc
#define gsifree free

char *goastrdup(const char *src);
void ArrayAppend(void *array, const void *elem);

#define COPY(param) if(srcParams->param != NULL)\
 {\
 destParams->param = goastrdup(srcParams->param);\
 if(destParams->param == NULL)\
 {\
 gsifree(destParams);\
 gsifree(data.channel);\
 return CHATFalse;\
 }\
 } else {}
#define COPY_MODE() if(srcParams->mode != NULL)\
 {\
 destParams->mode = (CHATChannelMode *)gsimalloc(sizeof(CHATChannelMode));\
 if(destParams->mode == NULL)\
 {\
 gsifree(destParams);\
 gsifree(data.channel);\
 return CHATFalse;\
 }\
 memcpy(destParams->mode, srcParams->mode, sizeof(CHATChannelMode));\
 } else {}
#define COPY_STR_ARRAY(array, num) \
 if(!srcParams->array)\
 destParams->array = NULL;\
 else\
 {\
 destParams->array = (char **)gsimalloc(sizeof(char *) * srcParams->num);\
 if(destParams->array == NULL)\
 {\
 gsifree(destParams);\
 gsifree(data.channel);\
 return CHATFalse;\
 }\
 for(i = 0 ; i < srcParams->num ; i++)\
 {\
 if(srcParams->array[i] == NULL)\
 destParams->array[i] = NULL;\
 else\
 {\
 destParams->array[i] = goastrdup(srcParams->array[i]);\
 if(destParams->array[i] == NULL)\
 {\
 for(i-- ; i >= 0 ; i--)\
 gsifree(destParams->array[i]);\
 gsifree(destParams->array);\
 gsifree(destParams);\
 gsifree(data.channel);\
 return CHATFalse;\
 }\
 }\
 }\
 }
#define COPY_INT_ARRAY(array, num) \
 if(srcParams->num > 0)\
 {\
 len = (int)(sizeof(int) * srcParams->num);\
 destParams->array = (int *)gsimalloc((unsigned int)len);\
 if(destParams->array == NULL)\
 {\
 gsifree(destParams);\
 gsifree(data.channel);\
 return CHATFalse;\
 }\
 memcpy(destParams->array, srcParams->array, (unsigned int)len);\
 } else {}

CHATBool ciAddCallback_(CHAT chat, int type, void *callback, void *callbackParams,
	void *param, int ID, const char *channel, unsigned int callbackParamsSize)
{
	ciCallbackData data;
	int len;
	int i;
	ciConnection *connection;

	memset(&data, 0, sizeof(ciCallbackData));
	data.type = type;
	data.callback = callback;
	data.callbackParams = gsimalloc(callbackParamsSize);
	if(data.callbackParams == NULL)
		return CHATFalse;
	memcpy(data.callbackParams, callbackParams, callbackParamsSize);
	data.param = param;
	data.ID = ID;
	if(channel == NULL)
		data.channel = NULL;
	else
	{
		len = (int)(strlen(channel) + 1);
		data.channel = (char *)gsimalloc((unsigned int)len);
		if(data.channel == NULL)
		{
			gsifree(data.callbackParams);
			return CHATFalse;
		}
		memcpy(data.channel, channel, (unsigned int)len);
	}

	switch(data.type)
	{
	case CALLBACK_RAW:
	{
		ciCallbackRawParams *destParams = (ciCallbackRawParams *)data.callbackParams;
		ciCallbackRawParams *srcParams = (ciCallbackRawParams *)callbackParams;
		COPY(raw);
		break;
	}
	case CALLBACK_DISCONNECTED:
	{
		ciCallbackDisconnectedParams *destParams = (ciCallbackDisconnectedParams *)data.callbackParams;
		ciCallbackDisconnectedParams *srcParams = (ciCallbackDisconnectedParams *)callbackParams;
		COPY(reason);
		break;
	}
	case CALLBACK_PRIVATE_MESSAGE:
	{
		ciCallbackPrivateMessageParams *destParams = (ciCallbackPrivateMessageParams *)data.callbackParams;
		ciCallbackPrivateMessageParams *srcParams = (ciCallbackPrivateMessageParams *)callbackParams;
		COPY(user);
		COPY(message);
		break;
	}
	case CALLBACK_INVITED:
	{
		ciCallbackInvitedParams *destParams = (ciCallbackInvitedParams *)data.callbackParams;
		ciCallbackInvitedParams *srcParams = (ciCallbackInvitedParams *)callbackParams;
		COPY(channel);
		COPY(user);
		break;
	}
	case CALLBACK_CHANNEL_MESSAGE:
	{
		ciCallbackChannelMessageParams *destParams = (ciCallbackChannelMessageParams *)data.callbackParams;
		ciCallbackChannelMessageParams *srcParams = (ciCallbackChannelMessageParams *)callbackParams;
		COPY(channel);
		COPY(user);
		COPY(message);
		break;
	}
	case CALLBACK_KICKED:
	{
		ciCallbackKickedParams *destParams = (ciCallbackKickedParams *)data.callbackParams;
		ciCallbackKickedParams *srcParams = (ciCallbackKickedParams *)callbackParams;
		COPY(channel);
		COPY(user);
		COPY(reason);
		break;
	}
	case CALLBACK_USER_JOINED:
	{
		ciCallbackUserJoinedParams *destParams = (ciCallbackUserJoinedParams *)data.callbackParams;
		ciCallbackUserJoinedParams *srcParams = (ciCallbackUserJoinedParams *)callbackParams;
		COPY(channel);
		COPY(user);
		break;
	}
	case CALLBACK_USER_PARTED:
	{
		ciCallbackUserPartedParams *destParams = (ciCallbackUserPartedParams *)data.callbackParams;
		ciCallbackUserPartedParams *srcParams = (ciCallbackUserPartedParams *)callbackParams;
		COPY(channel);
		COPY(user);
		COPY(reason);
		COPY(kicker);
		break;
	}
	case CALLBACK_USER_CHANGED_NICK:
	{
		ciCallbackUserChangedNickParams *destParams = (ciCallbackUserChangedNickParams *)data.callbackParams;
		ciCallbackUserChangedNickParams *srcParams = (ciCallbackUserChangedNickParams *)callbackParams;
		COPY(channel);
		COPY(oldNick);
		COPY(newNick);
		break;
	}
	case CALLBACK_TOPIC_CHANGED:
	{
		ciCallbackTopicChangedParams *destParams = (ciCallbackTopicChangedParams *)data.callbackParams;
		ciCallbackTopicChangedParams *srcParams = (ciCallbackTopicChangedParams *)callbackParams;
		COPY(channel);
		COPY(topic);
		break;
	}
	case CALLBACK_CHANNEL_MODE_CHANGED:
	{
		ciCallbackChannelModeChangedParams *destParams = (ciCallbackChannelModeChangedParams *)data.callbackParams;
		ciCallbackChannelModeChangedParams *srcParams = (ciCallbackChannelModeChangedParams *)callbackParams;
		COPY(channel);
		COPY_MODE();
		break;
	}
	case CALLBACK_USER_MODE_CHANGED:
	{
		ciCallbackUserModeChangedParams *destParams = (ciCallbackUserModeChangedParams *)data.callbackParams;
		ciCallbackUserModeChangedParams *srcParams = (ciCallbackUserModeChangedParams *)callbackParams;
		COPY(channel);
		COPY(user);
		break;
	}
	case CALLBACK_USER_LIST_UPDATED:
	{
		ciCallbackUserListUpdatedParams *destParams = (ciCallbackUserListUpdatedParams *)data.callbackParams;
		ciCallbackUserListUpdatedParams *srcParams = (ciCallbackUserListUpdatedParams *)callbackParams;
		COPY(channel);
		break;
	}
	case CALLBACK_ENUM_CHANNELS_EACH:
	{
		ciCallbackEnumChannelsEachParams *destParams = (ciCallbackEnumChannelsEachParams *)data.callbackParams;
		ciCallbackEnumChannelsEachParams *srcParams = (ciCallbackEnumChannelsEachParams *)callbackParams;
		COPY(channel);
		COPY(topic);
		break;
	}
	case CALLBACK_ENUM_CHANNELS_ALL:
	{
		ciCallbackEnumChannelsAllParams *destParams = (ciCallbackEnumChannelsAllParams *)data.callbackParams;
		ciCallbackEnumChannelsAllParams *srcParams = (ciCallbackEnumChannelsAllParams *)callbackParams;
		COPY_STR_ARRAY(channels, numChannels);
		COPY_STR_ARRAY(topics, numChannels);
		if(srcParams->numChannels > 0)
		{
			len = (int)(sizeof(int) * srcParams->numChannels);
			destParams->numUsers = (int *)gsimalloc((unsigned int)len);
			if(destParams->numUsers == NULL)
			{
				gsifree(destParams);
				gsifree(data.channel);
				return CHATFalse;
			}
			memcpy(destParams->numUsers, srcParams->numUsers, (unsigned int)len);
		}
		break;
	}
	case CALLBACK_ENTER_CHANNEL:
	{
		ciCallbackEnterChannelParams *destParams = (ciCallbackEnterChannelParams *)data.callbackParams;
		ciCallbackEnterChannelParams *srcParams = (ciCallbackEnterChannelParams *)callbackParams;
		COPY(channel);
		break;
	}
	case CALLBACK_GET_CHANNEL_TOPIC:
	{
		ciCallbackGetChannelTopicParams *destParams = (ciCallbackGetChannelTopicParams *)data.callbackParams;
		ciCallbackGetChannelTopicParams *srcParams = (ciCallbackGetChannelTopicParams *)callbackParams;
		COPY(channel);
		COPY(topic);
		break;
	}
	case CALLBACK_GET_CHANNEL_MODE:
	{
		ciCallbackGetChannelModeParams *destParams = (ciCallbackGetChannelModeParams *)data.callbackParams;
		ciCallbackGetChannelModeParams *srcParams = (ciCallbackGetChannelModeParams *)callbackParams;
		COPY(channel);
		COPY_MODE();
		break;
	}
	case CALLBACK_GET_CHANNEL_PASSWORD:
	{
		ciCallbackGetChannelPasswordParams *destParams = (ciCallbackGetChannelPasswordParams *)data.callbackParams;
		ciCallbackGetChannelPasswordParams *srcParams = (ciCallbackGetChannelPasswordParams *)callbackParams;
		COPY(channel);
		COPY(password);
		break;
	}
	case CALLBACK_ENUM_USERS:
	{
		ciCallbackEnumUsersParams *destParams = (ciCallbackEnumUsersParams *)data.callbackParams;
		ciCallbackEnumUsersParams *srcParams = (ciCallbackEnumUsersParams *)callbackParams;
		COPY(channel);
		COPY_STR_ARRAY(users, numUsers);
		COPY_INT_ARRAY(modes, numUsers);
		break;
	}
	case CALLBACK_GET_USER_INFO:
	{
		ciCallbackGetUserInfoParams *destParams = (ciCallbackGetUserInfoParams *)data.callbackParams;
		ciCallbackGetUserInfoParams *srcParams = (ciCallbackGetUserInfoParams *)callbackParams;
		COPY(nick);
		COPY(user);
		COPY(name);
		COPY(address);
		COPY_STR_ARRAY(channels, numChannels);
		break;
	}
	case CALLBACK_GET_BASIC_USER_INFO:
	{
		ciCallbackGetBasicUserInfoParams *destParams = (ciCallbackGetBasicUserInfoParams *)data.callbackParams;
		ciCallbackGetBasicUserInfoParams *srcParams = (ciCallbackGetBasicUserInfoParams *)callbackParams;
		COPY(nick);
		COPY(user);
		COPY(address);
		break;
	}
	case CALLBACK_GET_CHANNEL_BASIC_USER_INFO:
	{
		ciCallbackGetChannelBasicUserInfoParams *destParams = (ciCallbackGetChannelBasicUserInfoParams *)data.callbackParams;
		ciCallbackGetChannelBasicUserInfoParams *srcParams = (ciCallbackGetChannelBasicUserInfoParams *)callbackParams;
		COPY(channel);
		COPY(nick);
		COPY(user);
		COPY(address);
		break;
	}
	case CALLBACK_GET_USER_MODE:
	{
		ciCallbackGetUserModeParams *destParams = (ciCallbackGetUserModeParams *)data.callbackParams;
		ciCallbackGetUserModeParams *srcParams = (ciCallbackGetUserModeParams *)callbackParams;
		COPY(channel);
		COPY(user);
		break;
	}
	case CALLBACK_ENUM_CHANNEL_BANS:
	{
		ciCallbackEnumChannelBansParams *destParams = (ciCallbackEnumChannelBansParams *)data.callbackParams;
		ciCallbackEnumChannelBansParams *srcParams = (ciCallbackEnumChannelBansParams *)callbackParams;
		COPY(channel);
		COPY_STR_ARRAY(bans, numBans);
		break;
	}
	case CALLBACK_NICK_ERROR:
	{
		ciCallbackNickErrorParams *destParams = (ciCallbackNickErrorParams *)data.callbackParams;
		ciCallbackNickErrorParams *srcParams = (ciCallbackNickErrorParams *)callbackParams;
		COPY(nick);
		COPY_STR_ARRAY(suggestedNicks, numSuggestedNicks);
		break;
	}
	case CALLBACK_CHANGE_NICK:
	{
		ciCallbackChangeNickParams *destParams = (ciCallbackChangeNickParams *)data.callbackParams;
		ciCallbackChangeNickParams *srcParams = (ciCallbackChangeNickParams *)callbackParams;
		COPY(oldNick);
		COPY(newNick);
		break;
	}
	case CALLBACK_NEW_USER_LIST:
	{
		ciCallbackNewUserListParams *destParams = (ciCallbackNewUserListParams *)data.callbackParams;
		ciCallbackNewUserListParams *srcParams = (ciCallbackNewUserListParams *)callbackParams;
		COPY(channel);
		COPY_STR_ARRAY(users, numUsers);
		COPY_INT_ARRAY(modes, numUsers);
		break;
	}
	case CALLBACK_BROADCAST_KEY_CHANGED:
	{
		ciCallbackBroadcastKeyChangedParams *destParams = (ciCallbackBroadcastKeyChangedParams *)data.callbackParams;
		ciCallbackBroadcastKeyChangedParams *srcParams = (ciCallbackBroadcastKeyChangedParams *)callbackParams;
		COPY(channel);
		COPY(user);
		COPY(key);
		COPY(value);
		break;
	}
	case CALLBACK_GET_GLOBAL_KEYS:
	{
		ciCallbackGetGlobalKeysParams *destParams = (ciCallbackGetGlobalKeysParams *)data.callbackParams;
		ciCallbackGetGlobalKeysParams *srcParams = (ciCallbackGetGlobalKeysParams *)callbackParams;
		COPY(user);
		COPY_STR_ARRAY(keys, num);
		COPY_STR_ARRAY(values, num);
		break;
	}
	case CALLBACK_GET_CHANNEL_KEYS:
	{
		ciCallbackGetChannelKeysParams *destParams = (ciCallbackGetChannelKeysParams *)data.callbackParams;
		ciCallbackGetChannelKeysParams *srcParams = (ciCallbackGetChannelKeysParams *)callbackParams;
		COPY(channel);
		COPY(user);
		COPY_STR_ARRAY(keys, num);
		COPY_STR_ARRAY(values, num);
		break;
	}
	case CALLBACK_AUTHENTICATE_CDKEY:
	{
		ciCallbackAuthenticateCDKeyParams *destParams = (ciCallbackAuthenticateCDKeyParams *)data.callbackParams;
		ciCallbackAuthenticateCDKeyParams *srcParams = (ciCallbackAuthenticateCDKeyParams *)callbackParams;
		COPY(message);
		break;
	}
	}

	/* unused label: its presence keeps SUCCESS at +0x39B so the jump table
	   and the first 3872 code bytes match retail. */
done:
	connection = (ciConnection *)chat;
	ArrayAppend(connection->callbackList, &data);

	return CHATTrue;
}
