class BfmeThingAY;

struct BfmeInfoAY
{
	unsigned char m_bfmeFlagAY;
	unsigned char m_bfmeLevelAY;
};

class BfmeAgentAY
{
public:
	virtual void bfmeSlot00AY();
	virtual void bfmeSlot01AY();
	virtual void bfmeSlot02AY();
	virtual void bfmeSlot03AY();
	virtual char bfmeSkipAY();
	virtual void bfmeSlot05AY();
	virtual void bfmeSlot06AY();
	virtual void bfmeSlot07AY();
	virtual void bfmeSlot08AY();
	virtual void bfmeSlot09AY();
	virtual void bfmeFillAY(BfmeInfoAY *info);
	virtual void bfmeSlot11AY();
	virtual void bfmeLinkAY(BfmeThingAY *o);
	virtual void bfmeSlot13AY();
	virtual void bfmeSlot14AY();
	virtual void bfmeSlot15AY();
	virtual void bfmeSlot16AY();
	virtual void bfmeSlot17AY();
	virtual void bfmeSlot18AY();
	virtual void bfmeSlot19AY();
	virtual void bfmeSlot20AY();
	virtual void bfmeSlot21AY();
	virtual void bfmeSlot22AY();
	virtual void bfmeSlot23AY();
	virtual void bfmeSlot24AY();
	virtual void bfmeSlot25AY();
	virtual void bfmeSlot26AY();
	virtual void bfmeLateAY(void *dst);
	virtual void bfmeSlot28AY();
	virtual void bfmeSlot29AY();
	virtual void bfmeWordAY(void *dst);
	virtual void bfmeSlot31AY();
	virtual void bfmeSlot32AY();
	virtual void bfmeSlot33AY();
	virtual void bfmeSlot34AY();
	virtual void bfmeByteAY(unsigned char *dst);
};

extern "C" void __cdecl bfmeXferAY(BfmeAgentAY *ag, void *dst);

class BfmeHostAY
{
public:
	void bfmeSaveAY(BfmeAgentAY *ag);
	void bfmeBeginAY(BfmeAgentAY *ag);

	unsigned char m_bfmeHeadAY[0x50];
	unsigned char m_bfmeSlotAAY[4];
	unsigned char m_bfmeSlotBAY[4];
	unsigned char m_bfmeSlotCAY;
	unsigned char m_bfmeSlotDAY;
	unsigned char m_bfmeSlotEAY;
	unsigned char m_bfmeSlotFAY;
	unsigned char m_bfmeSlotGAY[4];
	BfmeThingAY *m_bfmeSlotHAY;
	unsigned char m_bfmeSlotIAY[4];
	unsigned char m_bfmeSlotJAY;
};

void BfmeHostAY::bfmeSaveAY(BfmeAgentAY *ag)
{
	BfmeInfoAY info;

	info.m_bfmeFlagAY = 1;
	info.m_bfmeLevelAY = 3;
	ag->bfmeFillAY(&info);

	bfmeBeginAY(ag);

	if (ag->bfmeSkipAY() != 0)
		return;

	ag->bfmeWordAY(m_bfmeSlotAAY);
	ag->bfmeByteAY(&m_bfmeSlotCAY);
	ag->bfmeByteAY(&m_bfmeSlotDAY);
	ag->bfmeByteAY(&m_bfmeSlotEAY);

	if (info.m_bfmeLevelAY > 1)
	{
		ag->bfmeWordAY(m_bfmeSlotBAY);
		bfmeXferAY(ag, m_bfmeSlotGAY);

		if (m_bfmeSlotHAY != 0)
			ag->bfmeLinkAY(m_bfmeSlotHAY);

		ag->bfmeLateAY(m_bfmeSlotIAY);
		ag->bfmeByteAY(&m_bfmeSlotJAY);
	}

	if (info.m_bfmeLevelAY > 2)
		ag->bfmeByteAY(&m_bfmeSlotFAY);
}
