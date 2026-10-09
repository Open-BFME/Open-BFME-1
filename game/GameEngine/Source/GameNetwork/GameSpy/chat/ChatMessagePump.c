// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
// GameSpy Chat SDK 2007 source algorithm; BFME 2004 field offsets.
#include <string.h>
typedef void *CHAT;
typedef struct ciServerMessage { char *message; char beforeCommand[16]; char *command; } ciServerMessage;
typedef struct ciServerMessageType { const char *command; void (*handler)(CHAT,const ciServerMessage*); } ciServerMessageType;
extern int numServerMessageTypes;
extern ciServerMessageType serverMessageTypes[];
typedef struct ciConnection {
 int connected;
 char beforeSocket[24];
 int socketOpaque;
 int connectState;
 char beforeRaw[0x7f8-0x24];
 void *rawCallback;
 char beforeParam[12];
 void *callbackParam;
} ciConnection;
void ciSocketThink(void*);
ciServerMessage *ciSocketRecv(void*);
void ciAddCallback_(CHAT,int,void*,void*,void*,int,void*,int);
void ciHandleDisconnect(CHAT,const char*);
void ciFilterThink(CHAT);
void ciCallCallbacks(CHAT,int);
static __declspec(noinline) int ciProcessServerMessage(CHAT chat,const ciServerMessage *message) {
 int i;
 for(i=0;i<numServerMessageTypes;i++) {
  if(_strcmpi(message->command,serverMessageTypes[i].command)==0) {
   if(serverMessageTypes[i].handler)serverMessageTypes[i].handler(chat,message);
   return 1;
  }
 }
 return 0;
}
static __declspec(noinline) void ciThink(CHAT chat,int ID) {
 ciServerMessage *message;
 ciConnection *connection=(ciConnection*)chat;
 if(connection->connectState==1) {
  ciSocketThink(&connection->socketOpaque);
  while((message=ciSocketRecv(&connection->socketOpaque))!=0) {
   if(connection->rawCallback) {
    struct { const char *raw; } params;
    params.raw=message->message;
    ciAddCallback_(chat,0,connection->rawCallback,&params,connection->callbackParam,0,0,sizeof(params));
   }
   ciProcessServerMessage(chat,message);
  }
  if(connection->connectState==2)ciHandleDisconnect(chat,"Disconnected");
 }
 ciFilterThink(chat);
 ciCallCallbacks(chat,ID);
}
void ciSocketSendf(void*,const char*,...);
int ciAddWHOISFilter(CHAT,const char*,void*,void*);
void msleep(unsigned int);
int ciCheckFiltersForID(CHAT,int);
int ciCheckCallbacksForID(CHAT,int);
static int ciCheckForID(CHAT chat,int ID) { return ciCheckFiltersForID(chat,ID)||ciCheckCallbacksForID(chat,ID); }
void chatGetUserInfoA(CHAT chat,const char *nick,void *callback,void *param,int blocking) {
 ciConnection *connection=(ciConnection*)chat;
 int ID;
 if(!chat||!connection->connected)return;
 ciSocketSendf(&connection->socketOpaque,"WHOIS %s",nick);
 ID=ciAddWHOISFilter(chat,nick,callback,param);
 if(blocking) {
  do {
   ciThink(chat,ID);
   msleep(10);
  }while(ciCheckForID(chat,ID));
 }
}

int ciAddGETBANFilter(CHAT,const char*,void*,void*);
void chatEnumChannelBansA(CHAT chat, const char *channel, void *callback,
	void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	if (!chat || !connection->connected)
		return;

	ciSocketSendf(&connection->socketOpaque, "MODE %s +b", channel);
	ID = ciAddGETBANFilter(chat, channel, callback, param);

	if (blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
}

int ciAddCWHOFilter(CHAT,const char*,void*,void*);
void chatGetChannelBasicUserInfoA(CHAT chat, const char *channel,
	void *callback, void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	if (!chat || !connection->connected)
		return;

	ciSocketSendf(&connection->socketOpaque, "WHO %s", channel);
	ID = ciAddCWHOFilter(chat, channel, callback, param);

	if (blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
}

void chatThink(CHAT chat)
{
	ciThink(chat, 0);
}

/* The remaining blocking chatMain.c wrappers share this TU's static ciThink,
   which reads the CHAT from ESI (already live in each caller). */
typedef enum { CHATFalse, CHATTrue } CHATBool;
typedef void (*chatEnumUsersCallback)(CHAT chat, CHATBool success,
	const char *channel, int numUsers, const char **users, int *modes,
	void *param);
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
int ciInChannel(CHAT chat, const char *channel);
int ciGetNextID(CHAT chat);
void ciChannelListUsers(CHAT chat, const char *channel, void *callback,
	void *param);
int ciAddNAMESFilter(CHAT chat, const char *channel, void *callback,
	void *param);
int ciGetChannelMode(CHAT chat, const char *channel, CHATChannelMode *mode);
int ciAddCMODEFilter(CHAT chat, const char *channel, void *callback,
	void *param);
const char *ciGetChannelPassword(CHAT chat, const char *channel);
int ciAddLISTFilter(CHAT chat, void *callbackEach, void *callbackAll,
	void *param);
int ciAddJOINFilter(CHAT chat, const char *channel, void *callback,
	void *param, void *callbacks, const char *password);
void ciChannelEntering(CHAT chat, const char *channel);
int ciAddCDKEYFilter(CHAT chat, void *callback, void *param);
const char *ciGetChannelTopic(CHAT chat, const char *channel);
int ciAddTOPICFilter(CHAT chat, const char *channel, void *callback,
	void *param);

void chatEnumChannelsA(CHAT chat, const char *filter, void *callbackEach,
	void *callbackAll, void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	if (!chat || !connection->connected)
		return;
	if (!filter)
		filter = "";

	ciSocketSendf(&connection->socketOpaque, "LIST %s", filter);
	ID = ciAddLISTFilter(chat, callbackEach, callbackAll, param);

	if (blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
}

void chatEnterChannelA(CHAT chat, const char *channel, const char *password,
	void *callbacks, void *callback, void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	if (!chat || !connection->connected)
		return;
	if (!password)
		password = "";

	ciSocketSendf(&connection->socketOpaque, "JOIN %s %s", channel, password);
	ID = ciAddJOINFilter(chat, channel, callback, param, callbacks, password);
	ciChannelEntering(chat, channel);

	if (blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
}

void chatAuthenticateCDKeyA(CHAT chat, const char *cdkey, void *callback,
	void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int success = 1;
	int ID;
	struct
	{
		int result;
		const char *message;
	} callbackParams;

	if (!chat || !connection->connected)
		return;
	if (!cdkey || !cdkey[0])
		success = 0;

	if (!success)
	{
		if (callback)
		{
			callbackParams.result = 0;
			callbackParams.message = "";
			ID = ciGetNextID(chat);
			ciAddCallback_(chat, 31, callback, &callbackParams, param, ID,
				0, sizeof(callbackParams));

			if (blocking)
			{
				do
				{
					ciThink(chat, ID);
					msleep(10);
				}
				while (ciCheckForID(chat, ID));
			}
		}
		return;
	}

	ciSocketSendf(&connection->socketOpaque, "CDKEY %s", cdkey);
	ID = ciAddCDKEYFilter(chat, callback, param);
	if (blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
}

void chatGetChannelTopicA(CHAT chat, const char *channel, void *callback,
	void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	const char *topic;
	int ID;
	struct
	{
		int success;
		const char *channel;
		const char *topic;
	} callbackParams;

	if (!chat || !connection->connected)
		return;

	topic = ciGetChannelTopic(chat, channel);
	if (topic)
	{
		ID = ciGetNextID(chat);
		callbackParams.success = 1;
		callbackParams.channel = channel;
		callbackParams.topic = topic;
		ciAddCallback_(chat, 16, callback, &callbackParams, param, ID,
			(void *)channel, sizeof(callbackParams));
	}
	else
	{
		ciSocketSendf(&connection->socketOpaque, "TOPIC %s", channel);
		ID = ciAddTOPICFilter(chat, channel, callback, param);
	}

	if (blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
}

void chatGetChannelModeA(CHAT chat, const char *channel, void *callback,
	void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	CHATChannelMode mode;
	int ID;
	struct
	{
		int success;
		const char *channel;
		CHATChannelMode *mode;
	} callbackParams;

	if (!chat || !connection->connected)
		return;

	if (ciInChannel(chat, channel) && ciGetChannelMode(chat, channel, &mode))
	{
		ID = ciGetNextID(chat);
		callbackParams.success = 1;
		callbackParams.channel = channel;
		callbackParams.mode = &mode;
		ciAddCallback_(chat, 17, callback, &callbackParams, param, ID,
			0, sizeof(callbackParams));

		if (blocking)
		{
			do
			{
				ciThink(chat, ID);
				msleep(10);
			}
			while (ciCheckForID(chat, ID));
		}
	}
	else
	{
		ciSocketSendf(&connection->socketOpaque, "MODE %s", channel);
		ID = ciAddCMODEFilter(chat, channel, callback, param);
		if (blocking)
		{
			do
			{
				ciThink(chat, ID);
				msleep(10);
			}
			while (ciCheckForID(chat, ID));
		}
	}
}

void chatGetChannelPasswordA(CHAT chat, const char *channel, void *callback,
	void *param, int blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	const char *password;
	int ID;
	struct
	{
		int success;
		const char *channel;
		int enabled;
		const char *password;
	} callbackParams;

	if (!chat || !connection->connected)
		return;

	if (!ciInChannel(chat, channel))
		return;

	password = ciGetChannelPassword(chat, channel);
	ID = ciGetNextID(chat);
	callbackParams.success = 1;
	callbackParams.enabled = 1;
	callbackParams.channel = channel;
	callbackParams.password = password;
	ciAddCallback_(chat, 18, callback, &callbackParams, param, ID,
		0, sizeof(callbackParams));

	if (blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
}

typedef struct ciEnumUsersData
{
	chatEnumUsersCallback callback;
	void *param;
} ciEnumUsersData;

/* 0x00861100: adapter handed to ciChannelListUsers below. */
static void ciEnumUsersCallback(CHAT chat, const char *channel, int numUsers,
	const char **users, int *modes, void *param)
{
	ciEnumUsersData *data = (ciEnumUsersData *)param;
	data->callback(chat, CHATTrue, channel, numUsers, users, modes, data->param);
}

void chatEnumUsersA(
	CHAT chat, const char *channel, chatEnumUsersCallback callback,
	void *param, CHATBool blocking)
{
	register const char *channelHandle;
	register CHAT chatHandle = chat;
	ciConnection *connection = (ciConnection *)chatHandle;
	struct
	{
		chatEnumUsersCallback callback;
		void *param;
	} data;
	int ID;

	if (!chatHandle || !connection->connected)
		return;
	channelHandle = channel;
	if (!channelHandle)
		channelHandle = "";

	if (channelHandle[0] && ciInChannel(chatHandle, channelHandle)) {
		data.callback = callback;
		data.param = param;
		ciChannelListUsers(chatHandle, channelHandle, ciEnumUsersCallback, &data);
		return;
	}

	ciSocketSendf(&connection->socketOpaque, "NAMES %s", channelHandle);
	if (!channelHandle[0])
		channelHandle = 0;
	ID = ciAddNAMESFilter(chatHandle, channelHandle, callback, param);

	if (blocking) {
		do {
			ciThink(chatHandle, ID);
			msleep(10);
		} while (ciCheckForID(chatHandle, ID));
	}
}

/* Keep the ESI-contract blocking caller with static ciThink, as its peers are. */
int ciGetUserMode(CHAT, const char *, const char *);
int ciAddUMODEFilter(CHAT, const char *, const char *,
 void (*)(CHAT, int, const char *, const char *, int, void *), void *);

static __forceinline void Rva008615F0Wait(CHAT chat, int id)
{
 do {
  ciThink(chat, id);
  msleep(10);
 } while (ciCheckFiltersForID(chat, id) || ciCheckCallbacksForID(chat, id));
}

// Separate body at 0x008615F0, bracketed by int3 padding; ret at 0x008616F0.
void Rva008615F0(CHAT chat, const char *channel, const char *user,
 void *callback, void *param, int blocking)
{
 ciConnection *connection = (ciConnection *)chat;
 int mode;
 int id;
 if (!chat || !connection->connected) return;
 mode = ciGetUserMode(chat, channel, user);
 if (mode != -1) {
  struct { int success; const char *channel; const char *user; int mode; } args;
  args.success = 1;
  args.channel = channel;
  args.user = user;
  args.mode = mode;
  id = ciGetNextID(chat);
  ciAddCallback_(chat, 23, callback, &args, param, id, 0, sizeof(args));
  if (blocking) Rva008615F0Wait(chat, id);
 }
 ciSocketSendf(&connection->socketOpaque, "WHO %s", user);
 id = ciAddUMODEFilter(chat, user, channel,
  (void (*)(CHAT, int, const char *, const char *, int, void *))callback, param);
 if (blocking) Rva008615F0Wait(chat, id);
}
