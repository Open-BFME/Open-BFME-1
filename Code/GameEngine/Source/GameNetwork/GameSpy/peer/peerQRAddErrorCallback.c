// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef int PEERBool;

typedef struct PEERConnection PEERConnection;
typedef PEERConnection *PEER;

typedef void (*qrAddErrorCallback)(PEER peer, int error,
	char *errorString, void *param);

struct PEERConnection
{
	unsigned char pad_0000[0x1808];
	qrAddErrorCallback qrAddError;
	unsigned char pad_180C[0x1814 - 0x180C];
	void *callbackParam;
	unsigned char pad_1818[0x18D4 - 0x1818];
	int autoMatchStatus;
	unsigned char pad_18D8[0x1EFC - 0x18D8];
	PEERBool autoMatchSBFailed;
	PEERBool autoMatchQRFailed;
};

PEERBool peerIsAutoMatching(PEER peer);
void piSetAutoMatchStatus(PEER peer, int status);

void piQRAddErrorCallback(int error, char *errorString, PEER peer)
{
	if (peerIsAutoMatching(peer))
	{
		int status;

		peer->autoMatchQRFailed = 1;
		if (peer->autoMatchSBFailed && peer->autoMatchStatus != 3)
			status = 0;
		else
			status = 1;

		piSetAutoMatchStatus(peer, status);
		return;
	}

	if (peer->qrAddError)
		peer->qrAddError(peer, error, errorString, peer->callbackParam);
}
