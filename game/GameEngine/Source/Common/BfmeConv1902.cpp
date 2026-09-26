struct BfmeInfoAV
{
	unsigned char m_bfmeFlagAV;
	unsigned char m_bfmeLevelAV;
};

class BfmeAgentAV
{
public:
	virtual void bfmeSlot00AV();
	virtual void bfmeSlot01AV();
	virtual void bfmeSlot02AV();
	virtual void bfmeSlot03AV();
	virtual char bfmeSkipAV();
	virtual void bfmeSlot05AV();
	virtual void bfmeSlot06AV();
	virtual void bfmeSlot07AV();
	virtual void bfmeSlot08AV();
	virtual void bfmeSlot09AV();
	virtual void bfmeFillAV(BfmeInfoAV *info);
	virtual void bfmeSlot11AV();
	virtual void bfmeSlot12AV();
	virtual void bfmeSlot13AV();
	virtual void bfmeSlot14AV();
	virtual void bfmeSlot15AV();
	virtual void bfmeSlot16AV();
	virtual void bfmeSlot17AV();
	virtual void bfmeSlot18AV();
	virtual void bfmeSlot19AV();
	virtual void bfmeSlot20AV();
	virtual void bfmeSlot21AV();
	virtual void bfmeSlot22AV();
	virtual void bfmeSlot23AV();
	virtual void bfmeSlot24AV();
	virtual void bfmeSlot25AV();
	virtual void bfmeSlot26AV();
	virtual void bfmeSlot27AV();
	virtual void bfmeSlot28AV();
	virtual void bfmeStoreAV(void *dst);
	virtual void bfmeSlot30AV();
	virtual void bfmeSlot31AV();
	virtual void bfmeSlot32AV();
	virtual void bfmeSlot33AV();
	virtual void bfmeSlot34AV();
	virtual void bfmeByteAV(unsigned char *dst);
};

class BfmeHostAV
{
public:
	void bfmeSaveAV(BfmeAgentAV *ag);
	void bfmeBeginAV(BfmeAgentAV *ag);

	unsigned char m_bfmeHeadAV[0x24];
	unsigned char m_bfmeGateAV[4];
	unsigned char m_bfmeFirstAV;
	unsigned char m_bfmeSecondAV;
	unsigned char m_bfmeThirdAV;
};

void BfmeHostAV::bfmeSaveAV(BfmeAgentAV *ag)
{
	bfmeBeginAV(ag);

	if (ag->bfmeSkipAV() != 0)
		return;

	BfmeInfoAV info;

	info.m_bfmeFlagAV = 1;
	info.m_bfmeLevelAV = 2;
	ag->bfmeFillAV(&info);

	ag->bfmeByteAV(&m_bfmeFirstAV);
	ag->bfmeByteAV(&m_bfmeThirdAV);
	ag->bfmeByteAV(&m_bfmeSecondAV);

	if (info.m_bfmeLevelAV >= 2)
		ag->bfmeStoreAV(m_bfmeGateAV);
}
