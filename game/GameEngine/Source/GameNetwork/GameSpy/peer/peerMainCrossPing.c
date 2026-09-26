// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

typedef void *PEER;
typedef int PEERBool;

PEERBool piGetXping(PEER peer, const char *nick1, const char *nick2,
	int *ping);

PEERBool peerGetPlayersCrossPingA(PEER peer, const char *nick1,
	const char *nick2, int *crossPing)
{
	return piGetXping(peer, nick1, nick2, crossPing);
}
