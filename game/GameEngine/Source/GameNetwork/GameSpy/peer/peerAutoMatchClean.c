// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerAutoMatch.c */

typedef struct PEERConnection
{
	unsigned char pad_0000[0x1EF0];
	void *autoMatchOperation;
	unsigned char pad_1EF4[4];
	char *autoMatchFilter;
} PEERConnection;

typedef PEERConnection *PEER;

extern __declspec(dllimport) void __cdecl gsifree(void *memory);
void piRemoveOperation(PEER peer, void *operation);

static __declspec(noinline) void piCleanAutoMatch(PEER peer)
{
	gsifree(peer->autoMatchFilter);
	piRemoveOperation(peer, peer->autoMatchOperation);
	peer->autoMatchOperation = 0;
}

void piCleanAutoMatchCaller(PEER peer)
{
	piCleanAutoMatch(peer);
}
