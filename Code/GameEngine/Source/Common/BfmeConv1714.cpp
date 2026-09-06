class BfmeAudioGG
{
public:
	virtual void bfmeSlot00GG(void);
	virtual void bfmeSlot01GG(void);
	virtual void bfmeSlot02GG(void);
	virtual void bfmeSlot03GG(void);
	virtual void bfmeSlot04GG(void);
	virtual void bfmeSlot05GG(void);
	virtual void bfmeSlot06GG(void);
	virtual void bfmeSlot07GG(void);
	virtual void bfmeSlot08GG(void);
	virtual void bfmeSlot09GG(void);
	virtual void bfmeSlot10GG(void);
	virtual void bfmeSlot11GG(void);
	virtual void bfmeSlot12GG(void);
	virtual void bfmeSlot13GG(void);
	virtual void bfmeSlot14GG(void);
	virtual void bfmeSlot15GG(void);
	virtual void bfmeSlot16GG(void);
	virtual void bfmeSlot17GG(void);
	virtual void bfmeSlot18GG(void);
	virtual void bfmeNotifyGG(int value);
};

extern BfmeAudioGG *g_bfmeAudioGG;

class BfmeOwnerGG
{
public:
	unsigned char m_bfmeHeadGG[0x10];
	char m_bfmeFlagGG;
};

class BfmePrimaryGG
{
public:
	void bfmeApplyGG(void *target, int limit);
};

class BfmeSecondGG
{
public:
	void bfmeGoGG(int unused);

	unsigned char m_bfmeHeadGG[4];
	int m_bfmeValueGG;
};

void BfmeSecondGG::bfmeGoGG(int unused)
{
	char *base = (char *)this;

	if ((*(BfmeOwnerGG **)(base - 0x24))->m_bfmeFlagGG == 0)
		return;

	if (g_bfmeAudioGG != 0)
	{
		g_bfmeAudioGG->bfmeNotifyGG(m_bfmeValueGG);
		m_bfmeValueGG = 1;
	}

	((BfmePrimaryGG *)(base - 0x28))->bfmeApplyGG(*(void **)(base - 0x20), 0x3fffffff);
}
