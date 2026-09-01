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
	unsigned char pad_005C[0x1EF0 - 0x5C];
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
int SBServerGetIntValue(SBServer server, const char *key, int defaultValue);
int piCallAutoMatchRateCallback(PEER peer, SBServer server);

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

int piSBAutoMatchGetServerRating(PEER peer, SBServer server)
{
	if (peer->autoMatchReporting && piIsLocalServer(peer, server))
		return 0;

	if (!SBServerHasFullKeys(server))
		return 0;

	if (SBServerGetIntValue(server, "numplayers", 0) >=
		SBServerGetIntValue(server, "maxplayers", 0))
		return 0;

	return piCallAutoMatchRateCallback(peer, server);
}
