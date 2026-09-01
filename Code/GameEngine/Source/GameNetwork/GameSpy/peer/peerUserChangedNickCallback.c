// cl: /DNDEBUG /MD -Ireference/shims/gamespy

typedef void *CHAT;
typedef void *PEER;

typedef enum
{
	PEERFalse,
	PEERTrue
} PEERBool;

typedef enum
{
	TitleRoom,
	GroupRoom,
	StagingRoom,
	NumRooms
} RoomType;

PEERBool piRoomToType(PEER peer, const char *channel, RoomType *roomType);
void piPlayerChangedNick(PEER peer, const char *oldNick, const char *newNick);
void piAddPlayerChangedNickCallback(
	PEER peer, RoomType roomType, const char *oldNick, const char *newNick);

void piUserChangedNickCallback(
	CHAT chat, const char *channel, const char *oldNick, const char *newNick, void *param)
{
	RoomType roomType;

	(void)chat;
	if (piRoomToType((PEER)param, channel, &roomType)) {
		piPlayerChangedNick((PEER)param, oldNick, newNick);
		piAddPlayerChangedNickCallback((PEER)param, roomType, oldNick, newNick);
	}
}
