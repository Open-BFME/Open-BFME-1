class BfmeReqEUG
{
public:
	BfmeReqEUG();
	~BfmeReqEUG();

	int m_bfmeKindEUG;
	unsigned char m_bfmeBodyEUG[0x20c];
};

class BfmeQueueEUG
{
public:
	virtual void bfmeSlot0EUG();
	virtual void bfmeSlot1EUG();
	virtual void bfmeSlot2EUG();
	virtual void bfmeSlot3EUG();
	virtual void bfmeAddEUG(BfmeReqEUG *req);
};

extern BfmeQueueEUG *g_bfmeQueueEUG;

void bfmeRequestEUG()
{
	BfmeReqEUG req;

	req.m_bfmeKindEUG = 10;

	if (g_bfmeQueueEUG != 0)
		g_bfmeQueueEUG->bfmeAddEUG(&req);
}
