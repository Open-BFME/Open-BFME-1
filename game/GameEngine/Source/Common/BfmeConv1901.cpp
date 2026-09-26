struct BfmeInfoAU
{
	unsigned char m_bfmeFlagAU;
	unsigned char m_bfmeLevelAU;
};

class BfmeAgentAU
{
public:
	virtual void bfmeSlot00AU();
	virtual void bfmeSlot01AU();
	virtual void bfmeSlot02AU();
	virtual void bfmeSlot03AU();
	virtual char bfmeSkipAU();
	virtual void bfmeSlot05AU();
	virtual void bfmeSlot06AU();
	virtual void bfmeSlot07AU();
	virtual void bfmeSlot08AU();
	virtual void bfmeSlot09AU();
	virtual void bfmeFillAU(BfmeInfoAU *info);
	virtual void bfmeSlot11AU();
	virtual void bfmeSlot12AU();
	virtual void bfmeSlot13AU();
	virtual void bfmeSlot14AU();
	virtual void bfmeSlot15AU();
	virtual void bfmeSlot16AU();
	virtual void bfmeSlot17AU();
	virtual void bfmeSlot18AU();
	virtual void bfmeSlot19AU();
	virtual void bfmeSlot20AU();
	virtual void bfmeSlot21AU();
	virtual void bfmeSlot22AU();
	virtual void bfmeSlot23AU();
	virtual void bfmeWriteAU(void *dst);
	virtual void bfmeSlot25AU();
	virtual void bfmeSlot26AU();
	virtual void bfmeSlot27AU();
	virtual void bfmeSlot28AU();
	virtual void bfmeSlot29AU();
	virtual void bfmeStoreAU(void *dst);
};

extern "C" void __cdecl bfmeXferAU(BfmeAgentAU *ag, void *dst);

class BfmeHostAU
{
public:
	void bfmeSaveAU(BfmeAgentAU *ag);
	void bfmeBeginAU(BfmeAgentAU *ag);

	unsigned char m_bfmeHeadAU[0x38];
	unsigned char m_bfmeSlotAAU[4];
	unsigned char m_bfmeSlotBAU[0xc];
	unsigned char m_bfmeSlotCAU[4];
};

void BfmeHostAU::bfmeSaveAU(BfmeAgentAU *ag)
{
	bfmeBeginAU(ag);

	if (ag->bfmeSkipAU() != 0)
		return;

	BfmeInfoAU info;

	info.m_bfmeFlagAU = 1;
	info.m_bfmeLevelAU = 2;
	ag->bfmeFillAU(&info);

	bfmeXferAU(ag, m_bfmeSlotAAU);
	ag->bfmeWriteAU(m_bfmeSlotBAU);

	if (info.m_bfmeLevelAU >= 2)
		ag->bfmeStoreAU(m_bfmeSlotCAU);
}
