// cl: /O2 /Ob2 /DNDEBUG /MD
// 0x00857690, 33 bytes. API identity witnessed by matched PeerThreadClass::Thread_Function.

typedef void *PEER;

typedef struct piConnection
{
	unsigned char reservedBeforeTitle[0x60];
	char title[32];
} piConnection;

typedef void *SBServer;

extern "C" void piSBUpdateGame(PEER peer, SBServer server,
	int fullUpdate, int forceUpdateByMaster);

extern "C" void peerUpdateGame(PEER peer, SBServer server, int fullUpdate)
{
	piConnection *connection = (piConnection *)peer;
	if (connection->title[0])
		piSBUpdateGame(peer, server, fullUpdate, 0);
}
