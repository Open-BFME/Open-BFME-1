// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- matching filter helpers and RPL handlers at retail 0x0086F070,
   0x0086F210 and 0x0086F300.  This TU keeps the authentic file-static
   filter helpers visible to the handlers so MSVC 7.1 can use the private
   register convention present in the retail chatHandlers.c build. */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef void *CHAT;
typedef int CHATBool;

enum
{

    TYPE_LIST,
    TYPE_JOIN,
    TYPE_TOPIC,
    TYPE_NAMES,
    TYPE_WHOIS,
    TYPE_CMODE,
    TYPE_UMODE,
    TYPE_BAN,
    TYPE_GETBAN,
    TYPE_NICK,
    TYPE_WHO,
    TYPE_CWHO,
    TYPE_GETKEY,
    TYPE_GETCKEY,
    TYPE_GETCHANKEY,
    TYPE_UNQUIET,
    TYPE_CDKEY,
    NUM_TYPES
};

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

typedef struct ciServerMessage
{
    unsigned char reserved0[8];
    char *nick;
    unsigned char reserved0c[0x20 - 0x0c];
    char **params;
    int numParams;
} ciServerMessage;

typedef struct ciFilterMatch
{
    int type;
    const char *name;
    const char *name2;
} ciFilterMatch;

typedef struct LISTData
{
    CHATBool gotStart;
    int numChannels;
    char **channels;
    int *numUsers;
    char **topics;
} LISTData;

typedef struct NAMESData
{
    int len;
    int numUsers;
    char **users;
    int *modes;
} NAMESData;

typedef struct WHOISData
{
    char *user;
    char *name;
    char *address;
    int numChannels;
    char **channels;
} WHOISData;

typedef struct BANData
{
    char *channel;
} BANData;

typedef struct GETBANData
{
    int numBans;
    char **bans;
} GETBANData;

typedef struct GETKEYData
{
    int num;
    char **keys;
    char *channel;
} GETKEYData;

typedef struct GETCKEYData
{
    int num;
    char **keys;
    CHATBool channel;
    CHATBool allBroadcastKeys;
} GETCKEYData;

typedef struct GETCHANKEYData
{
    int num;
    char **keys;
    CHATBool allBroadcastKeys;
} GETCHANKEYData;

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

typedef struct ciServerMessageFilter
{
    int type;
    unsigned int timeout;
    char *name;
    char *name2;
    void *callback;
    void *callback2;
    void *param;
    void *data;
    int ID;
    struct ciServerMessageFilter *pnext;
} ciServerMessageFilter;

typedef struct ciConnection
{
    unsigned char beforeSocket[0x1c];
    unsigned char chatSocket[1];
    unsigned char betweenSocketAndFilters[0x814 - 0x1d];
    ciServerMessageFilter *filterList;
    ciServerMessageFilter *lastFilter;
    int nextID;
} ciConnection;

#define FILTER_TIMEOUT 60000
#define CALLBACK_ENUM_CHANNELS_ALL 14
#define CALLBACK_ENTER_CHANNEL 15
#define CALLBACK_GET_CHANNEL_TOPIC 16
#define CALLBACK_ENUM_USERS 19
#define CALLBACK_GET_USER_INFO 20
#define CALLBACK_GET_BASIC_USER_INFO 21
#define CALLBACK_GET_CHANNEL_BASIC_USER_INFO 22
#define CALLBACK_GET_USER_MODE 23
#define CALLBACK_ENUM_CHANNEL_BANS 24
#define CALLBACK_CHANGE_NICK 26
#define CALLBACK_NEW_USER_LIST 27
#define CALLBACK_GET_GLOBAL_KEYS 29
#define CALLBACK_GET_CHANNEL_KEYS 30
#define CALLBACK_AUTHENTICATE_CDKEY 31

#define ASSERT_TYPE(type) assert((type >= 0) && (type < NUM_TYPES))
#define ASSERT_STR(str) assert(str != NULL); assert(str[0] != '\0')
#define GSI_UNUSED(value) (void)(value)

unsigned int current_time(void);
int __cdecl ciGetNextID(CHAT chat);
char *goastrdup(const char *source);
void ciAddCallback_(CHAT chat, int type, void *callback, void *params,
    void *param, int ID, void *channel, unsigned int paramsSize);
void ciSocketSendf(void *socket, const char *format, ...);

static ciServerMessageFilter *ciFindFilter(CHAT chat, int numMatches,
    ciFilterMatch *matches)
{
    int i;
    const char *name;
    const char *name2;
    ciServerMessageFilter *filter;
    ciConnection *connection = (ciConnection *)chat;

    assert(numMatches > 0);
    assert(matches);

    for (filter = connection->filterList; filter != NULL; filter = filter->pnext)
    {
        for (i = 0; i < numMatches; i++)
        {
            ASSERT_TYPE(matches[i].type);
            if (filter->type == matches[i].type)
            {
                name = matches[i].name;
                name2 = matches[i].name2;
                if ((!name && !filter->name) ||
                    (name && filter->name && (_stricmp(name, filter->name) == 0)))
                {
                    if ((!name2 && !filter->name2) ||
                        (name2 && filter->name2 && (_stricmp(name2, filter->name2) == 0)))
                    {
                        filter->timeout = current_time() + FILTER_TIMEOUT;
                        return filter;
                    }
                }
            }
        }
    }

    return NULL;
}

static ciServerMessageFilter *ciFindGetKeyFilter(CHAT chat,
    const char *channel)
{
    GETKEYData *data;
    ciServerMessageFilter *filter;
    ciConnection *connection = (ciConnection *)chat;

    assert(channel);
    assert(channel[0]);

    for (filter = connection->filterList; filter != NULL; filter = filter->pnext)
    {
        if (filter->type == TYPE_GETKEY)
        {
            data = (GETKEYData *)filter->data;
            if (_stricmp(data->channel, channel) == 0)
                return filter;
        }
    }

    return NULL;
}

static void ciDestroyFilter(ciServerMessageFilter *filter)
{
    assert(filter != NULL);

    free(filter->data);
    free(filter->name);
    free(filter->name2);
    free(filter);
}

static void ciRemoveFilter(CHAT chat, ciServerMessageFilter *filter)
{
    ciServerMessageFilter *pcurr;
    ciServerMessageFilter *pprev = NULL;
    ciConnection *connection = (ciConnection *)chat;

    assert(filter != NULL);

    for (pcurr = connection->filterList; pcurr != NULL; pcurr = pcurr->pnext)
    {
        if (pcurr == filter)
        {
            if (connection->filterList == pcurr)
                connection->filterList = pcurr->pnext;

            if (connection->lastFilter == pcurr)
                connection->lastFilter = pprev;

            if (pprev != NULL)
                pprev->pnext = pcurr->pnext;

            ciDestroyFilter(pcurr);
            return;
        }

        pprev = pcurr;
    }
}

static void ciFinishFilter(CHAT chat, ciServerMessageFilter *filter,
    void *params)
{
    int i;

    assert(filter);
    ASSERT_TYPE(filter->type);

    if (filter->type == TYPE_LIST)
    {
        LISTData *data = (LISTData *)filter->data;

        if (filter->callback2)
            ciAddCallback_(chat, CALLBACK_ENUM_CHANNELS_ALL,
                filter->callback2, params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackEnumChannelsAllParams));

        for (i = 0; i < data->numChannels; i++)
        {
            free(data->channels[i]);
            free(data->topics[i]);
        }
        free(data->channels);
        free(data->topics);
        free(data->numUsers);
    }
    else if (filter->type == TYPE_JOIN)
    {
        if (filter->callback != NULL)
            ciAddCallback_(chat, CALLBACK_ENTER_CHANNEL, filter->callback,
                params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackEnterChannelParams));
    }
    else if (filter->type == TYPE_TOPIC)
    {
        const char *channel =
            ((ciCallbackGetChannelTopicParams *)params)->channel;

        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_CHANNEL_TOPIC, filter->callback,
                params, filter->param, filter->ID, (void *)channel,
                sizeof(ciCallbackGetChannelTopicParams));
    }
    else if (filter->type == TYPE_NAMES)
    {
        NAMESData *data = (NAMESData *)filter->data;

        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_ENUM_USERS, filter->callback, params,
                filter->param, filter->ID, NULL,
                sizeof(ciCallbackEnumUsersParams));

        for (i = 0; i < data->numUsers; i++)
            free(data->users[i]);
        free(data->users);
        free(data->modes);
    }
    else if (filter->type == TYPE_WHOIS)
    {
        WHOISData *data = (WHOISData *)filter->data;

        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_USER_INFO, filter->callback,
                params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackGetUserInfoParams));

        for (i = 0; i < data->numChannels; i++)
            free(data->channels[i]);
        free(data->channels);
        free(data->name);
        free(data->address);
        free(data->user);
    }
    else if (filter->type == TYPE_WHO)
    {
        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_BASIC_USER_INFO,
                filter->callback, params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackGetBasicUserInfoParams));
    }
    else if (filter->type == TYPE_CWHO)
    {
        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_CHANNEL_BASIC_USER_INFO,
                filter->callback, params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackGetBasicUserInfoParams));
    }
    else if (filter->type == TYPE_CMODE)
    {
        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_CHANNEL_MODE, filter->callback,
                params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackGetChannelModeParams));
    }
    else if (filter->type == TYPE_UMODE)
    {
        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_USER_MODE, filter->callback,
                params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackGetUserModeParams));
    }
    else if (filter->type == TYPE_BAN)
    {
        BANData *data = (BANData *)filter->data;
        free(data->channel);
    }
    else if (filter->type == TYPE_GETBAN)
    {
        GETBANData *data = (GETBANData *)filter->data;

        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_ENUM_CHANNEL_BANS,
                filter->callback, params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackEnumChannelBansParams));

        for (i = 0; i < data->numBans; i++)
            free(data->bans[i]);
    }
    else if (filter->type == TYPE_NICK)
    {
        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_CHANGE_NICK, filter->callback,
                params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackChangeNickParams));
    }
    else if (filter->type == TYPE_GETKEY)
    {
        GETKEYData *data = (GETKEYData *)filter->data;

        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_GLOBAL_KEYS, filter->callback,
                params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackGetGlobalKeysParams));

        free(data->channel);
        for (i = 0; i < data->num; i++)
            free(data->keys[i]);
        free(data->keys);
    }
    else if (filter->type == TYPE_GETCKEY)
    {
        GETCKEYData *data = (GETCKEYData *)filter->data;

        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_CHANNEL_KEYS,
                filter->callback, params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackGetChannelKeysParams));

        for (i = 0; i < data->num; i++)
            free(data->keys[i]);
        free(data->keys);
    }
    else if (filter->type == TYPE_GETCHANKEY)
    {
        GETCHANKEYData *data = (GETCHANKEYData *)filter->data;

        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_GET_CHANNEL_KEYS,
                filter->callback, params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackGetChannelKeysParams));

        for (i = 0; i < data->num; i++)
            free(data->keys[i]);
        free(data->keys);
    }
    else if (filter->type == TYPE_UNQUIET)
    {
        NAMESData *data = (NAMESData *)filter->data;

        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_NEW_USER_LIST, filter->callback,
                params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackNewUserListParams));

        for (i = 0; i < data->numUsers; i++)
            free(data->users[i]);
        free(data->users);
        free(data->modes);
    }
    else if (filter->type == TYPE_CDKEY)
    {
        if (filter->callback)
            ciAddCallback_(chat, CALLBACK_AUTHENTICATE_CDKEY,
                filter->callback, params, filter->param, filter->ID, NULL,
                sizeof(ciCallbackAuthenticateCDKeyParams));
    }
    else
    {
        assert(0);
    }

    ciRemoveFilter(chat, filter);
}

void ciRplListEndHandler(CHAT chat, const ciServerMessage *message)
{
    ciFilterMatch match;
    ciServerMessageFilter *filter;

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_LIST;
    filter = ciFindFilter(chat, 1, &match);
    if (filter != NULL)
    {
        LISTData *data = (LISTData *)filter->data;
        ciCallbackEnumChannelsAllParams params;
        params.success = 1;
        params.numChannels = data->numChannels;
        params.channels = data->channels;
        params.numUsers = data->numUsers;
        params.topics = data->topics;

        ciFinishFilter(chat, filter, &params);
    }

    GSI_UNUSED(message);
}

void ciRplWhoisUserHandler(CHAT chat, const ciServerMessage *message)
{
    char *nick;
    ciFilterMatch matches[2];
    ciServerMessageFilter *filter;

    if (message->numParams != 6)
        return;

    nick = message->params[1];

    memset(matches, 0, sizeof(matches));
    matches[0].type = TYPE_WHOIS;
    matches[0].name = nick;
    matches[1].type = TYPE_BAN;
    matches[1].name = nick;

    filter = ciFindFilter(chat, 2, matches);
    if (!filter)
        return;

    if (filter->type == TYPE_WHOIS)
    {
        char *user;
        char *name;
        char *address;
        WHOISData *data = (WHOISData *)filter->data;

        user = message->params[2];
        name = message->params[5];
        address = message->params[3];

        data->user = goastrdup(user);
        if (data->user == NULL)
            return;

        data->name = goastrdup(name);
        if (data->name == NULL)
            return;

        data->address = goastrdup(address);
        if (data->address == NULL)
            return;

        return;
    }

    if (filter->type == TYPE_BAN)
    {
        char *host;
        BANData *data = (BANData *)filter->data;
        ciConnection *connection = (ciConnection *)chat;

        host = message->params[3];
        ciSocketSendf(&connection->chatSocket, "MODE %s +b *!*@%s",
            data->channel, host);
        ciFinishFilter(chat, filter, NULL);
    }
}

void ciRplWhoisChannelsHandler(CHAT chat, const ciServerMessage *message)
{
    char *nick;
    ciServerMessageFilter *filter;
    ciFilterMatch match;

    if (message->numParams != 3)
        return;

    nick = message->params[1];

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_WHOIS;
    match.name = nick;
    filter = ciFindFilter(chat, 1, &match);
    if (filter != NULL)
    {
        char *channels;
        char *str;
        char *channel;
        char **tempPtr;
        WHOISData *data = (WHOISData *)filter->data;

        channels = message->params[2];
        str = strtok(channels, " ");
        while (str != NULL)
        {
            if (str[0] == '-')
                str++;

            if ((str[0] == '@') || (str[0] == '+'))
                str++;

            channel = goastrdup(str);
            if (channel == NULL)
                return;
            tempPtr = (char **)realloc(data->channels,
                sizeof(char *) * (data->numChannels + 1));
            if (tempPtr == NULL)
            {
                free(channel);
                return;
            }
            data->channels = tempPtr;
            data->channels[data->numChannels] = channel;
            data->numChannels++;
            str = strtok(NULL, " ");
        }
    }
}

#define FINISH_FILTER ciFinishFilter(chat, filter, &params)
#define CHATTrue 1

void ciRplEndOfWhoisHandler(CHAT chat, const ciServerMessage * message)
{
	char * nick;
	ciServerMessageFilter * filter;
	ciFilterMatch match;

#ifdef FEEDBACK_HANDLERS
	OutputDebugString("ciRplEndOfWhoisHandler called\n");
#endif

	assert(message->numParams == 3);
	if(message->numParams != 3)
		return; //ERRCON

	// Get the nick.
	////////////////
	nick = message->params[1];

	memset(&match, 0, sizeof(ciFilterMatch));
	match.type = TYPE_WHOIS;
	match.name = nick;
	filter = ciFindFilter(chat, 1, &match);
	if(filter != NULL)
	{
		WHOISData * data = (WHOISData *)filter->data;
		ciCallbackGetUserInfoParams params;
		params.success = (CHATBool)(data->user != NULL);  //PANTS|08.21.00 - false if nothing found
		params.nick = nick;
		params.user = data->user;
		params.name = data->name;
		params.address = data->address;
		params.numChannels = data->numChannels;
		params.channels = data->channels;

		FINISH_FILTER;
	}
}

void ciRplBanListHandler(CHAT chat, const ciServerMessage * message)
{
	ciFilterMatch match;
	ciServerMessageFilter * filter;
	char * channel;
	char * ban;

#ifdef FEEDBACK_HANDLERS
	OutputDebugString("ciRplBanListHandler called\n");
#endif

	assert(message->numParams >= 3);
	if(message->numParams < 3)
		return; //ERRCON

	channel = message->params[1];
	ban = message->params[2];

	// Look for a filter.
	/////////////////////
	memset(&match, 0, sizeof(ciFilterMatch));
	match.type = TYPE_GETBAN;
	match.name = channel;
	filter = ciFindFilter(chat, 1, &match);
	if(filter != NULL)
	{
		int len;
		void * tempPtr;
		GETBANData * data = (GETBANData *)filter->data;
		assert(data != NULL);
		assert(data->numBans >= 0);

		// Increase the ban list.
		/////////////////////////
		tempPtr = realloc(data->bans, sizeof(char *) * (data->numBans + 1));
		if(tempPtr == NULL)
			return; //ERRCON
		data->bans = (char **)tempPtr;

		// Add the new ban.
		///////////////////
		len = (int)(strlen(ban) + 1);
		tempPtr = malloc((unsigned int)len);
		if(tempPtr == NULL)
			return; //ERRCON
		memcpy(tempPtr, ban, (unsigned int)len);
		data->bans[data->numBans] = (char *)tempPtr;
		data->numBans++;
	}
}

void ciRplEndOfBanListHandler(CHAT chat, const ciServerMessage * message)
{
	char * channel;
	ciServerMessageFilter * filter;
	ciFilterMatch match;

#ifdef FEEDBACK_HANDLERS
	OutputDebugString("ciRplEndOfBanListHandler called\n");
#endif

	assert(message->numParams == 3);
	if(message->numParams != 3)
		return; //ERRCON

	channel = message->params[1];

	// Look for a filter.
	/////////////////////
	memset(&match, 0, sizeof(ciFilterMatch));
	match.type = TYPE_GETBAN;
	match.name = channel;
	filter = ciFindFilter(chat, 1, &match);
	if(filter != NULL)
	{
		GETBANData * data = (GETBANData *)filter->data;
		ciCallbackEnumChannelBansParams params;
		params.success = CHATTrue;
		params.channel = channel;
		params.numBans = data->numBans;
		params.bans = data->bans;

		FINISH_FILTER;
	}
}

#define ciAddCallback(chat,type,callback,params,param,ID,channel) ciAddCallback_(chat,type,callback,params,param,ID,channel,sizeof(*(params)))
void ciRplListHandler(CHAT chat, const ciServerMessage * message)
{
	ciFilterMatch match;
	ciServerMessageFilter * filter;

#ifdef FEEDBACK_HANDLERS
	OutputDebugString("ciRplListHandler called\n");
#endif

	assert(message->numParams == 4);
	if(message->numParams != 4)
		return; //ERRCON

	memset(&match, 0, sizeof(ciFilterMatch));
	match.type = TYPE_LIST;
	filter = ciFindFilter(chat, 1, &match);
	if(filter != NULL)
	{
		if(filter->callback != NULL)
		{
			ciCallbackEnumChannelsEachParams params;
			int index;
			char * channel;
			int numUsers;
			char * topic;
			int len;
			void * tempPtr;
			LISTData * data = (LISTData *)filter->data;

			assert(data != NULL);
			//assert(data->gotStart);

			// Get the channel.
			///////////////////
			len = (int)(strlen(message->params[1]) + 1);
			channel = (char *)malloc((unsigned int)len);
			if(channel == NULL)
				return; //ERRCON
			memcpy(channel, message->params[1], (unsigned int)len);

			// Get the num users.
			/////////////////////
			numUsers = atoi(message->params[2]);

			// Get the topic.
			/////////////////
			len = (int)(strlen(message->params[3]) + 1);
			topic = (char *)malloc((unsigned int)len);
			if(topic == NULL)
			{
				free(channel);
				return; //ERRCON
			}
			memcpy(topic, message->params[3], (unsigned int)len);

			// Get the index.
			/////////////////
			index = data->numChannels;

			// Add the callback.
			////////////////////
			params.success = CHATTrue;
			params.index = index;
			params.channel = channel;
			params.topic = topic;
			params.numUsers = numUsers;
			ciAddCallback(chat, CALLBACK_ENUM_CHANNELS_EACH, filter->callback, &params, filter->param, filter->ID, NULL);

			//TODO:only store this stuff if there's an "all" callback

			// Add the channel.
			///////////////////
			tempPtr = realloc(data->channels, sizeof(char *) * (data->numChannels + 1));
			if(tempPtr == NULL)
			{
				free(channel);
				free(topic);
				return; //ERRCON
			}
			data->channels = (char **)tempPtr;
			data->channels[index] = channel;

			// Add the numUsers.
			////////////////////
			tempPtr = realloc(data->numUsers, sizeof(int) * (data->numChannels + 1));
			if(tempPtr == NULL)
			{
				free(channel);
				free(topic);
				return; //ERRCON
			}
			data->numUsers = (int *)tempPtr;
			data->numUsers[index] = numUsers;

			// Add the topic.
			/////////////////
			tempPtr = realloc(data->topics, sizeof(char *) * (data->numChannels + 1));
			if(tempPtr == NULL)
			{
				free(channel);
				free(topic);
				return; //ERRCON
			}
			data->topics = (char **)tempPtr;
			data->topics[index] = topic;

			// One more channel.
			////////////////////
			data->numChannels++;
		}
	}
}

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

void ciSetChannelTopic(CHAT chat, const char *channel, const char *topic);
chatChannelCallbacks *ciGetChannelCallbacks(CHAT chat, const char *channel);

void ciRplTopicHandler(CHAT chat, const ciServerMessage * message)
{
	ciFilterMatch match;
	ciServerMessageFilter * filter;
	char * topic;
	char * channel;



	assert(message->numParams == 3);
	if(message->numParams != 3)
		return; //ERRCON

	channel = message->params[1];
	topic = message->params[2];

	// Set the channel's topic.
	///////////////////////////
	ciSetChannelTopic(chat, channel, topic);

	// Setup a filter match.
	////////////////////////
	memset(&match, 0, sizeof(ciFilterMatch));
	match.type = TYPE_TOPIC;
	match.name = channel;

	// Find the filter.
	///////////////////
	filter = ciFindFilter(chat, 1, &match);
	if(filter != NULL)
	{
		ciCallbackGetChannelTopicParams params;
		params.success = CHATTrue;
		params.channel = channel;
		params.topic = topic;

		FINISH_FILTER;
	}
	else
	{
		// No filter, probably checking the topic on join.
		//////////////////////////////////////////////////
		chatChannelCallbacks * callbacks;
		callbacks = ciGetChannelCallbacks(chat, channel);
		if((callbacks != NULL) && (callbacks->topicChanged != NULL))
		{
			ciCallbackTopicChangedParams params;
			params.channel = channel;
			params.topic = topic;
			ciAddCallback(chat, CALLBACK_TOPIC_CHANGED, (void*)callbacks->topicChanged, &params, callbacks->param, 0, channel);
		}
	}
}

void ciRplNoTopicHandler(CHAT chat, const ciServerMessage * message)
{
	ciFilterMatch match;
	ciServerMessageFilter * filter;
	char * channel;



	assert(message->numParams >= 2);
	if(message->numParams < 2)
		return; //ERRCON

	// Get the channel.
	///////////////////
	channel = message->params[1];

	// Setup the filter match.
	//////////////////////////
	memset(&match, 0, sizeof(ciFilterMatch));
	match.type = TYPE_TOPIC;
	match.name = channel;

	// Find the filter.
	///////////////////
	filter = ciFindFilter(chat, 1, &match);
	if(filter != NULL)
	{
		ciCallbackGetChannelTopicParams params;
		params.success = CHATTrue;
		params.channel = channel;
		params.topic = "";

		FINISH_FILTER;
	}
	else
	{
		// No filter, probably checking the topic on join.
		//////////////////////////////////////////////////
		chatChannelCallbacks * callbacks;
		callbacks = ciGetChannelCallbacks(chat, channel);
		if((callbacks != NULL) && (callbacks->topicChanged != NULL))
		{
			ciCallbackTopicChangedParams params;
			params.channel = channel;
			params.topic = "";
			ciAddCallback(chat, CALLBACK_TOPIC_CHANGED, (void*)callbacks->topicChanged, &params, callbacks->param, 0, channel);
		}
	}
}

void ciRplListStartHandler(CHAT chat, const ciServerMessage * message)
{
	ciFilterMatch match;
	ciServerMessageFilter * filter;



	memset(&match, 0, sizeof(ciFilterMatch));
	match.type = TYPE_LIST;
	filter = ciFindFilter(chat, 1, &match);
	if(filter != NULL)
	{
		LISTData * data = (LISTData *)filter->data;
		assert(data != NULL);
		//assert(!data->gotStart);

		data->gotStart = CHATTrue;
	}

	(void)message;
}

typedef struct ciNickConnection
{
    int connected;
    CHATBool connecting;
    unsigned char pad08[0x510 - 0x08];
    char uniquenick[1];
} ciNickConnection;
enum { CHAT_INVALID_UNIQUENICK = 4 };
void ciNickError(CHAT chat, int type, const char *nick, int numSuggestedNicks, char **suggestedNicks);

void ciErrRegisterNickFailedHandler(CHAT chat,
    const ciServerMessage *message)
{
    int num;
    char *nicks;
    char *nick;
    char **nickArray;
    int i;
    ciNickConnection *connection = (ciNickConnection *)chat;

    assert(message->numParams == 4);
    if (message->numParams != 4)
        return;

    num = atoi(message->params[1]);
    nicks = message->params[2];

    if (!connection->connecting)
        return;

    nickArray = (char **)malloc(sizeof(char *) * num);
    if (!nickArray)
        return;

    nick = strtok(nicks, "\\");
    for (i = 0; (i < num) && nick; i++)
    {
        nickArray[i] = goastrdup(nick);
        if (!nickArray[i])
            break;
        nick = strtok(NULL, "\\");
    }

    num = i;
    ciNickError(chat, CHAT_INVALID_UNIQUENICK,
        connection->uniquenick, num, nickArray);

    for (i = 0; i < num; i++)
        free(nickArray[i]);
    free(nickArray);
}

void ciRplCDKeyHandler(CHAT chat, const ciServerMessage *message)
{
    ciFilterMatch match;
    ciServerMessageFilter *filter;
    int result;
    char *msg;

    assert(message->numParams == 3);
    if (message->numParams != 3)
        return;

    result = atoi(message->params[1]);
    msg = message->params[2];

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_CDKEY;

    filter = ciFindFilter(chat, 1, &match);
    if (filter)
    {
        ciCallbackAuthenticateCDKeyParams params;
        params.result = result;
        params.message = msg;
        ciFinishFilter(chat, filter, &params);
    }
}




enum
{
    MODE_END,
    MODE_BAN,
    MODE_INVITE_ONLY,
    MODE_LIMIT,
    MODE_PRIVATE,
    MODE_SECRET,
    MODE_KEY,
    MODE_MODERATED,
    MODE_NO_EXTERNAL_MESSAGES,
    MODE_ONLY_OPS_CHANGE_TOPIC,
    MODE_OP,
    MODE_VOICE,
    MODE_USERS_HIDDEN,
    MODE_RECEIVE_WALLOPS,
    MODE_OPS_OBEY_CHANNEL_LIMIT
};

typedef struct ciModeChange
{
    int mode;
    CHATBool enable;
    char *param;
} ciModeChange;


enum { CHAT_VOICE=1, CHAT_OP=2 };
ciModeChange *ciParseMode(char *mode, char **params, int numParams);
CHATBool ciInChannel(CHAT chat, const char *channel);
void ciSetChannelPassword(CHAT chat, const char *channel,
    const char *password);
void ciUserChangedMode(CHAT chat, const char *user, const char *channel,
    int mode, CHATBool enable);
CHATBool ciGetChannelMode(CHAT chat, const char *channel,
    CHATChannelMode *mode);
void ciSetChannelMode(CHAT chat, const char *channel, CHATChannelMode *mode);
static void ciApplyChangesToMode(CHATChannelMode *mode,
    ciModeChange *changes)
{
    ciModeChange *change;

    for (change = changes; change->mode != MODE_END; change++)
    {
        switch (change->mode)
        {
        case MODE_BAN:
            break;
        case MODE_INVITE_ONLY:
            mode->InviteOnly = change->enable;
            break;
        case MODE_LIMIT:
            if (change->enable && change->param)
                mode->Limit = atoi(change->param);
            else
                mode->Limit = 0;
            break;
        case MODE_PRIVATE:
            mode->Private = change->enable;
            break;
        case MODE_SECRET:
            mode->Secret = change->enable;
            break;
        case MODE_KEY:
            break;
        case MODE_MODERATED:
            mode->Moderated = change->enable;
            break;
        case MODE_NO_EXTERNAL_MESSAGES:
            mode->NoExternalMessages = change->enable;
            break;
        case MODE_ONLY_OPS_CHANGE_TOPIC:
            mode->OnlyOpsChangeTopic = change->enable;
            break;
        case MODE_OP:
            break;
        case MODE_VOICE:
            break;
        case MODE_USERS_HIDDEN:
            break;
        case MODE_RECEIVE_WALLOPS:
            break;
        case MODE_OPS_OBEY_CHANNEL_LIMIT:
            mode->OpsObeyChannelLimit = change->enable;
            break;
        default:
            assert(0);
        }
    }
}

void ciModeHandler(CHAT chat, const ciServerMessage *message)
{
    ciModeChange *changes;
    ciModeChange *change;
    CHATChannelMode channelMode;
    char *channel;
    char *mode;

    assert(message->numParams >= 2);
    if (message->numParams < 2)
        return;

    channel = message->params[0];
    mode = message->params[1];

    if (!ciInChannel(chat, channel))
        return;

    changes = ciParseMode(mode, message->params + 2,
        message->numParams - 2);
    if (changes == NULL)
        return;

    for (change = changes; change->mode != MODE_END; change++)
    {
        switch (change->mode)
        {
        case MODE_BAN:
            break;
        case MODE_INVITE_ONLY:
            break;
        case MODE_LIMIT:
            break;
        case MODE_PRIVATE:
            break;
        case MODE_SECRET:
            break;
        case MODE_KEY:
            if (change->enable)
                ciSetChannelPassword(chat, channel, change->param);
            else
                ciSetChannelPassword(chat, channel, NULL);
            break;
        case MODE_MODERATED:
            break;
        case MODE_NO_EXTERNAL_MESSAGES:
            break;
        case MODE_ONLY_OPS_CHANGE_TOPIC:
            break;
        case MODE_USERS_HIDDEN:
            break;
        case MODE_RECEIVE_WALLOPS:
            break;
        case MODE_OP:
            if (change->param)
                ciUserChangedMode(chat, change->param, channel,
                    CHAT_OP, change->enable);
            break;
        case MODE_VOICE:
            if (change->param)
                ciUserChangedMode(chat, change->param, channel,
                    CHAT_VOICE, change->enable);
            break;
        case MODE_OPS_OBEY_CHANNEL_LIMIT:
            break;
        default:
            assert(0);
        }
    }

    if (!ciGetChannelMode(chat, channel, &channelMode))
    {
        free(changes);
        return;
    }

    ciApplyChangesToMode(&channelMode, changes);
    ciSetChannelMode(chat, channel, &channelMode);
    free(changes);
}

void ciRplChannelModeIsHandler(CHAT chat, const ciServerMessage * message)
{
	char * channel;
	char * modes;
	ciModeChange * changes;
	CHATChannelMode mode;
	CHATChannelMode dummyMode;
	ciServerMessageFilter * filter;
	ciFilterMatch match;



	assert(message->numParams >=3);
	if(message->numParams < 3)
		return; //ERRCON

	channel = message->params[1];
	modes = message->params[2];

	// Parse the mode.
	//////////////////
	changes = ciParseMode(modes, message->params + 3, message->numParams - 3);
	if(changes == NULL)
		return; //ERRCON

	// Fill the mode struct.
	////////////////////////
	memset(&mode, 0, sizeof(CHATChannelMode));
	ciApplyChangesToMode(&mode, changes);

	// Check if we have this channel's mode.
	////////////////////////////////////////
	if(!ciGetChannelMode(chat, channel, &dummyMode))
	{
		chatChannelCallbacks * callbacks;

		// Set the mode.
		////////////////
		ciSetChannelMode(chat, channel, &mode);

		// Mode changed callback?
		/////////////////////////
		callbacks = ciGetChannelCallbacks(chat, channel);
		if((callbacks != NULL) && (callbacks->channelModeChanged != NULL))
		{
			ciCallbackChannelModeChangedParams params;
			params.channel = channel;
			params.mode = &mode;
			ciAddCallback(chat, CALLBACK_CHANNEL_MODE_CHANGED, (void*)callbacks->channelModeChanged, &params, callbacks->param, 0, channel);
		}
	}

	// Were we waiting for this?
	////////////////////////////
	memset(&match, 0, sizeof(ciFilterMatch));
	match.type = TYPE_CMODE;
	match.name = channel;
	filter = ciFindFilter(chat, 1, &match);
	if(filter != NULL)
	{
		ciCallbackGetChannelModeParams params;
		params.success = CHATTrue;
		params.channel = channel;
		params.mode = &mode;

		FINISH_FILTER;
	}

	// gsifree the changes.
	////////////////////
	free(changes);
}

enum
{
    CHATFalse = 0,
    CHATChannelIsFull = 2,
    CHATTooManyChannels = 6
};

void ciErrTooManyChannelsHandler(CHAT chat, const ciServerMessage *message)
{
    ciFilterMatch match;
    ciServerMessageFilter *filter;
    char *channel;

    assert(message->numParams == 3);
    if (message->numParams != 3)
        return;

    channel = message->params[1];

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_JOIN;
    match.name = channel;
    filter = ciFindFilter(chat, 1, &match);
    if (filter != NULL)
    {
        ciCallbackEnterChannelParams params;
        params.success = CHATFalse;
        params.result = CHATTooManyChannels;
        params.channel = channel;

        ciFinishFilter(chat, filter, &params);
    }
}

void ciErrChannelIsFullHandler(CHAT chat, const ciServerMessage *message)
{
    ciFilterMatch match;
    ciServerMessageFilter *filter;
    char *channel;

    assert(message->numParams == 3);
    if (message->numParams != 3)
        return;

    channel = message->params[1];

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_JOIN;
    match.name = channel;
    filter = ciFindFilter(chat, 1, &match);
    if (filter != NULL)
    {
        ciCallbackEnterChannelParams params;
        params.success = CHATFalse;
        params.result = CHATChannelIsFull;
        params.channel = channel;

        ciFinishFilter(chat, filter, &params);
    }
}

enum { CHATInviteOnlyChannel=3, CHATBannedFromChannel=4, CHATBadChannelPassword=5, CHATBadChannelMask=8 };
void ciErrInviteOnlyChanHandler(CHAT chat, const ciServerMessage *message)
{
    ciFilterMatch match;
    ciServerMessageFilter *filter;
    char *channel;

    assert(message->numParams == 3);
    if (message->numParams != 3)
        return;

    channel = message->params[1];

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_JOIN;
    match.name = channel;
    filter = ciFindFilter(chat, 1, &match);
    if (filter != NULL)
    {
        ciCallbackEnterChannelParams params;
        params.success = CHATFalse;
        params.result = CHATInviteOnlyChannel;
        params.channel = channel;

        ciFinishFilter(chat, filter, &params);
    }
}

void ciErrBannedFromChanHandler(CHAT chat, const ciServerMessage *message)
{
    ciFilterMatch match;
    ciServerMessageFilter *filter;
    char *channel;

    assert(message->numParams == 3);
    if (message->numParams != 3)
        return;

    channel = message->params[1];

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_JOIN;
    match.name = channel;
    filter = ciFindFilter(chat, 1, &match);
    if (filter != NULL)
    {
        ciCallbackEnterChannelParams params;
        params.success = CHATFalse;
        params.result = CHATBannedFromChannel;
        params.channel = channel;

        ciFinishFilter(chat, filter, &params);
    }
}

void ciErrBadChannelKeyHandler(CHAT chat, const ciServerMessage *message)
{
    ciFilterMatch match;
    ciServerMessageFilter *filter;
    char *channel;

    assert(message->numParams == 3);
    if (message->numParams != 3)
        return;

    channel = message->params[1];

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_JOIN;
    match.name = channel;
    filter = ciFindFilter(chat, 1, &match);
    if (filter != NULL)
    {
        ciCallbackEnterChannelParams params;
        params.success = CHATFalse;
        params.result = CHATBadChannelPassword;
        params.channel = channel;

        ciFinishFilter(chat, filter, &params);
    }
}

void ciErrBadChanMaskHandler(CHAT chat, const ciServerMessage *message)
{
    ciFilterMatch match;
    ciServerMessageFilter *filter;
    char *channel;

    assert(message->numParams == 3);
    if (message->numParams != 3)
        return;

    channel = message->params[1];

    memset(&match, 0, sizeof(ciFilterMatch));
    match.type = TYPE_JOIN;
    match.name = channel;
    filter = ciFindFilter(chat, 1, &match);
    if (filter != NULL)
    {
        ciCallbackEnterChannelParams params;
        params.success = CHATFalse;
        params.result = CHATBadChannelMask;
        params.channel = channel;

        ciFinishFilter(chat, filter, &params);
    }
}

enum { CHATBadChannelName=1 };
void ciErrNoSuchChannelHandler(CHAT chat, const ciServerMessage * message)
{
	ciFilterMatch matches[2];
	ciServerMessageFilter * filter;
	char * channel;

#ifdef FEEDBACK_HANDLERS
	OutputDebugString("ciErrNoSuchChannel called\n");
#endif

	assert(message->numParams == 3);
	if(message->numParams != 3)
		return; //ERRCON

	// Get the channel.
	///////////////////
	channel = message->params[1];

	// Setup the filter matches.
	////////////////////////////
	memset(&matches, 0, sizeof(ciFilterMatch));
	matches[0].type = TYPE_JOIN;
	matches[0].name = channel;
	matches[1].type = TYPE_CMODE;
	matches[1].name = channel;

	// Look for a matching filter.
	//////////////////////////////
	filter = ciFindFilter(chat, 2, matches);
	if(filter)
	{
		// Join?
		////////
		if(filter->type == TYPE_JOIN)
		{
			ciCallbackEnterChannelParams params;
			params.success = CHATFalse;
			params.result = CHATBadChannelName;
			params.channel = channel;

			FINISH_FILTER;

			return;
		}

		// Channel mode?
		////////////////
		if(filter->type == TYPE_CMODE)
		{
			ciCallbackGetChannelModeParams params;
			params.success = CHATFalse;
			params.channel = channel;
			params.mode = NULL;

			FINISH_FILTER;

			return;
		}
	}

	// GetKey?
	//////////
	filter = ciFindGetKeyFilter(chat, channel);
	if(filter)
	{
		ciCallbackGetGlobalKeysParams params;
		params.success = CHATFalse;
		params.user = NULL;
		params.num = 0;
		params.keys = NULL;
		params.values = NULL;

		FINISH_FILTER;

		return;
	}
}

/* GameSpy Chat SDK 2007 timeout handling, without post-retail UDP relay filter. */
enum { CHATEnterTimedOut = 7 };
static void ciFilterTimedout(CHAT chat, ciServerMessageFilter * filter)
{
	assert(filter);
	ASSERT_TYPE(filter->type);

	// Check the type.
	//////////////////
	if(filter->type == TYPE_LIST)
	{
		ciCallbackEnumChannelsAllParams params;
		params.success = 0;
		params.numChannels = 0;
		params.channels = NULL;
		params.topics = NULL;
		params.numUsers = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_JOIN)
	{
		ciCallbackEnterChannelParams params;
		params.success = 0;
		params.result = CHATEnterTimedOut;
		params.channel = filter->name;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_TOPIC)
	{
		ciCallbackGetChannelTopicParams params;
		params.success = 0;
		params.channel = filter->name;
		params.topic = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_NAMES)
	{
		ciCallbackEnumUsersParams params;
		params.success = 0;
		params.channel = filter->name;
		params.numUsers = 0;
		params.users = NULL;
		params.modes = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_WHOIS)
	{
		ciCallbackGetUserInfoParams params;
		params.success = 0;
		params.nick = filter->name;
		params.user = NULL;
		params.name = NULL;
		params.address = NULL;
		params.numChannels = 0;
		params.channels = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_WHO)
	{
		ciCallbackGetBasicUserInfoParams params;
		params.success = 0;
		params.nick = filter->name;
		params.user = NULL;
		params.address = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_CWHO)
	{
		ciCallbackGetChannelBasicUserInfoParams params;
		params.success = 0;
		params.channel = filter->name;
		params.nick = NULL;
		params.user = NULL;
		params.address = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_CMODE)
	{
		ciCallbackGetChannelModeParams params;
		params.success = 0;
		params.channel = filter->name;
		params.mode = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_UMODE)
	{
		ciCallbackGetUserModeParams params;
		params.success = 0;
		params.channel = filter->name2;
		params.user = filter->name;
		params.mode = 0;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_BAN)
	{
		ciFinishFilter(chat, filter, NULL);
	}
	else if(filter->type == TYPE_GETBAN)
	{
		ciCallbackEnumChannelBansParams params;
		params.channel = filter->name;
		params.numBans = 0;
		params.bans = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_NICK)
	{
		ciCallbackChangeNickParams params;
		params.success = 0;
		params.oldNick = filter->name;
		params.newNick = filter->name2;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_GETKEY)
	{
		ciCallbackGetGlobalKeysParams params;
		params.success = 0;
		params.user = NULL;
		params.num = 0;
		params.keys = NULL;
		params.values = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_GETCKEY)
	{
		ciCallbackGetChannelKeysParams params;
		params.success = 0;
		params.channel = NULL;
		params.user = NULL;
		params.num = 0;
		params.keys = NULL;
		params.values = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_GETCHANKEY)
	{
		ciCallbackGetChannelKeysParams params;
		params.success = 0;
		params.channel = NULL;
		params.user = NULL;
		params.num = 0;
		params.keys = NULL;
		params.values = NULL;

		FINISH_FILTER;
	}
	else if(filter->type == TYPE_UNQUIET)
	{
		ciRemoveFilter(chat, filter);
	}
	else if(filter->type == TYPE_CDKEY)
	{
		ciCallbackAuthenticateCDKeyParams params;
		params.result = 0;
		params.message = "Timed out";

		FINISH_FILTER;
	}
	else
	{
		assert(0);
	}
}


void ciFilterThink(CHAT chat) {
 ciServerMessageFilter *filter,*pnext;
 unsigned int now;
 ciConnection *connection=(ciConnection *)chat;
 now=current_time();
 for(filter=connection->filterList;filter;filter=pnext) {
  pnext=filter->pnext;
  if(now>filter->timeout)ciFilterTimedout(chat,filter);
 }
}
void ciFilterCleanup(CHAT chat) {
 ciConnection *connection=(ciConnection *)chat;
 while(connection->filterList)ciFilterTimedout(chat,connection->filterList);
}
