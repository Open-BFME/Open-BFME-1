// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

typedef void *PEER;
typedef int PEERBool;

void piSendPlayerUTM(PEER peer, const char *nick, const char *command,
	const char *parameters, int authenticate);

void peerUTMPlayerA(PEER peer, const char *nick, const char *command,
	const char *parameters, PEERBool authenticate)
{
	piSendPlayerUTM(peer, nick, command, parameters, authenticate);
}
