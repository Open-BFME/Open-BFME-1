// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK 2007 cached user-information update algorithm, BFME 2004 ABI.
   Retail WHO reply handler calls ciSetUserBasicInfo; TableMap proves its callback. */
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
typedef struct ciSetUserBasicInfoData {ciChatUser *chatUser;char *user,*address;} ciSetUserBasicInfoData;
void *TableLookup(void *,const void *);
void TableMap(void *,void (*)(void *,void *),void *);
static void ciSetUserBasicInfoMap(void *elem,void *clientData) {
 ciChatChannel *channel=(ciChatChannel *)elem;
 ciSetUserBasicInfoData *data=(ciSetUserBasicInfoData *)clientData;
 ciChatUser *user=(ciChatUser *)TableLookup(channel->users,data->chatUser);
 if(user) {
  strncpy(user->user,data->user,24);user->user[23]=0;
  strncpy(user->address,data->address,64);user->address[63]=0;
  user->gotUserAndAddress=1;
 }
}
void ciSetUserBasicInfo(CHAT chat,const char *nick,const char *user,const char *address) {
 ciChatUser chatUser;
 ciSetUserBasicInfoData data;
 ciConnection *connection=(ciConnection *)chat;
 strncpy(chatUser.name,nick,128);chatUser.name[127]=0;
 data.chatUser=&chatUser;data.user=(char *)user;data.address=(char *)address;
 TableMap(connection->channelTable,ciSetUserBasicInfoMap,&data);
}
