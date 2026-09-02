// Release path: drop from a tracker, clear the holder slot, then tail-release.

class BfmeObj4310;

class BfmeTracker4310
{
public:
	void bfmeDrop(BfmeObj4310 *obj);
};

class BfmeHolder4310
{
public:
	char m_bfmePad[0x126c];
	BfmeObj4310 *m_bfmeCurrent;				// +0x126c
};

extern BfmeTracker4310 *g_bfmeTracker4310;			// retail 0x013377F8
extern BfmeHolder4310 *g_bfmeHolderBU;				// retail 0x013377D8

class BfmeNodeEA;
void __cdecl bfmeUnlink(BfmeNodeEA *node);			// retail 0x008BD280

class BfmeObj4310
{
public:
	virtual void destroy(void);
	virtual void release(void);
	void bfmeCleanup(int mode);				// retail 0x008C3F10

	void bfmeDrop(void);

	unsigned int m_bfmeFlags;				// +0x04
	int m_bfmeGap[22];					// +0x08
	unsigned int m_bfmeState;				// +0x60
};

// ?bfmeDrop@BfmeObj4310@@QAEXXZ
void BfmeObj4310::bfmeDrop(void)
{
	g_bfmeTracker4310->bfmeDrop(this);

	if (g_bfmeHolderBU->m_bfmeCurrent == this)
	{
		g_bfmeHolderBU->m_bfmeCurrent->release();
		g_bfmeHolderBU->m_bfmeCurrent = 0;
	}

	bfmeCleanup(1);

	unsigned packed = *(unsigned short *)((char *)this + 6) & 0xfff;

	if (packed > 1)
	{
		bfmeUnlink((BfmeNodeEA *)this);

		if ((m_bfmeState & 0xC0000) == 0)
			m_bfmeFlags &= 0xFFFF7FFF;
	}

	release();
}
