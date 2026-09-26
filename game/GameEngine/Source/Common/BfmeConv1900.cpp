struct BfmeInfoAT
{
	unsigned char m_bfmeFlagAT;
	unsigned char m_bfmeLevelAT;
};

class BfmeAgentAT
{
public:
	virtual void bfmeSlot00AT();
	virtual void bfmeSlot01AT();
	virtual void bfmeSlot02AT();
	virtual void bfmeSlot03AT();
	virtual char bfmeSkipAT();
	virtual void bfmeSlot05AT();
	virtual void bfmeSlot06AT();
	virtual void bfmeSlot07AT();
	virtual void bfmeSlot08AT();
	virtual void bfmeSlot09AT();
	virtual void bfmeFillAT(BfmeInfoAT *info);
	virtual void bfmeSlot11AT();
	virtual void bfmeSlot12AT();
	virtual void bfmeSlot13AT();
	virtual void bfmeSlot14AT();
	virtual void bfmeSlot15AT();
	virtual void bfmeSlot16AT();
	virtual void bfmeSlot17AT();
	virtual void bfmeSlot18AT();
	virtual void bfmeSlot19AT();
	virtual void bfmeSlot20AT();
	virtual void bfmeSlot21AT();
	virtual void bfmeSlot22AT();
	virtual void bfmeSlot23AT();
	virtual void bfmeSlot24AT();
	virtual void bfmeSlot25AT();
	virtual void bfmeSlot26AT();
	virtual void bfmeWriteAT(void *dst);
	virtual void bfmeSlot28AT();
	virtual void bfmeSlot29AT();
	virtual void bfmeSlot30AT();
	virtual void bfmeSlot31AT();
	virtual void bfmeSlot32AT();
	virtual void bfmeSlot33AT();
	virtual void bfmeSlot34AT();
	virtual void bfmeStoreAT(void *dst);
};

class BfmeHostAT
{
public:
	void bfmeSaveAT(BfmeAgentAT *ag);
	void bfmeBeginAT(BfmeAgentAT *ag);
	void bfmeEndAT(BfmeAgentAT *ag);

	unsigned char m_bfmeHeadAT[0xec];
	unsigned char m_bfmeSlotBAT[4];
	unsigned char m_bfmeSlotAAT[4];
};

void BfmeHostAT::bfmeSaveAT(BfmeAgentAT *ag)
{
	bfmeBeginAT(ag);

	if (ag->bfmeSkipAT() != 0)
		return;

	BfmeInfoAT info;

	info.m_bfmeFlagAT = 1;
	info.m_bfmeLevelAT = 2;
	ag->bfmeFillAT(&info);

	ag->bfmeStoreAT(m_bfmeSlotAAT);
	ag->bfmeWriteAT(m_bfmeSlotBAT);

	if (info.m_bfmeLevelAT >= 2)
		bfmeEndAT(ag);
}
