// _peerCreateStagingRoomA
// cl: /DNDEBUG /MD
// GameSpy Peer SDK peerMainBlockingOperations.c body (gap at 0x008599D0),
// ported as a C++ ABI slice: forwards to the socket-taking variant with
// INVALID_SOCKET and port 0.

typedef void *PEER;

extern "C" void peerCreateStagingRoomWithSocketA(PEER peer, const char *name,
	int maxPlayers, const char *password, unsigned int socket,
	unsigned short port, void *callback, void *param, int blocking);

extern "C" void peerCreateStagingRoomA(PEER peer, const char *name,
	int maxPlayers, const char *password, void *callback, void *param,
	int blocking)
{
	peerCreateStagingRoomWithSocketA(peer, name, maxPlayers, password,
		(unsigned int)-1, 0, callback, param, blocking);
}
