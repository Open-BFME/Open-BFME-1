// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef struct PEERConnection
{
	unsigned char pad_0000[0x0BA0];
	int sbInitialized;
	unsigned char gameList[1];
} PEERConnection;

typedef PEERConnection *PEER;

unsigned short __stdcall htons(unsigned short port);
void SBSendNatNegotiateCookieToServer(
	void *serverList,
	unsigned int ip,
	unsigned short port,
	int cookie);

void piSendNatNegotiateCookie(
	PEER peer,
	unsigned int ip,
	unsigned short port,
	int cookie)
{
	if (!peer->sbInitialized)
		return;

	SBSendNatNegotiateCookieToServer(
		&peer->gameList,
		ip,
		htons(port),
		cookie);
}
