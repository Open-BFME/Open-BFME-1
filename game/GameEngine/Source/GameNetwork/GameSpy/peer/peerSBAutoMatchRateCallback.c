// GameSpy Peer SDK -- peerSB.c

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
	{
		piOperation *callOperation = (piOperation *)operation;
		return callOperation->callback2(peer, server, operation->callbackParam);
	}

	return 0;
}
