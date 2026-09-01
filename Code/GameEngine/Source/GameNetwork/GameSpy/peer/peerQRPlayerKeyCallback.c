// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef struct PEERConnection PEERConnection;
typedef PEERConnection *PEER;
typedef void *qr2_buffer_t;

typedef struct piPlayer
{
	char nick[0x40];
	unsigned char pad_0040[0x80 - 0x40];
	int pingAverage;
} piPlayer;

typedef void (*qrPlayerKeyCallback)(PEER peer, int key, int index,
	qr2_buffer_t buffer, void *param);

struct PEERConnection
{
	unsigned char pad_0000[0x398];
	int inStagingRoom;
	unsigned char pad_039C[0xB38 - 0x39C];
	int reportingOptions;
	unsigned char pad_0B3C[0xB44 - 0xB3C];
	int playing;
	unsigned char pad_0B48[0x17F8 - 0xB48];
	qrPlayerKeyCallback qrPlayerKey;
	unsigned char pad_17FC[0x1814 - 0x17FC];
	void *callbackParam;
};

piPlayer *piFindPlayerByIndex(PEER peer, int roomType, int index);
void qr2_buffer_addA(qr2_buffer_t buffer, const char *value);
void qr2_buffer_add_int(qr2_buffer_t buffer, int value);

void piQRPlayerKeyCallback(int key, int index, qr2_buffer_t buffer, PEER peer)
{
	piPlayer *player;

	if (peer->inStagingRoom &&
		(!peer->playing || (peer->reportingOptions & 4)))
	{
		if (key == 21 || key == 24)
		{
			player = piFindPlayerByIndex(peer, 2, index);
			if (!player)
				qr2_buffer_addA(buffer, "");
			else if (key == 21)
				qr2_buffer_addA(buffer, player->nick);
			else if (key == 24)
				qr2_buffer_add_int(buffer, player->pingAverage);

			return;
		}
	}

	if (peer->qrPlayerKey)
		peer->qrPlayerKey(peer, key, index, buffer, peer->callbackParam);
}
