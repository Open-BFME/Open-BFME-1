// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// Upstream: GameSpy Peer SDK peerPlayers.c, 2004 release.

#include <string.h>

typedef void *PEER;
typedef int PEERBool;
typedef int RoomType;

enum
{
	StagingRoom = 2,
	PEER_FLAG_STAGING = 0x01,
	PEER_FLAG_READY = 0x02,
	PEER_FLAG_PLAYING = 0x04,
	PEER_FLAG_AWAY = 0x08,
	PEER_FLAG_HOST = 0x10,
	PEER_FLAG_OP = 0x20,
	PEER_FLAG_VOICE = 0x40
};

typedef struct piPlayer
{
	char nick[0x40];
	PEERBool inRoom[3];
	char unreconstructed_4C[0x10];
	int flags[3];
} piPlayer;

piPlayer *piGetPlayer(PEER peer, const char *nick);
void piAddReadyChangedCallback(PEER peer, const char *nick, PEERBool ready);
void piAddPlayerFlagsChangedCallback(PEER peer, RoomType roomType,
	const char *nick, int oldFlags, int newFlags);

static void piSetNewPlayerFlags(PEER peer, const char *nick,
	RoomType roomType, int flags)
{
	piPlayer *player;
	int oldFlags;

	if (!nick)
		return;

	player = piGetPlayer(peer, nick);
	if (!player || !player->inRoom[roomType])
		return;

	oldFlags = player->flags[roomType];
	if (flags == oldFlags)
		return;

	player->flags[roomType] = flags;
	if ((roomType == StagingRoom)
		&& ((oldFlags & PEER_FLAG_READY) != (flags & PEER_FLAG_READY)))
	{
		piAddReadyChangedCallback(peer, player->nick,
			(PEERBool)((player->flags[roomType] & PEER_FLAG_READY) != 0));
	}

	piAddPlayerFlagsChangedCallback(peer, roomType, nick, oldFlags, flags);
}

int piParseFlags(const char *flags)
{
	int nFlags = 0;

	if (strchr(flags, 's'))
		nFlags |= PEER_FLAG_STAGING;
	if (strchr(flags, 'r'))
		nFlags |= PEER_FLAG_READY;
	if (strchr(flags, 'g'))
		nFlags |= PEER_FLAG_PLAYING;
	if (strchr(flags, 'a'))
		nFlags |= PEER_FLAG_AWAY;
	if (strchr(flags, 'h'))
		nFlags |= PEER_FLAG_HOST;

	return nFlags;
}

void piSetPlayerRoomFlags(PEER peer, const char *nick,
	RoomType roomType, const char *flags)
{
	piPlayer *player;
	int nFlags;

	if (!nick)
		return;

	player = piGetPlayer(peer, nick);
	if (!player || !player->inRoom[roomType])
		return;

	nFlags = player->flags[roomType] & (PEER_FLAG_OP | PEER_FLAG_VOICE);
	nFlags |= piParseFlags(flags);
	piSetNewPlayerFlags(peer, nick, roomType, nFlags);
}
