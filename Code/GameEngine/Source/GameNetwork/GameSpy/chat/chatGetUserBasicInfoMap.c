// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK 2007 cached user-information lookup algorithm, BFME 2004 ABI.
   Matched ciGetUserBasicInfoA supplies callback identity and context layout. */
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
typedef struct ciGetUserBasicInfoData {int found;ciChatUser *chatUser;char *user,*address;} ciGetUserBasicInfoData;
void *TableLookup(void *,const void *);
void ciGetUserBasicInfoMap(void *elem,void *clientData) {
 ciChatChannel *channel;
 ciChatUser *user;
 ciGetUserBasicInfoData *data=(ciGetUserBasicInfoData *)clientData;
 if(data->found && strcmp(data->address,"*")!=0)return;
 channel=(ciChatChannel *)elem;
 user=(ciChatUser *)TableLookup(channel->users,data->chatUser);
 if(user) {
  if(user->gotUserAndAddress) {
   data->found=1;data->user=user->user;data->address=user->address;
  }
 }
}
