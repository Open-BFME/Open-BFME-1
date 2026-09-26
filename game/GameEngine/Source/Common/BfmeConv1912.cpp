class BfmeAgentBH;

struct BfmeInfoBH
{
	unsigned char m_bfmeFlagBH;
	unsigned char m_bfmeLevelBH;
};

class BfmeAgentBH
{
public:
	virtual void bfmeSlot00BH();
	virtual char bfmeReadingBH();
	virtual void bfmeSlot02BH();
	virtual void bfmeSlot03BH();
	virtual char bfmeSkipBH();
	virtual void bfmeSlot05BH();
	virtual void bfmeSlot06BH();
	virtual void bfmeSlot07BH();
	virtual void bfmeSlot08BH();
	virtual void bfmeSlot09BH();
	virtual void bfmeFillBH(BfmeInfoBH *info);
	virtual void bfmeSlot11BH();
	virtual void bfmeSlot12BH();
	virtual void bfmeSlot13BH();
	virtual void bfmeSlot14BH();
	virtual void bfmeSlot15BH();
	virtual void bfmeSlot16BH();
	virtual void bfmeSlot17BH();
	virtual void bfmeSlot18BH();
	virtual void bfmeSlot19BH();
	virtual void bfmeSlot20BH();
	virtual void bfmeSlot21BH();
	virtual void bfmeSlot22BH();
	virtual void bfmeSlot23BH();
	virtual void bfmeMarkBH(void *dst);
	virtual void bfmeSlot25BH();
	virtual void bfmeSlot26BH();
	virtual void bfmeSlot27BH();
	virtual void bfmeSlot28BH();
	virtual void bfmeSlot29BH();
	virtual void bfmeSlot30BH();
	virtual void bfmeSlot31BH();
	virtual void bfmeSlot32BH();
	virtual void bfmeSlot33BH();
	virtual void bfmeSlot34BH();
	virtual void bfmeByteBH(unsigned char *dst);
};

class BfmeSubOneBH
{
public:
	void bfmeSaveBH(BfmeAgentBH *ag);

	unsigned char m_bfmePadBH[0x28];
};

class BfmeSubTwoBH
{
public:
	void bfmeSaveBH(BfmeAgentBH *ag);

	unsigned char m_bfmePadBH[0xc];
};

class BfmeHostBH
{
public:
	void bfmeSaveBH(BfmeAgentBH *ag);
	void bfmeBeginBH(BfmeAgentBH *ag);
	void bfmeOnBH();
	void bfmeOffBH();

	unsigned char m_bfmeHeadBH[0x24];
	unsigned char m_bfmeSlotABH[4];
	unsigned char m_bfmePadOneBH[8];
	BfmeSubOneBH m_bfmeSubOneBH;
	BfmeSubTwoBH m_bfmeSubTwoBH;
	unsigned char m_bfmeSlotDBH;
	unsigned char m_bfmeStateBH;
};

void BfmeHostBH::bfmeSaveBH(BfmeAgentBH *ag)
{
	bfmeBeginBH(ag);

	if (ag->bfmeSkipBH() != 0)
		return;

	BfmeInfoBH info;

	info.m_bfmeFlagBH = 1;
	info.m_bfmeLevelBH = 1;
	ag->bfmeFillBH(&info);

	ag->bfmeMarkBH(m_bfmeSlotABH);
	m_bfmeSubOneBH.bfmeSaveBH(ag);
	m_bfmeSubTwoBH.bfmeSaveBH(ag);
	ag->bfmeByteBH(&m_bfmeSlotDBH);

	if (ag->bfmeReadingBH() != 0)
	{
		unsigned char v;

		ag->bfmeByteBH(&v);

		if (v == m_bfmeStateBH)
			return;

		if (v != 0)
			bfmeOnBH();
		else
			bfmeOffBH();
	}
	else
		ag->bfmeByteBH(&m_bfmeStateBH);
}
