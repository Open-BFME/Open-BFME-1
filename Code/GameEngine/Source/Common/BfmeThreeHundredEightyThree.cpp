struct BfmeOutAC
{
	unsigned char m_bfmeHead[0x3c];
	void *m_bfmeWhat;
};

class BfmeInnerAC
{
public:
	virtual void *bfmeGetAC();
};

struct BfmeSubAC
{
	unsigned char m_bfmeHead[0x14];
	BfmeInnerAC m_bfmeInner;
};

class BfmeNextAC
{
public:
	void bfmeSendAC(BfmeOutAC *out);
};

class BfmeThingAC
{
public:
	void bfmeGoAC(BfmeOutAC *out);
	BfmeSubAC *m_bfmeSub;
	BfmeNextAC m_bfmeNext;
};

void BfmeThingAC::bfmeGoAC(BfmeOutAC *out)
{
	BfmeSubAC *sub = m_bfmeSub;
	if (sub != 0)
		out->m_bfmeWhat = sub->m_bfmeInner.bfmeGetAC();
	else
		out->m_bfmeWhat = 0;
	m_bfmeNext.bfmeSendAC(out);
}
