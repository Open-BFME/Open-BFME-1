struct BfmeInfoBA
{
	unsigned char m_bfmeFlagBA;
	unsigned char m_bfmeLevelBA;
};

class BfmeAgentBA
{
public:
	virtual void bfmeSlot00BA();
	virtual void bfmeSlot01BA();
	virtual void bfmeSlot02BA();
	virtual void bfmeSlot03BA();
	virtual void bfmeSlot04BA();
	virtual void bfmeSlot05BA();
	virtual void bfmeSlot06BA();
	virtual void bfmeSlot07BA();
	virtual void bfmeSlot08BA();
	virtual void bfmeSlot09BA();
	virtual void bfmeFillBA(BfmeInfoBA *info);
	virtual void bfmeSlot11BA();
	virtual void bfmeSlot12BA();
	virtual void bfmeSlot13BA();
	virtual void bfmeSlot14BA();
	virtual void bfmeSlot15BA();
	virtual void bfmeSlot16BA();
	virtual void bfmeSlot17BA();
	virtual void bfmeSlot18BA();
	virtual void bfmeSlot19BA();
	virtual void bfmeSlot20BA();
	virtual void bfmeSlot21BA();
	virtual void bfmeSlot22BA();
	virtual void bfmeSlot23BA();
	virtual void bfmeSlot24BA();
	virtual void bfmeSlot25BA();
	virtual void bfmeMarkBA(void *dst);
	virtual void bfmeLateBA(void *dst);
	virtual void bfmeSlot28BA();
	virtual void bfmeSlot29BA();
	virtual void bfmeWordBA(void *dst);
	virtual void bfmeSlot31BA();
	virtual void bfmeSlot32BA();
	virtual void bfmeSlot33BA();
	virtual void bfmeSlot34BA();
	virtual void bfmeByteBA(unsigned char *dst);
};

extern "C" void __cdecl bfmeXferOneBA(BfmeAgentBA *ag, void *dst);
extern "C" void __cdecl bfmeXferTwoBA(BfmeAgentBA *ag, void *dst);
extern "C" void __cdecl bfmeXferThreeBA(BfmeAgentBA *ag, void *dst);
extern "C" void __cdecl bfmeXferFourBA(BfmeAgentBA *ag, void *dst);

class BfmeHostBA
{
public:
	void bfmeSaveBA(BfmeAgentBA *ag);

	unsigned char m_bfmeHeadBA[0x18];
	unsigned char m_bfmeSlotABA[4];
	unsigned char m_bfmePadOneBA[0x14];
	unsigned char m_bfmeSlotBBA[4];
	unsigned char m_bfmeSlotCBA[0x10];
	unsigned char m_bfmeSlotDBA;
	unsigned char m_bfmePadTwoBA[0x2f];
	unsigned char m_bfmeSlotEBA[4];
	unsigned char m_bfmeSlotFBA;
	unsigned char m_bfmePadThreeBA[7];
	unsigned char m_bfmeSlotGBA;
	unsigned char m_bfmePadFourBA[0xf];
	unsigned char m_bfmeSlotHBA[4];
	unsigned char m_bfmeSlotIBA[4];
	unsigned char m_bfmePadFiveBA[8];
	unsigned char m_bfmeSlotJBA[4];
	unsigned char m_bfmeSlotKBA[4];
	unsigned char m_bfmeSlotLBA[4];
};

void BfmeHostBA::bfmeSaveBA(BfmeAgentBA *ag)
{
	BfmeInfoBA info;

	info.m_bfmeFlagBA = 1;
	info.m_bfmeLevelBA = 4;
	ag->bfmeFillBA(&info);

	ag->bfmeWordBA(m_bfmeSlotABA);
	ag->bfmeMarkBA(m_bfmeSlotBBA);
	bfmeXferOneBA(ag, m_bfmeSlotCBA);
	ag->bfmeByteBA(&m_bfmeSlotDBA);
	ag->bfmeWordBA(m_bfmeSlotEBA);
	ag->bfmeByteBA(&m_bfmeSlotFBA);
	ag->bfmeByteBA(&m_bfmeSlotGBA);
	bfmeXferTwoBA(ag, m_bfmeSlotHBA);

	if (info.m_bfmeLevelBA >= 2)
	{
		ag->bfmeWordBA(m_bfmeSlotJBA);
		bfmeXferThreeBA(ag, m_bfmeSlotIBA);
	}

	if (info.m_bfmeLevelBA >= 3)
		bfmeXferFourBA(ag, m_bfmeSlotLBA);

	if (info.m_bfmeLevelBA >= 4)
		ag->bfmeLateBA(m_bfmeSlotKBA);
}
