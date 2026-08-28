struct BfmeDeepRZ
{
	unsigned char m_bfmeHead[0x40];
	unsigned int m_bfmeFlags;
};

struct BfmeMidRZ
{
	unsigned char m_bfmeHead[0x1cc];
	BfmeDeepRZ *m_bfmeDeep;
};

struct BfmeInnerRZ
{
	unsigned char m_bfmeHead[0x204];
	BfmeMidRZ *m_bfmeMid;
};

struct BfmeOuterRZ
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerRZ *m_bfmeInner;
};

class BfmeThingRZ
{
public:
	void bfmeStepRZ(void *what);
	void bfmeGoRZ(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOuterRZ *m_bfmeOuter;
};

void BfmeThingRZ::bfmeGoRZ(void *what)
{
	bfmeStepRZ(what);
	BfmeMidRZ *mid = m_bfmeOuter->m_bfmeInner->m_bfmeMid;
	if (mid != 0)
	{
		BfmeDeepRZ *deep = mid->m_bfmeDeep;
		if (deep != 0)
			deep->m_bfmeFlags &= 0xfffffff7;
	}
}
