// cl: /O2 /Ob2 /DNDEBUG /MD
// 0x0086B5E0, 290 bytes. Callback identity witnessed by
// peerGlobalCallbacksSetChannel.c; connection/player layout shared with
// peerMainBlockingOperations.c and aligned retail field accesses.
typedef void *PEER;

typedef struct piConnection
{
	void *chat;
	char nick[64];
	int connecting;
	int connected;
	void *nickErrorCallback;
	unsigned int lastChatPing;
	unsigned int publicIP;
	unsigned int privateIP;
	int profileID;
	char title[32];
	char room[3][257];
	int enteringRoom[3];
	int inRoom[3];
	char names[3][512];
	int oldFlags[3];
	int groupID;
	char titleRoomChannel[257];
	char reservedTitleRoom[0xAB0 - 0xAAD];
	int stayInTitleRoom;
	void *players;
	int numPlayers[3];
	int alwaysRequestPlayerInfo;
	char reservedStay[0xAD0 - 0xAC8];
	int pingRoom[3];
	int xpingRoom[3];
	char reservedPingRooms[0xAF0 - 0xAE8];
	void *queryReporting;
	char qrSecretKey[0xB34 - 0xAF4];
	int natNegotiate;
	int reportingOptions;
	char reservedReportingOptions[0xB40 - 0xB3C];
	int hosting;
	int playing;
	int maxPlayers;
	int passwordedRoom;
	void *hostServer;
	int ready;
	char sbName[32];
	char sbSecretKey[32];
	int sbGameVersion;
	int sbMaxUpdates;
	char reservedReady[0x1784 - 0xBA0];
	void *gameListCallback;
	void *gameListParam;
	int initialGameList;
	char reservedGameList[0x1794 - 0x1790];
	int nextID;
	char reservedBeforeCallbacks[0x17A4 - 0x1798];
	void *disconnectedCallback;
	char callbackRest[0x70];
	char reservedCallbacks[0x1824 - 0x1818];
	int callbackDepth;
	int away;
	char awayReason[128];
	char reserved2[0x18D4 - 0x18AC];
	int autoMatchStatus;
	char reserved3[0x1EF8 - 0x18D8];
	char *autoMatchFilter;
	int autoMatchSBFailed;
	int autoMatchQRFailed;
	int disconnect;
	int shutdown;
} piConnection;

typedef struct piPlayer
{
	char nick[64];
	int inRoom[3];
	int local;
	unsigned int IP;
	int profileID;
	int gotIPAndProfileID;
	int flags[3];
	char reservedFlags[0x74 - 0x68];
	int waitingForPing;
	char reservedWaitingForPing[0x80 - 0x78];
	int pingAverage;
	char reservedPingAverage[0x98 - 0x84];
	int numPings;
	char reservedNumPings[0xA0 - 0x9C];
	int inPingRoom;
	char reservedInPingRoom[0xA8 - 0xA4];
	int mustPing;
	int pingOnce;
} piPlayer;


extern "C" {
int piRoomToType(PEER, const char *, int *);
piPlayer *piPlayerJoinedRoom(PEER, const char *, int, int);
int chatGetBasicUserInfoNoWaitA(void *, const char *, const char **, const char **);
int piDemangleUser(const char *, unsigned int *, int *);
void piSetPlayerIPAndProfileID(PEER, const char *, unsigned int, int);
void piKeyCacheRefreshPlayer(PEER, int, const char *);
void piAddPlayerJoinedCallback(PEER, int, const char *);
void peerMessagePlayerA(PEER, const char *, const char *, int);
int peerIsAutoMatching(PEER);
void piSetAutoMatchStatus(PEER, int);
}
extern "C" void piChannelUserJoinedA(void *chat, const char *channel,
 const char *nick, int mode, PEER peer)
{
 int roomType;
 piConnection *connection = (piConnection *)peer;
 if (!piRoomToType(peer, channel, &roomType)) return;
 piPlayer *player = piPlayerJoinedRoom(peer, nick, roomType, mode);
 if (!player) return;
 if (!player->gotIPAndProfileID) {
  const char *user;
  unsigned int IP;
  int profileID;
  if (chatGetBasicUserInfoNoWaitA(connection->chat, nick, &user, 0)
      && piDemangleUser(user, &IP, &profileID))
   piSetPlayerIPAndProfileID(peer, nick, IP, profileID);
 }
 piKeyCacheRefreshPlayer(peer, roomType, nick);
 piAddPlayerJoinedCallback(peer, roomType, nick);
 if (roomType == 2) {
  if (connection->ready)
   peerMessagePlayerA(peer, nick, "@@@NFO \\$flags$\\rX\\", 0);
  if (roomType == 2 && peerIsAutoMatching(peer)) {
   if (connection->autoMatchStatus == 2) piSetAutoMatchStatus(peer, 3);
   if (connection->autoMatchStatus == 3
       && connection->numPlayers[2] >= connection->maxPlayers)
    piSetAutoMatchStatus(peer, 4);
  }
 }
}
