struct BfmeOutAC
{
	unsigned char m_bfmeHead[0x3c];
	void *m_bfmeWhat;
	void *m_bfmeFirst;
	void *m_bfmeSecond;
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

class Y3AdjOut;

class Y3Adj_005CE6A0
{
public:
	void collect( Y3AdjOut *out );

	void *m_f0;
	unsigned char m_gap[0x0c];
	void *m_f1;
	void *m_tail;
};

class BfmeNextAC
{
public:
	void bfmeSendAC(BfmeOutAC *out);
	BfmeSubAC *m_bfmeFirst;
	BfmeSubAC *m_bfmeSecond;
	Y3Adj_005CE6A0 m_bfmeTail;
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

void BfmeNextAC::bfmeSendAC(BfmeOutAC *out)
{
	BfmeSubAC *first = m_bfmeFirst;
	if (first != 0)
		out->m_bfmeFirst = first->m_bfmeInner.bfmeGetAC();
	else
		out->m_bfmeFirst = 0;

	BfmeSubAC *second = m_bfmeSecond;
	if (second != 0)
		out->m_bfmeSecond = second->m_bfmeInner.bfmeGetAC();
	else
		out->m_bfmeSecond = 0;

	m_bfmeTail.collect( (Y3AdjOut *)out );
}
