// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// Upstream: GameSpy Peer SDK peerRooms.c, 2004 release.

typedef int PEERBool;
typedef int RoomType;

enum
{
	TitleRoom = 0,
	NumRooms = 3
};

typedef struct piConnection
{
	char unreconstructed_0000[0x80];
	char room[NumRooms][0x101];
	char unreconstructed_0383;
	PEERBool enteringRoom[NumRooms];
	PEERBool inRoom[NumRooms];
	char name[NumRooms][0x200];
	int oldFlags[NumRooms];
	int groupID;
	char titleRoomChannel[0x104];
	PEERBool stayInTitleRoom;
} piConnection;

typedef piConnection *PEER;

__declspec(dllimport) int __cdecl strcasecmp(const char *left,
	const char *right);

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
