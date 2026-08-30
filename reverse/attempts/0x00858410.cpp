// ?d_00858410@@YAXXZ
// partial score=0.64 date=2026-08-30
// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release, piDisconnect.

typedef void *PEER;
typedef int PEERBool;

typedef struct piConnection
{
	char reserved[0xAB0];
	PEERBool stayInTitleRoom;
	char reserved2[0x1824 - 0xAB4];
	int callbackDepth;
	char reserved3[0x1F04 - 0x1828];
	PEERBool disconnect;
} piConnection;

void bfmePiDisconnectCleanupFromEsi(void);
void bfmePiThinkFromEsi(int ID);

void piDisconnect(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (connection->callbackDepth > 0) {
		connection->disconnect = 1;
		return;
	}

	connection->stayInTitleRoom = 0;
	bfmePiDisconnectCleanupFromEsi();
	bfmePiThinkFromEsi(-1);
}
