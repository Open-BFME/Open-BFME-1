// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// Upstream: GameSpy Peer SDK peerRooms.c, 2004 release.

typedef int PEERBool;
typedef int RoomType;

enum
{
	TitleRoom = 0,
	GroupRoom = 1,
	StagingRoom = 2,
	NumRooms = 3
};

typedef struct piConnection
{
	void *chat;
	char nick[0x40];
	PEERBool connecting;
	PEERBool connected;
	char unreconstructed_004C[0x80 - 0x4C];
	char room[NumRooms][0x101];
	char unreconstructed_0383;
	PEERBool enteringRoom[NumRooms];
	PEERBool inRoom[NumRooms];
	char name[NumRooms][0x200];
	int oldFlags[NumRooms];
	int groupID;
	char titleRoomChannel[0x104];
	PEERBool stayInTitleRoom;
	char unreconstructed_0AB4[0xB40 - 0xAB4];
	PEERBool hosting;
	PEERBool playing;
	int maxPlayers;
	PEERBool passwordedRoom;
	void *hostServer;
	PEERBool ready;
	char unreconstructed_0B58[0x1828 - 0xB58];
	PEERBool away;
} piConnection;

typedef piConnection *PEER;

__declspec(dllimport) int __cdecl strcasecmp(const char *left,
	const char *right);
__declspec(dllimport) char *__cdecl strzcpy(char *dest, const char *source,
	int len);
int piParseFlags(const char *flags);
void chatSetChannelKeysA(void *chat, const char *channel, const char *user,
	int num, const char **keys, const char **values);
void chatLeaveChannel(void *chat, const char *channel, const char *reason);
void piCancelJoinOperation(PEER peer, RoomType roomType);
void piClearRoomPlayers(PEER peer, RoomType roomType);
void piKeyCacheCleanse(PEER peer);
void piKeyCacheRefreshRoom(PEER peer, RoomType roomType);
void piSBFreeHostServer(PEER peer);
void piSetLocalFlags(PEER peer);
void piStopHosting(PEER peer, PEERBool stopReporting);
void piStopReporting(PEER peer);

PEERBool piRoomsInit(PEER peer)
{
	int roomType;

	for (roomType = 0; roomType < NumRooms; roomType++)
	{
		if (peer->stayInTitleRoom && roomType == TitleRoom)
			continue;

		peer->room[roomType][0] = '\0';
		peer->name[roomType][0] = '\0';
		peer->enteringRoom[roomType] = 0;
		peer->inRoom[roomType] = 0;
		peer->oldFlags[roomType] = 0;
	}
	peer->groupID = 0;
	peer->titleRoomChannel[0] = '\0';
	return 1;
}

void piFinishedEnteringRoom(PEER peer, RoomType roomType, const char *name)
{
	if (!name)
		name = "";

	peer->inRoom[roomType] = 1;
	peer->enteringRoom[roomType] = 0;
	strzcpy(peer->name[roomType], name, 0x200);
	peer->name[roomType][0x1FF] = '\0';
	piSetLocalFlags(peer);
	piKeyCacheRefreshRoom(peer, roomType);
}

void piLeaveRoom(PEER peer, RoomType roomType, const char *reason)
{
	if (!peer->enteringRoom[roomType] && !peer->inRoom[roomType])
		return;

	if (peer->enteringRoom[roomType])
		piCancelJoinOperation(peer, roomType);
	if (peer->connected)
		chatLeaveChannel(peer->chat, peer->room[roomType], reason);

	piClearRoomPlayers(peer, roomType);
	if (peer->inRoom[roomType])
		peer->inRoom[roomType] = 0;
	else
		peer->enteringRoom[roomType] = 0;

	peer->room[roomType][0] = '\0';
	peer->name[roomType][0] = '\0';
	peer->oldFlags[roomType] = 0;

	if (roomType == StagingRoom)
	{
		piStopHosting(peer, 0);
		if (!peer->playing)
			piStopReporting(peer);
		piSBFreeHostServer(peer);
		peer->ready = 0;
		peer->passwordedRoom = 0;
		piSetLocalFlags(peer);
	}
	else if (roomType == GroupRoom)
	{
		peer->groupID = 0;
	}

	piKeyCacheCleanse(peer);
}

void piRoomsCleanup(PEER peer)
{
	int roomType;

	for (roomType = 0; roomType < NumRooms; roomType++)
	{
		if (peer->stayInTitleRoom && roomType == TitleRoom)
			continue;

		if (peer->inRoom[roomType] || peer->enteringRoom[roomType])
			piLeaveRoom(peer, roomType, 0);
		peer->room[roomType][0] = '\0';
		peer->name[roomType][0] = '\0';
		peer->enteringRoom[roomType] = 0;
		peer->inRoom[roomType] = 0;
	}
	peer->titleRoomChannel[0] = '\0';
}

PEERBool piRoomToType(PEER peer, const char *room, RoomType *roomType)
{
	int i;

	for (i = 0; i < NumRooms; i++)
	{
		if (strcasecmp(room, peer->room[i]) == 0)
		{
			*roomType = (RoomType)i;
			return 1;
		}
	}
	return 0;
}

void piSetLocalFlags(PEER peer)
{
	char buffer[NumRooms][128];
	char *titleRoom;
	char *groupRoom;
	char *stagingRoom;
	const char *key = "b_flags";
	int nFlags;

	if (!peer->connected)
		return;

	if (peer->inRoom[0] || peer->enteringRoom[0])
		titleRoom = buffer[0];
	else
		titleRoom = 0;
	if (peer->inRoom[1] || peer->enteringRoom[1])
		groupRoom = buffer[1];
	else
		groupRoom = 0;
	if (peer->inRoom[2] || peer->enteringRoom[2])
		stagingRoom = buffer[2];
	else
		stagingRoom = 0;

	if (peer->inRoom[2])
	{
		if (titleRoom)
			*titleRoom++ = 's';
		if (groupRoom)
			*groupRoom++ = 's';
		*stagingRoom++ = 's';
		if (peer->ready)
			*stagingRoom++ = 'r';
		if (peer->hosting)
			*stagingRoom++ = 'h';
	}

	if (peer->playing)
	{
		if (titleRoom)
			*titleRoom++ = 'g';
		if (groupRoom)
			*groupRoom++ = 'g';
		if (stagingRoom)
			*stagingRoom++ = 'g';
	}

	if (peer->away)
	{
		if (titleRoom)
			*titleRoom++ = 'a';
		if (groupRoom)
			*groupRoom++ = 'a';
		if (stagingRoom)
			*stagingRoom++ = 'a';
	}

	if (titleRoom)
	{
		*titleRoom = '\0';
		titleRoom = buffer[0];
	}
	if (groupRoom)
	{
		*groupRoom = '\0';
		groupRoom = buffer[1];
	}
	if (stagingRoom)
	{
		*stagingRoom = '\0';
		stagingRoom = buffer[2];
	}

	if (titleRoom)
	{
		nFlags = piParseFlags(titleRoom);
		if (nFlags != peer->oldFlags[0])
		{
			chatSetChannelKeysA(peer->chat, peer->room[0], peer->nick,
				1, &key, (const char **)&titleRoom);
			peer->oldFlags[0] = nFlags;
		}
	}
	if (groupRoom)
	{
		nFlags = piParseFlags(groupRoom);
		if (nFlags != peer->oldFlags[1])
		{
			chatSetChannelKeysA(peer->chat, peer->room[1], peer->nick,
				1, &key, (const char **)&groupRoom);
			peer->oldFlags[1] = nFlags;
		}
	}
	if (stagingRoom)
	{
		nFlags = piParseFlags(stagingRoom);
		if (nFlags != peer->oldFlags[2])
		{
			chatSetChannelKeysA(peer->chat, peer->room[2], peer->nick,
				1, &key, (const char **)&stagingRoom);
			peer->oldFlags[2] = nFlags;
		}
	}
}
