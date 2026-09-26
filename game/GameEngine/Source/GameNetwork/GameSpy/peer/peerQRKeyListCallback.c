// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef int qr2_key_type;
typedef void *qr2_keybuffer_t;

typedef struct PEERConnection PEERConnection;
typedef PEERConnection *PEER;

typedef void (*qrKeyListCallback)(PEER peer, qr2_key_type type,
	qr2_keybuffer_t keyBuffer, void *param);

struct PEERConnection
{
	unsigned char pad_0000[0xB3C];
	int reportingGroupID;
	unsigned char pad_0B40[0xB48 - 0xB40];
	int maxPlayers;
	int passwordedRoom;
	unsigned char pad_0B50[0x1800 - 0xB50];
	qrKeyListCallback qrKeyList;
	unsigned char pad_1804[0x1814 - 0x1804];
	void *callbackParam;
	unsigned char pad_1818[0x1EF4 - 0x1818];
	void *autoMatchReporting;
};

void qr2_keybuffer_add(qr2_keybuffer_t keyBuffer, int key);

void piQRKeyListCallback(qr2_key_type type, qr2_keybuffer_t keyBuffer,
	PEER peer)
{
	switch (type)
	{
	case 0:
		if (!peer->autoMatchReporting)
		{
			qr2_keybuffer_add(keyBuffer, 1);
			qr2_keybuffer_add(keyBuffer, 11);
			if (peer->passwordedRoom)
				qr2_keybuffer_add(keyBuffer, 19);
			if (peer->reportingGroupID)
				qr2_keybuffer_add(keyBuffer, 20);
		}
		qr2_keybuffer_add(keyBuffer, 8);
		if (peer->maxPlayers)
			qr2_keybuffer_add(keyBuffer, 10);
		break;

	case 1:
		qr2_keybuffer_add(keyBuffer, 21);
		qr2_keybuffer_add(keyBuffer, 24);
		break;
	}

	if (peer->qrKeyList)
		peer->qrKeyList(peer, type, keyBuffer, peer->callbackParam);
}
