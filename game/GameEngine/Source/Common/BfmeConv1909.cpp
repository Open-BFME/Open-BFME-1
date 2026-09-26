class BfmeAgentBD;

struct BfmeInfoBD
{
	unsigned char m_bfmeFlagBD;
	unsigned char m_bfmeLevelBD;
};

class BfmeAgentBD
{
public:
	virtual void bfmeSlot00BD();
	virtual void bfmeSlot01BD();
	virtual void bfmeSlot02BD();
	virtual void bfmeSlot03BD();
	virtual char bfmeSkipBD();
	virtual void bfmeSlot05BD();
	virtual void bfmeSlot06BD();
	virtual void bfmeSlot07BD();
	virtual void bfmeSlot08BD();
	virtual void bfmeBlockBD(void *dst, int size);
	virtual void bfmeFillBD(BfmeInfoBD *info);
	virtual void bfmeSlot11BD();
	virtual void bfmeSlot12BD();
	virtual void bfmeSlot13BD();
	virtual void bfmeSlot14BD();
	virtual void bfmeSlot15BD();
	virtual void bfmeSlot16BD();
	virtual void bfmeSlot17BD();
	virtual void bfmeSlot18BD();
	virtual void bfmeSlot19BD();
	virtual void bfmeSlot20BD();
	virtual void bfmeSlot21BD();
	virtual void bfmeSlot22BD();
	virtual void bfmeSlot23BD();
	virtual void bfmeSlot24BD();
	virtual void bfmeSlot25BD();
	virtual void bfmeSlot26BD();
	virtual void bfmeLateBD(void *dst);
	virtual void bfmeSlot28BD();
	virtual void bfmeSlot29BD();
	virtual void bfmeSlot30BD();
	virtual void bfmeSlot31BD();
	virtual void bfmeSlot32BD();
	virtual void bfmeSlot33BD();
	virtual void bfmeSlot34BD();
	virtual void bfmeByteBD(unsigned char *dst);
};

class BfmeSubBD
{
public:
	virtual void bfmeSlot0BD();
	virtual void bfmeSlot1BD();
	virtual void bfmeSlot2BD();
	virtual void bfmeSaveBD(BfmeAgentBD *ag);

	unsigned char m_bfmePadBD[0x48];
};

class BfmeHostBD
{
public:
	void bfmeSaveBD(BfmeAgentBD *ag);
	void bfmeBeginBD(BfmeAgentBD *ag);

	unsigned char m_bfmeHeadBD[0x20];
	unsigned char m_bfmeSlotABD[4];
	BfmeSubBD m_bfmeSubBD;
	unsigned char m_bfmeSlotBBD[4];
	unsigned char m_bfmeSlotCBD;
	unsigned char m_bfmeSlotDBD;
};

void BfmeHostBD::bfmeSaveBD(BfmeAgentBD *ag)
{
	bfmeBeginBD(ag);

	if (ag->bfmeSkipBD() != 0)
		return;

	BfmeInfoBD info;

	info.m_bfmeFlagBD = 1;
	info.m_bfmeLevelBD = 1;
	ag->bfmeFillBD(&info);

	ag->bfmeLateBD(m_bfmeSlotBBD);
	ag->bfmeByteBD(&m_bfmeSlotCBD);
	ag->bfmeByteBD(&m_bfmeSlotDBD);
	ag->bfmeBlockBD(m_bfmeSlotABD, 4);
	m_bfmeSubBD.bfmeSaveBD(ag);
}
