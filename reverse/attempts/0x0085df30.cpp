// ?d_0085df30@@YAXXZ
// partial score=0.9 date=2026-08-30
// cl: /DNDEBUG /MD
// Upstream identity: GameSpy Peer SDK piCallAutoMatchRateCallback.

typedef void *PEER;
typedef void *SBServer;
typedef int (*peerAutoMatchRateCallback)(PEER peer, SBServer server, void *param);

typedef struct piOperation
{
	char reserved[0x14];
	peerAutoMatchRateCallback callback2;
	void *callbackParam;
} piOperation;

typedef struct piConnection
{
	char reserved[0x1EF0];
	piOperation *autoMatchOperation;
} piConnection;

int piCallAutoMatchRateCallback(PEER peer, SBServer server)
{
	piConnection *connection = (piConnection *)peer;
	volatile piOperation *operation = connection->autoMatchOperation;

	if (operation && operation->callback2)
		return operation->callback2(peer, server, operation->callbackParam);

	return 0;
}
