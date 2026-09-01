// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef int PEERBool;
typedef void *SBServer;

typedef struct piOperation
{
	unsigned char pad_0000[0x30];
	unsigned short port;
} piOperation;

typedef struct PEERConnection
{
	unsigned char pad_0000[0x54];
	unsigned int publicIP;
	unsigned int privateIP;
	unsigned char pad_005C[0x384 - 0x5C];
	int enteringRoom[3];
	unsigned char pad_0390[0x18D4 - 0x390];
	int autoMatchStatus;
	unsigned char pad_18D8[0x1EF0 - 0x18D8];
	piOperation *autoMatchOperation;
	int autoMatchReporting;
} PEERConnection;

typedef PEERConnection *PEER;

unsigned int SBServerGetPublicInetAddress(SBServer server);
int SBServerHasPrivateAddress(SBServer server);
unsigned int SBServerGetPrivateInetAddress(SBServer server);
unsigned short SBServerGetPrivateQueryPort(SBServer server);
unsigned short SBServerGetPublicQueryPort(SBServer server);
int SBServerHasFullKeys(SBServer server);
int SBServerGetIntValueA(SBServer server, const char *key, int defaultValue);
int piCallAutoMatchRateCallback(PEER peer, SBServer server);
void piStopAutoMatchReporting(PEER peer);
void piLeaveRoom(PEER peer, int roomType, const char *reason);
int piJoinAutoMatchRoom(PEER peer, SBServer server);
void piSetAutoMatchStatus(PEER peer, int status);

static __declspec(noinline) PEERBool piIsLocalServer(PEER peer, SBServer server)
{
	if (SBServerGetPublicInetAddress(server) != peer->publicIP)
		return 0;

	if (SBServerHasPrivateAddress(server))
	{
		if (SBServerGetPrivateInetAddress(server) != peer->privateIP)
			return 0;

		if (SBServerGetPrivateQueryPort(server) != peer->autoMatchOperation->port)
			return 0;
	}
	else if (SBServerGetPublicQueryPort(server) != peer->autoMatchOperation->port)
	{
		return 0;
	}

	return 1;
}

static __declspec(noinline) int piSBAutoMatchGetServerRating(PEER peer, SBServer server)
{
	if (peer->autoMatchReporting && piIsLocalServer(peer, server))
		return 0;

	if (!SBServerHasFullKeys(server))
		return 0;

	if (SBServerGetIntValueA(server, "numplayers", 0) >=
		SBServerGetIntValueA(server, "maxplayers", 0))
		return 0;

	return piCallAutoMatchRateCallback(peer, server);
}

void piSBAutoMatchCheckUpdatedServer(PEER peer, SBServer server)
{
	int rating;

	if (peer->autoMatchStatus != 2)
		return;
	if (peer->enteringRoom[2])
		return;

	rating = piSBAutoMatchGetServerRating(peer, server);
	if (rating <= 0)
		return;

	piStopAutoMatchReporting(peer);
	piLeaveRoom(peer, 2, "");
	if (!piJoinAutoMatchRoom(peer, server))
		piSetAutoMatchStatus(peer, 0);
}
