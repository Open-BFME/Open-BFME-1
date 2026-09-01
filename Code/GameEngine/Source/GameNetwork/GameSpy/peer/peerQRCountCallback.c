// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef struct PEERConnection PEERConnection;
typedef PEERConnection *PEER;
typedef int (*qrCountCallback)(PEER peer, int type, void *param);

struct PEERConnection
{
	unsigned char pad_0000[0x398];
	int inStagingRoom;
	unsigned char pad_039C[0xAC0 - 0x39C];
	int stagingRoomPlayerCount;
	unsigned char pad_0AC4[0xB38 - 0xAC4];
	int reportingOptions;
	unsigned char pad_0B3C[0xB44 - 0xB3C];
	int playing;
	unsigned char pad_0B48[0x1804 - 0xB48];
	qrCountCallback qrCount;
	unsigned char pad_1808[0x1814 - 0x1808];
	void *callbackParam;
};

int piQRCountCallback(int type, PEER peer)
{
	if (type == 1)
	{
		if (peer->inStagingRoom &&
			(!peer->playing || (peer->reportingOptions & 4)))
			return peer->stagingRoomPlayerCount;
	}

	if (peer->qrCount)
		return peer->qrCount(peer, type, peer->callbackParam);

	return 0;
}
