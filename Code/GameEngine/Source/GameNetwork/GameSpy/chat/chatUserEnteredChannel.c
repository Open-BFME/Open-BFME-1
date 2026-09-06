// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK 2007 channel user-entry algorithm, BFME 2004 ABI.
   Retail JOIN handler calls ciUserEnteredChannel with six arguments. */
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
void ciUserEnteredChannel(CHAT chat,const char *name,const char *channel,int mode,const char *user,const char *address) {
 ciChatUser chatUser;
 ciChatChannel *chatChannel;
 ciConnection *connection=(ciConnection *)chat;
 chatChannel=ciGetChannel(connection,channel);
 if(!chatChannel)return;
 memset(&chatUser,0,sizeof(chatUser));
 strncpy(chatUser.name,name,128);chatUser.name[127]=0;
 if(user && address) {
  strncpy(chatUser.user,user,24);chatUser.user[23]=0;
  strncpy(chatUser.address,address,64);chatUser.address[63]=0;
  chatUser.gotUserAndAddress=1;
 } else chatUser.gotUserAndAddress=0;
 chatUser.mode=mode;
 TableEnter(chatChannel->users,&chatUser);
}
