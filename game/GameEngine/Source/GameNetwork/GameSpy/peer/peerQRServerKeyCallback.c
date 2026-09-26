// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef struct PEERConnection PEERConnection;
typedef PEERConnection *PEER;
typedef void *qr2_buffer_t;

typedef void (*qrServerKeyCallback)(PEER peer, int key,
	qr2_buffer_t buffer, void *param);

struct PEERConnection
{
	unsigned char pad_0000[0x398];
	int inStagingRoom;
	unsigned char pad_039C[0x79C - 0x39C];
	char stagingRoomName[0x200];
	unsigned char pad_099C[0xAC0 - 0x99C];
	int stagingRoomPlayerCount;
	unsigned char pad_0AC4[0xB38 - 0xAC4];
	int reportingOptions;
	int reportingGroupID;
	unsigned char pad_0B40[0xB44 - 0xB40];
	int playing;
	int maxPlayers;
	int passwordedRoom;
	unsigned char pad_0B50[0x17F4 - 0xB50];
	qrServerKeyCallback qrServerKey;
	unsigned char pad_17F8[0x1814 - 0x17F8];
	void *callbackParam;
};

void qr2_buffer_addA(qr2_buffer_t buffer, const char *value);
void qr2_buffer_add_int(qr2_buffer_t buffer, int value);

void piQRServerKeyCallback(int key, qr2_buffer_t buffer, PEER peer)
{
	if (peer->inStagingRoom &&
		(!peer->playing || (peer->reportingOptions & 2)))
	{
		switch (key)
		{
		case 1:
			qr2_buffer_addA(buffer, peer->stagingRoomName);
			return;
		case 8:
			qr2_buffer_add_int(buffer, peer->stagingRoomPlayerCount);
			return;
		case 10:
			if (!peer->maxPlayers)
				break;
			qr2_buffer_add_int(buffer, peer->maxPlayers);
			return;
		case 11:
			if (peer->playing)
				break;
			qr2_buffer_addA(buffer, "openstaging");
			return;
		case 19:
			qr2_buffer_add_int(buffer, peer->passwordedRoom ? 1 : 0);
			return;
		}
	}

	if (key == 20)
	{
		qr2_buffer_add_int(buffer, peer->reportingGroupID);
		return;
	}

	if (peer->qrServerKey)
		peer->qrServerKey(peer, key, buffer, peer->callbackParam);
}
