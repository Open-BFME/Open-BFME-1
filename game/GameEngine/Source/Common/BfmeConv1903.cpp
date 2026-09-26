struct BfmeInfoAW
{
	unsigned char m_bfmeFlagAW;
	unsigned char m_bfmeLevelAW;
};

class BfmeAgentAW
{
public:
	virtual void bfmeSlot00AW();
	virtual void bfmeSlot01AW();
	virtual void bfmeSlot02AW();
	virtual void bfmeSlot03AW();
	virtual char bfmeSkipAW();
	virtual void bfmeSlot05AW();
	virtual void bfmeSlot06AW();
	virtual void bfmeSlot07AW();
	virtual void bfmeSlot08AW();
	virtual void bfmeSlot09AW();
	virtual void bfmeFillAW(BfmeInfoAW *info);
	virtual void bfmeSlot11AW();
	virtual void bfmeSlot12AW();
	virtual void bfmeSlot13AW();
	virtual void bfmeSlot14AW();
	virtual void bfmeSlot15AW();
	virtual void bfmeSlot16AW();
	virtual void bfmeSlot17AW();
	virtual void bfmeSlot18AW();
	virtual void bfmeSlot19AW();
	virtual void bfmeSlot20AW();
	virtual void bfmeSlot21AW();
	virtual void bfmeSlot22AW();
	virtual void bfmeSlot23AW();
	virtual void bfmeSlot24AW();
	virtual void bfmeSlot25AW();
	virtual void bfmeSlot26AW();
	virtual void bfmeLateAW(void *dst);
	virtual void bfmeSlot28AW();
	virtual void bfmeStoreAW(void *dst);
	virtual void bfmeSlot30AW();
	virtual void bfmeSlot31AW();
	virtual void bfmeSlot32AW();
	virtual void bfmeSlot33AW();
	virtual void bfmeSlot34AW();
	virtual void bfmeWriteAW(void *dst);
};

extern "C" void __cdecl bfmeXferAW(BfmeAgentAW *ag, void *dst);

class BfmeHostAW
{
public:
	void bfmeSaveAW(BfmeAgentAW *ag);
	void bfmeBeginAW(BfmeAgentAW *ag);

	unsigned char m_bfmeHeadAW[0xe8];
	unsigned char m_bfmeSlotAAW[4];
	unsigned char m_bfmeSlotBAW[4];
	unsigned char m_bfmeSlotCAW[4];
	unsigned char m_bfmeSlotDAW[4];
	unsigned char m_bfmeSlotEAW[4];
};

void BfmeHostAW::bfmeSaveAW(BfmeAgentAW *ag)
{
	bfmeBeginAW(ag);

	if (ag->bfmeSkipAW() != 0)
		return;

	BfmeInfoAW info;

	info.m_bfmeFlagAW = 1;
	info.m_bfmeLevelAW = 2;
	ag->bfmeFillAW(&info);

	bfmeXferAW(ag, m_bfmeSlotAAW);
	ag->bfmeWriteAW(m_bfmeSlotCAW);
	ag->bfmeStoreAW(m_bfmeSlotBAW);

	if (info.m_bfmeLevelAW >= 2)
	{
		ag->bfmeLateAW(m_bfmeSlotDAW);
		ag->bfmeLateAW(m_bfmeSlotEAW);
	}
}
