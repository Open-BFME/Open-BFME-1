// ?bfmeFireDN@BfmeHostDN@@QAEXH@Z
// partial score=0.7 date=2026-09-08
extern "C" void *bfmeMsgVftDN[];

class BfmeMsgDN
{
public:
	BfmeMsgDN(void *p)
	{
		m_bfmeVftDN = bfmeMsgVftDN;
		m_bfmePtrDN = p;
		m_bfmeFlagDN = 0;
	}

	~BfmeMsgDN();

	void *m_bfmeVftDN;
	void *m_bfmePtrDN;
	int m_bfmeFlagDN;
};

class ControlBar
{
public:
	void bfmeSendDN(BfmeMsgDN *m);
};

extern ControlBar *TheControlBar;

class BfmeNodeDN
{
public:
	unsigned char m_bfmeHeadDN[8];
	void *m_bfmeValDN;
};

class BfmeSlotDN
{
public:
	BfmeNodeDN *m_bfmeFirstDN;
	unsigned char m_bfmeGapDN[0x14];
};

class BfmeBucketDN
{
public:
	unsigned char m_bfmeHeadDN[4];
	BfmeNodeDN *m_bfmeEndDN;
	BfmeSlotDN m_bfmeSlotsDN[1];
};

class BfmeHostDN
{
public:
	void bfmeFireDN(int unused);

	BfmeBucketDN *m_bfmeBucketDN;
	int m_bfmeIndexDN;
};

void BfmeHostDN::bfmeFireDN(int unused)
{
	BfmeBucketDN *b = m_bfmeBucketDN;
	BfmeNodeDN *e = b->m_bfmeSlotsDN[m_bfmeIndexDN].m_bfmeFirstDN;

	if (e != b->m_bfmeEndDN)
	{
		BfmeMsgDN msg(e->m_bfmeValDN);

		TheControlBar->bfmeSendDN(&msg);
	}
}
