// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerAutoMatch.c */

typedef int PEERBool;

typedef struct PEERConnection
{
	unsigned char pad_0000[4];
	char nick[64];
	unsigned char pad_0044[0x390 - 0x44];
	PEERBool inRoom[3];
	unsigned char pad_039C[0xAB8 - 0x39C];
	int numPlayers[3];
	unsigned char pad_0AC4[0xB40 - 0xAC4];
	PEERBool queryReporting;
	unsigned char pad_0B44[0xB48 - 0xB44];
	int maxPlayers;
	unsigned char pad_0B4C[0x18D4 - 0xB4C];
	int autoMatchStatus;
	unsigned char pad_18D8[0x1EEC - 0x18D8];
	PEERBool autoMatchBrowsing;
	void *autoMatchOperation;
	PEERBool autoMatchReporting;
	char *autoMatchFilter;
	PEERBool autoMatchSBFailed;
	PEERBool autoMatchQRFailed;
} PEERConnection;

typedef PEERConnection *PEER;

PEERBool piCreateAutoMatchRoom(PEER peer);
void piAddAutoMatchStatusCallback(PEER peer);
void piSBStopListingAutoMatches(PEER peer);
void piStopAutoMatchReporting(PEER peer);
void piLeaveRoom(PEER peer, int roomType, const char *reason);
int piCountRoomOps(PEER peer, int roomType, const char *nick);
PEERBool piSBStartListingAutoMatches(PEER peer);
PEERBool piStartAutoMatchReporting(PEER peer);
extern __declspec(dllimport) void __cdecl gsifree(void *memory);
void piRemoveOperation(PEER peer, void *operation);

static __declspec(noinline) void piCleanAutoMatch(PEER peer)
{
	gsifree(peer->autoMatchFilter);
	piRemoveOperation(peer, peer->autoMatchOperation);
	peer->autoMatchOperation = 0;
}

void piSetAutoMatchStatus(PEER peer, int status)
{
	if (!peer->autoMatchOperation)
		return;

	if (status == 2 && !peer->inRoom[2])
	{
		if (!piCreateAutoMatchRoom(peer))
			piSetAutoMatchStatus(peer,
				peer->autoMatchSBFailed ? 0 : 1);
		return;
	}

	if (peer->autoMatchStatus != status)
	{
		peer->autoMatchStatus = status;
		piAddAutoMatchStatusCallback(peer);
	}

	switch (status)
	{
	case 0:
		piSBStopListingAutoMatches(peer);
		piStopAutoMatchReporting(peer);
		piLeaveRoom(peer, 2, "");
		piCleanAutoMatch(peer);
		break;

	case 1:
		piStopAutoMatchReporting(peer);
		piLeaveRoom(peer, 2, "");
		if (!peer->autoMatchBrowsing &&
			!piSBStartListingAutoMatches(peer))
		{
			piSetAutoMatchStatus(peer,
				peer->autoMatchQRFailed ? 0 : 2);
			return;
		}
		break;

	case 2:
		if (!peer->autoMatchBrowsing && !peer->autoMatchSBFailed)
			piSBStartListingAutoMatches(peer);
		if (!peer->autoMatchReporting &&
			!piStartAutoMatchReporting(peer))
		{
			piSetAutoMatchStatus(peer,
				peer->autoMatchSBFailed ? 0 : 1);
			return;
		}
		break;

	case 3:
		if (!peer->queryReporting)
			piStopAutoMatchReporting(peer);
		piSBStopListingAutoMatches(peer);
		if (peer->queryReporting && !peer->autoMatchReporting &&
			!piStartAutoMatchReporting(peer))
		{
			piSetAutoMatchStatus(peer, 1);
			return;
		}
		break;

	case 4:
		if (peer->queryReporting && !peer->autoMatchReporting)
			piStartAutoMatchReporting(peer);
		break;

	case 5:
		piSBStopListingAutoMatches(peer);
		piStopAutoMatchReporting(peer);
		piCleanAutoMatch(peer);
		break;
	}
}

typedef int PEERJoinResult;
typedef int RoomType;

void piJoinAutoMatchRoomCallback
(
	PEER peer,
	PEERBool success,
	PEERJoinResult result,
	RoomType roomType,
	void *param
)
{
	if (success && ((peer->numPlayers[2] <= 1) ||
		!piCountRoomOps(peer, 2, peer->nick)))
	{
		piLeaveRoom(peer, 2, "");
		success = 0;
	}

	if (success)
	{
		piSetAutoMatchStatus(peer, 3);

		if ((peer->autoMatchStatus == 3) &&
			(peer->numPlayers[2] >= peer->maxPlayers))
			piSetAutoMatchStatus(peer, 4);
	}

	if (!success && (peer->autoMatchStatus == 2))
		piSetAutoMatchStatus(peer, 2);

	(void)result;
	(void)roomType;
	(void)param;
}
