// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef int PEERBool;

typedef struct SBServerRecord
{
	unsigned int publicip;
	unsigned short publicport;
	unsigned int privateip;
	unsigned short privateport;
	unsigned int icmpip;
	unsigned char state;
	unsigned char flags;
} *SBServer;

typedef struct PEERConnection
{
	unsigned char pad_0000[0x0BA0];
	int sbInitialized;
	unsigned char gameList[0x0B98];
	unsigned char gameEngine[1];
} PEERConnection;

typedef PEERConnection *PEER;

void SBQueryEngineRemoveServerFromFIFOs(void *engine, SBServer server);
void SBGetServerRulesFromMaster(
	void *serverList,
	unsigned int publicip,
	unsigned short publicport);
void SBQueryEngineUpdateServer(
	void *engine,
	SBServer server,
	int viaMaster,
	int queryType);

void piSBUpdateGame(
	PEER peer,
	SBServer server,
	PEERBool fullUpdate,
	PEERBool forceUpdateByMaster,
	PEERBool icmpEcho)
{
	(void)icmpEcho;

	if (!peer->sbInitialized)
		return;

	if (forceUpdateByMaster)
	{
		if (server->flags & 1)
			SBQueryEngineRemoveServerFromFIFOs(&peer->gameEngine, server);

		SBGetServerRulesFromMaster(
			&peer->gameList,
			server->publicip,
			server->publicport);
		return;
	}

	if (server->flags & 1)
	{
		SBQueryEngineRemoveServerFromFIFOs(&peer->gameEngine, server);
		SBQueryEngineUpdateServer(
			&peer->gameEngine,
			server,
			1,
			fullUpdate != 0);
		return;
	}

	SBGetServerRulesFromMaster(
		&peer->gameList,
		server->publicip,
		server->publicport);
}
