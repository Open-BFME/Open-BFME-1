// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef struct qr2_implementation *qr2_t;

typedef struct PEERConnection
{
	unsigned char pad_0000[0xAF0];
	qr2_t queryReporting;
	unsigned char pad_0AF4[0x1EF4 - 0xAF4];
	qr2_t autoMatchReporting;
} PEERConnection;

typedef PEERConnection *PEER;

void qr2_think(qr2_t qrec);

void piQRThink(PEER peer)
{
	if (peer->queryReporting)
		qr2_think(peer->queryReporting);
	if (peer->autoMatchReporting)
		qr2_think(peer->autoMatchReporting);
}
