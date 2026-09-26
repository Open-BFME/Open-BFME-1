class BfmeAgentAR;

struct BfmeInfoAR
{
	unsigned char m_bfmeFlagAR;
	unsigned char m_bfmeLevelAR;
};

class BfmeAgentAR
{
public:
	virtual void bfmeSlot00AR();
	virtual void bfmeSlot01AR();
	virtual void bfmeSlot02AR();
	virtual void bfmeSlot03AR();
	virtual void bfmeSlot04AR();
	virtual void bfmeSlot05AR();
	virtual void bfmeSlot06AR();
	virtual void bfmeSlot07AR();
	virtual void bfmeSlot08AR();
	virtual void bfmeSlot09AR();
	virtual void bfmeFillAR(BfmeInfoAR *info);
	virtual void bfmeSlot11AR();
	virtual void bfmeSlot12AR();
	virtual void bfmeSlot13AR();
	virtual void bfmeSlot14AR();
	virtual void bfmeSlot15AR();
	virtual void bfmeSlot16AR();
	virtual void bfmeSlot17AR();
	virtual void bfmeSlot18AR();
	virtual void bfmeSlot19AR();
	virtual void bfmeSlot20AR();
	virtual void bfmeSlot21AR();
	virtual void bfmeSlot22AR();
	virtual void bfmeSlot23AR();
	virtual void bfmeSlot24AR();
	virtual void bfmeSlot25AR();
	virtual void bfmeSlot26AR();
	virtual void bfmeSlot27AR();
	virtual void bfmeSlot28AR();
	virtual void bfmeSlot29AR();
	virtual void bfmeApplyAR(void *what);
};

class BfmeSubAR
{
public:
	void bfmeNotifyAR(BfmeAgentAR *ag);
};

class BfmeVirtAR
{
public:
	virtual void bfmeReleaseAR(BfmeAgentAR *ag);
};

class BfmeHostAR
{
public:
	void bfmeSendAR(BfmeAgentAR *ag);

	void bfmeHighAR(BfmeAgentAR *ag);
	void bfmeLowAR(BfmeAgentAR *ag);

	unsigned char m_bfmeHeadAR[0x20];
	BfmeSubAR m_bfmeSubAR;
	unsigned char m_bfmePadAR[0xb];
	BfmeVirtAR m_bfmeVirtAR;
	unsigned char m_bfmeMidAR[0x58];
	unsigned char m_bfmeStateAR[4];
};

void BfmeHostAR::bfmeSendAR(BfmeAgentAR *ag)
{
	BfmeInfoAR info;

	info.m_bfmeFlagAR = 1;
	info.m_bfmeLevelAR = 3;
	ag->bfmeFillAR(&info);

	if (info.m_bfmeLevelAR >= 2)
		bfmeHighAR(ag);
	else
		bfmeLowAR(ag);

	m_bfmeSubAR.bfmeNotifyAR(ag);

	if (info.m_bfmeLevelAR >= 3)
	{
		m_bfmeVirtAR.bfmeReleaseAR(ag);
		ag->bfmeApplyAR(m_bfmeStateAR);
	}
}
