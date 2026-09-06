// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK 2007 channel enumeration algorithm, BFME 2004 layout.
   QUIT/KILL handlers provide the public caller identity and callback ABI. */
#include <string.h>
typedef void *CHAT;
typedef struct ciChatUser {
    char name[128];
    char user[24];
    char address[64];
    int gotUserAndAddress;
    int mode;
} ciChatUser;
typedef struct ciChatChannel {
    char name[257];
    void *callbacks[12];
    void *users;
} ciChatChannel;
typedef struct ciConnection {
    unsigned char beforeChannelTable[0x80c];
    void *channelTable;
} ciConnection;
typedef void (*ciUserEnumChannelsCallback)(CHAT,const char *,const char *,void *);
typedef struct ciUserEnumChannelsData {
    CHAT chat;
    ciChatUser *user;
    ciUserEnumChannelsCallback callback;
    void *param;
} ciUserEnumChannelsData;
void *TableLookup(void *,const void *);
void TableMap(void *,void (*)(void *,void *),void *);
static void ciUserEnumChannelsMap(void *elem,void *clientData) {
    ciChatChannel *channel=(ciChatChannel *)elem;
    ciUserEnumChannelsData *data=(ciUserEnumChannelsData *)clientData;
    ciChatUser *user=(ciChatUser *)TableLookup(channel->users,data->user);
    if(user) data->callback(data->chat,data->user->name,channel->name,data->param);
}
void ciUserEnumChannels(CHAT chat,const char *user,ciUserEnumChannelsCallback callback,void *param) {
    ciChatUser chatUser;
    ciUserEnumChannelsData data;
    ciConnection *connection=(ciConnection *)chat;
    strncpy(chatUser.name,user,128);
    chatUser.name[127]='\0';
    data.chat=chat;
    data.user=&chatUser;
    data.callback=callback;
    data.param=param;
    TableMap(connection->channelTable,ciUserEnumChannelsMap,&data);
}
