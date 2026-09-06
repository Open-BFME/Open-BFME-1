// cl: /DNDEBUG /MD -Ireference/shims/gamespy
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
  if(_stricmp(message->command,serverMessageTypes[i].command)==0) {
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
