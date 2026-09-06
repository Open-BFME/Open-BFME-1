// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK 2007 quiet-mode channel user clearing algorithm, BFME 2004 ABI.
   ciClearAllUsers at872930 names the channel callback; TableMapSafe identifies its user callback. */
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
typedef struct ciClearAllUsersData {CHAT chat;ciChatChannel *channel;} ciClearAllUsersData;
typedef struct ciCallbackUserListUpdatedParams {char *channel;} ciCallbackUserListUpdatedParams;
int TableRemove(void *,const void *);
void TableMapSafe(void *,void (*)(void *,void *),void *);
void ciAddCallback_(CHAT,int,void *,void *,void *,int,const char *,int);
static void ciClearAllUsersUsersMap(void *elem,void *clientData) {
 ciClearAllUsersData *data=(ciClearAllUsersData *)clientData;
 ciChatUser *user=(ciChatUser *)elem;
 ciChatChannel *channel=data->channel;
 TableRemove(channel->users,user);
}
void ciClearAllUsersChannelMap(void *elem,void *clientData) {
 ciChatChannel *channel=(ciChatChannel *)elem;
 ciClearAllUsersData data;
 CHAT chat=(CHAT)clientData;
 data.chat=chat;data.channel=channel;
 TableMapSafe(channel->users,ciClearAllUsersUsersMap,&data);
 if(channel->callbacks.userListUpdated) {
  ciCallbackUserListUpdatedParams params;
  params.channel=channel->name;
  ciAddCallback_(chat,12,channel->callbacks.userListUpdated,&params,channel->callbacks.param,0,channel->name,sizeof(params));
 }
}
