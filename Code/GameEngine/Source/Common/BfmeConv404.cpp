class BfmeSubAHA
{
public:
	void bfmeStopAHA(int what);
};

class BfmeKillAHA
{
public:
	virtual void bfmeReleaseAHA(int what);
};

struct BfmeMidAHA
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubAHA *m_bfmeSub;
	unsigned char m_bfmeGap[0x19c];
	int m_bfmeFlag;
};

struct BfmeOwnerAHA
{
	unsigned char m_bfmeHead[0x10];
	BfmeMidAHA *m_bfmeMid;
};

class BfmeThingAHA
{
public:
	void bfmeGoAHA(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerAHA *m_bfmeOwner;
	unsigned char m_bfmeGapTwo[4];
	BfmeKillAHA *m_bfmeKill;
};

void BfmeThingAHA::bfmeGoAHA(void *what)
{
	BfmeSubAHA *sub = m_bfmeOwner->m_bfmeMid->m_bfmeSub;
	if (sub != 0)
		sub->bfmeStopAHA(0);
	m_bfmeOwner->m_bfmeMid->m_bfmeFlag = 0;
	BfmeKillAHA *kill = m_bfmeKill;
	if (kill != 0)
	{
		kill->bfmeReleaseAHA(1);
		m_bfmeKill = 0;
	}
}
