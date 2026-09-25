// cl: /O2 /Ob2 /DNDEBUG /MD
// 0x0086B8D0, 121 bytes. newUserList callback slot in piSetChannelCallbacks.

typedef int RoomType;
typedef void *PEER;

extern "C" {
struct piPlayer;
int piRoomToType(PEER peer, const char *channel, RoomType *roomType);
void piClearRoomPlayers(PEER peer, RoomType roomType);
piPlayer *piPlayerJoinedRoom(PEER peer, const char *nick, RoomType roomType,
	int mode);
void piKeyCacheRefreshRoom(PEER peer, RoomType roomType);
void piAddNewPlayerListCallback(PEER peer, RoomType roomType);

void piChannelNewUserListA(void *chat, const char *channel, int num,
	const char **users, const int *modes, void *param)
{
	PEER peer = (PEER)param;
	RoomType roomType;
	int i;

	(void)chat;
	if (!piRoomToType(peer, channel, &roomType))
		return;

	piClearRoomPlayers(peer, roomType);
	for (i = 0; i < num; i++)
		piPlayerJoinedRoom(peer, users[i], roomType, modes[i]);

	piKeyCacheRefreshRoom(peer, roomType);
	piAddNewPlayerListCallback(peer, roomType);
}

}
