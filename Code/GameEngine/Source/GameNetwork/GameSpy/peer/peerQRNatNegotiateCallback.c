// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef struct PEERConnection PEERConnection;
typedef PEERConnection *PEER;

typedef void (*qrNatNegotiateCallback)(PEER peer, int cookie, void *param);

struct PEERConnection
{
	unsigned char pad_0000[0x180C];
	qrNatNegotiateCallback qrNatNegotiate;
	unsigned char pad_1810[0x1814 - 0x1810];
	void *callbackParam;
};

void piQRNatNegotiateCallback(int cookie, PEER peer)
{
	if (peer->qrNatNegotiate)
		peer->qrNatNegotiate(peer, cookie, peer->callbackParam);
}
