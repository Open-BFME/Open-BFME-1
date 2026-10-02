// The constructor/destructor ILTs at 0x0002E38E/0x0001658B route to
// PSRequest's matched bodies at 0x0065AB40/0x000A5490.
class PSRequest
{
public:
	PSRequest();
	~PSRequest();

	int m_bfmeKindEUG;
	unsigned char m_bfmeBodyEUG[0x20c];
};

// Retail's header names this type GameSpyPSMessageQueueInterface; no game
// header declares it, so the local stand-in carries that name to give the
// global below retail's exact mangling.
class GameSpyPSMessageQueueInterface
{
public:
	virtual void bfmeSlot0EUG();
	virtual void bfmeSlot1EUG();
	virtual void bfmeSlot2EUG();
	virtual void bfmeSlot3EUG();
	virtual void bfmeAddEUG(PSRequest *req);
};

extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

void bfmeRequestEUG()
{
	PSRequest req;

	req.m_bfmeKindEUG = 10;

	if (TheGameSpyPSMessageQueue != 0)
		TheGameSpyPSMessageQueue->bfmeAddEUG(&req);
}
