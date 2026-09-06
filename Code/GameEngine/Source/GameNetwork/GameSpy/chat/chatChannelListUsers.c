// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK 2007 channel user-list enumeration algorithm, BFME 2004 ABI.
   Matched chatEnumUsersA names ciChannelListUsers and its six-argument callback. */
#include <string.h>
#include <stdlib.h>
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
typedef struct CHATChannelMode {
 int InviteOnly,Private,Secret,Moderated,NoExternalMessages,OnlyOpsChangeTopic,Limit; char *Ops;
} CHATChannelMode;
typedef struct ciChatChannel {
 char name[257]; chatChannelCallbacks callbacks; void *users;
 CHATChannelMode mode;int gotMode;char *password;int joinCallbackCalled;char topic[128];
} ciChatChannel;
typedef struct ciConnection {
 unsigned char beforeChannelTable[0x80c]; void *channelTable;
} ciConnection;
void *TableLookup(void *,const void *);
void TableEnter(void *,const void *);
static ciChatChannel *ciGetChannel(ciConnection *connection,const char *channel) {
 ciChatChannel chatChannel;
 strncpy(chatChannel.name,channel,257);chatChannel.name[256]=0;
 return (ciChatChannel *)TableLookup(connection->channelTable,&chatChannel);
}
typedef struct ciChannelListUsersData {CHAT chat;int numUsers;char **users;int *modes;} ciChannelListUsersData;
typedef void (*ciChannelListUsersCallback)(CHAT,const char *,int,const char **,int *,void *);
void TableMap(void *,void (*)(void *,void *),void *);
static void ciChannelListUsersMap(void *elem,void *clientData) {
 ciChatUser *user=(ciChatUser *)elem;
 ciChannelListUsersData *data=(ciChannelListUsersData *)clientData;
 void *tempPtr;
 tempPtr=realloc(data->users,sizeof(char *)*(data->numUsers+1));
 if(!tempPtr)return;
 data->users=(char **)tempPtr;
 tempPtr=realloc(data->modes,sizeof(int)*(data->numUsers+1));
 if(!tempPtr)return;
 data->modes=(int *)tempPtr;
 data->users[data->numUsers]=user->name;
 data->modes[data->numUsers]=user->mode;
 data->numUsers++;
}
void ciChannelListUsers(CHAT chat,const char *channel,ciChannelListUsersCallback callback,void *param) {
 ciChatChannel *chatChannel;
 ciChannelListUsersData data;
 ciConnection *connection=(ciConnection *)chat;
 chatChannel=ciGetChannel(connection,channel);
 if(!chatChannel)return;
 data.chat=chat;data.numUsers=0;data.users=0;data.modes=0;
 TableMap(chatChannel->users,ciChannelListUsersMap,&data);
 callback(chat,channel,data.numUsers,(const char **)data.users,data.modes,param);
 free(data.users);free(data.modes);
}
