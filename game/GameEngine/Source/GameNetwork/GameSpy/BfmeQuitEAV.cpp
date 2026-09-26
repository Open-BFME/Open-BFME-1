__declspec(dllimport) int __cdecl bfmeAtoi1027(char *text);

extern "C" void __cdecl peerSetQuietMode(void *peer, int quiet);
extern "C" void __cdecl peerStopListingGames(void *peer);

class BfmeMsgEAV
{
public:
	BfmeMsgEAV();
	~BfmeMsgEAV();

	int m_bfmeKindEAV;
	unsigned char m_bfmeHeadEAV[0xf0];
	int m_bfmeValueEAV;
	unsigned char m_bfmeTailEAV[0x238];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual void bfmeSlot00EAV();
	virtual void bfmeSlot01EAV();
	virtual void bfmeSlot02EAV();
	virtual void bfmeSlot03EAV();
	virtual void bfmeSlot04EAV();
	virtual void bfmeSlot05EAV();
	virtual void bfmeSlot06EAV();
	virtual void bfmeSlot07EAV();
	virtual void bfmePostEAV(BfmeMsgEAV *msg);
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

void __cdecl bfmeQuitEAV(void *peer, int unused, char *text)
{
	int value = bfmeAtoi1027(text);

	BfmeMsgEAV msg;

	msg.m_bfmeKindEAV = 0x12;
	msg.m_bfmeValueEAV = value;

	TheGameSpyPeerMessageQueue->bfmePostEAV(&msg);

	peerSetQuietMode(peer, 1);

	peerStopListingGames(peer);
}
