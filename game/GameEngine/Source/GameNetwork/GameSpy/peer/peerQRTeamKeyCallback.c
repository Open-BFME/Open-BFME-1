// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef struct PEERConnection PEERConnection;
typedef PEERConnection *PEER;
typedef void *qr2_buffer_t;

typedef void (*qrTeamKeyCallback)(PEER peer, int key, int index,
	qr2_buffer_t buffer, void *param);

struct PEERConnection
{
	unsigned char pad_0000[0x17FC];
	qrTeamKeyCallback qrTeamKey;
	unsigned char pad_1800[0x1814 - 0x1800];
	void *callbackParam;
};

void piQRTeamKeyCallback(int key, int index, qr2_buffer_t buffer, PEER peer)
{
	if (peer->qrTeamKey)
		peer->qrTeamKey(peer, key, index, buffer, peer->callbackParam);
}
