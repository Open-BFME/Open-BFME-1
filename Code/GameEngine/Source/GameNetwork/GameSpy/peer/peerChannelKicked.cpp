// cl: /O2 /Ob2 /DNDEBUG /MD
// 0x0086B570, 100 bytes. Kicked callback slot witnessed by piSetChannelCallbacks.

typedef void *CHAT;
typedef void *PEER;
typedef int PEERBool;
typedef int RoomType;

enum
{
	TitleRoom,
	GroupRoom,
	StagingRoom
};

extern "C" PEERBool piRoomToType(PEER peer, const char *channel, RoomType *roomType);
extern "C" void piLeaveRoom(PEER peer, RoomType roomType, const char *reason);
extern "C" void piAddKickedCallback(
	PEER peer, RoomType roomType, const char *kicker, const char *reason);
extern "C" PEERBool peerIsAutoMatching(PEER peer);
extern "C" void piSetAutoMatchStatus(PEER peer, int status);

extern "C" void piChannelKickedA(
	CHAT chat, const char *channel, const char *kicker, const char *reason,
	void *param)
{
	RoomType roomType;
	PEER peer = (PEER)param;

	(void)chat;
	if (piRoomToType(peer, channel, &roomType))
	{
		piLeaveRoom(peer, roomType, 0);
		piAddKickedCallback(peer, roomType, kicker, reason);
		if (roomType == StagingRoom && peerIsAutoMatching(peer))
			piSetAutoMatchStatus(peer, 1);
	}
}
