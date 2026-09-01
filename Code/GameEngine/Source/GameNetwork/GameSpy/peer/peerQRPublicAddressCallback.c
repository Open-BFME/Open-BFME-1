// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef struct PEERConnection PEERConnection;
typedef PEERConnection *PEER;

typedef void (*qrPublicAddressCallback)(PEER peer, unsigned int ip,
	unsigned short port, void *param);

struct PEERConnection
{
	unsigned char pad_0000[0x1810];
	qrPublicAddressCallback qrPublicAddress;
	void *callbackParam;
};

void piQRPublicAddressCallback(unsigned int ip, unsigned short port, PEER peer)
{
	if (peer->qrPublicAddress)
		peer->qrPublicAddress(peer, ip, port, peer->callbackParam);
}
