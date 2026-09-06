// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK 2007 channel nick-change algorithm, BFME 2004 ABI.
   Retail NICK handler calls ciUserChangedNick; TableMap identifies its callback. */
#include <string.h>
typedef void *CHAT;
typedef struct ciChatUser {
 char name[128]; char user[24]; char address[64];
 int gotUserAndAddress; int mode;
} ciChatUser;
typedef struct chatChannelCallbacks {
 void *channelMessage,*kicked,*userJoined,*userParted,*userChangedNick;
 void *topicChanged,*channelModeChanged,*userModeChanged,*userListUpdated;
 void *newUserList,*broadcastKeyChanged,*param;
} chatChannelCallbacks;
typedef struct ciChatChannel {
 char name[257]; chatChannelCallbacks callbacks; void *users;
} ciChatChannel;
typedef struct ciConnection {
 unsigned char beforeChannelTable[0x80c]; void *channelTable;
} ciConnection;
typedef struct ciUserChangedNickData {CHAT chat; const char *oldNick,*newNick;} ciUserChangedNickData;
typedef struct ciCallbackUserChangedNickParams {char *channel,*oldNick,*newNick;} ciCallbackUserChangedNickParams;
void *TableLookup(void *,const void *);
int TableRemove(void *,const void *);
void TableEnter(void *,const void *);
void TableMap(void *,void (*)(void *,void *),void *);
int ciWasJoinCallbackCalled(CHAT,const char *);
void ciAddCallback_(CHAT,int,void *,void *,void *,int,const char *,int);
static void ciUserChangeNickMap(void *elem,void *clientData) {
 ciChatChannel *channel=(ciChatChannel *)elem;
 ciChatUser tempUser;
 ciChatUser *user;
 ciUserChangedNickData *data=(ciUserChangedNickData *)clientData;
 ciCallbackUserChangedNickParams params;
 user=(ciChatUser *)TableLookup(channel->users,data->oldNick);
 if(user) {
  memcpy(&tempUser,user,sizeof(ciChatUser));
  TableRemove(channel->users,user);
  user=&tempUser;
  strncpy(user->name,data->newNick,128);user->name[127]=0;
  TableEnter(channel->users,user);
  if(ciWasJoinCallbackCalled(data->chat,channel->name)) {
   if(channel->callbacks.userChangedNick) {
    params.channel=channel->name;params.oldNick=(char *)data->oldNick;params.newNick=(char *)data->newNick;
    ciAddCallback_(data->chat,8,channel->callbacks.userChangedNick,&params,channel->callbacks.param,0,channel->name,sizeof(params));
   }
  }
 }
}
void ciUserChangedNick(CHAT chat,const char *oldNick,const char *newNick) {
 ciUserChangedNickData data;
 ciConnection *connection=(ciConnection *)chat;
 data.chat=chat;data.oldNick=oldNick;data.newNick=newNick;
 TableMap(connection->channelTable,ciUserChangeNickMap,&data);
}
