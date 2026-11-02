// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x0058D820 (101 B, EA file Palantir.cpp): if the indexed bucket slot
// is not the end node, hand ControlBar a stack message carrying its value.
// The earlier name bfmeFireDN is contradicted by ilt_oracle at ILT 0x0001F1AE,
// so the address names it. The message class installs the vtable recorded at
// VA 0x010F5738 as ??_7BfmeMsgDN@@6B@; its inline virtual destructor keeps
// retail's EH frame with no destructor call.

struct BfmeMsgDN
{
	BfmeMsgDN(void *p)
	{
		m_bfmePtrDN = p;
		m_bfmeFlagDN = 0;
	}

	virtual ~BfmeMsgDN() {}

	void *m_bfmePtrDN;
	int m_bfmeFlagDN;
};

class ControlBar
{
public:
	void bfmeShowDN(BfmeMsgDN *source);	// 0x004C15D0
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
	void rva0058D820(int unused);

	BfmeBucketDN *m_bfmeBucketDN;
	int m_bfmeIndexDN;
};

void BfmeHostDN::rva0058D820(int unused)
{
	BfmeBucketDN *b = m_bfmeBucketDN;
	BfmeSlotDN &slot = b->m_bfmeSlotsDN[m_bfmeIndexDN];
	BfmeNodeDN *end = b->m_bfmeEndDN;
	BfmeNodeDN *e = slot.m_bfmeFirstDN;
	if (e != end)
	{
		BfmeMsgDN msg(e->m_bfmeValDN);
		TheControlBar->bfmeShowDN(&msg);
	}
}
