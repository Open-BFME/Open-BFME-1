class BfmeSubFU;

class BfmeAudioFU
{
public:
	virtual void bfmeSlot00FU(void);
	virtual void bfmeSlot01FU(void);
	virtual void bfmeSlot02FU(void);
	virtual void bfmeSlot03FU(void);
	virtual void bfmeSlot04FU(void);
	virtual void bfmeSlot05FU(void);
	virtual void bfmeSlot06FU(void);
	virtual void bfmeSlot07FU(void);
	virtual void bfmeSlot08FU(void);
	virtual void bfmeSlot09FU(void);
	virtual void bfmeSlot10FU(void);
	virtual void bfmeSlot11FU(void);
	virtual void bfmeSlot12FU(void);
	virtual void bfmeSlot13FU(void);
	virtual void bfmeSlot14FU(void);
	virtual void bfmeSlot15FU(void);
	virtual void bfmeSlot16FU(void);
	virtual void *bfmeMakeFU(BfmeSubFU *sub);
};

extern BfmeAudioFU *g_bfmeAudioFU;

class BfmeSubFU
{
public:
	void bfmeFirstFU(void *value);
	void bfmeSecondFU(void *value);
	void bfmeThirdFU(void *value);

	unsigned char m_bfmeDataFU[4];
};

class BfmeOwnerFU
{
public:
	void bfmeGoFU(void *first, void *second);

	unsigned char m_bfmeHeadFU[0xe8];
	BfmeSubFU m_bfmeSubFU;
};

void BfmeOwnerFU::bfmeGoFU(void *first, void *second)
{
	BfmeSubFU *sub = &m_bfmeSubFU;

	sub->bfmeFirstFU(first);
	sub->bfmeSecondFU(second);
	sub->bfmeThirdFU(g_bfmeAudioFU->bfmeMakeFU(sub));
}
