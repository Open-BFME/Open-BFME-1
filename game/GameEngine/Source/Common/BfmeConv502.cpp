struct BfmePairBOC
{
	void *m_bfmeOne;
	void *m_bfmeTwo;
};

void __stdcall bfmeTailBOC(int flag);

class BfmeThingBOC
{
public:
	void bfmeGoBOC(BfmePairBOC *pair);
	unsigned char m_bfmeHead[0xc];
	void *m_bfmeA;
	void *m_bfmeB;
};

void BfmeThingBOC::bfmeGoBOC(BfmePairBOC *pair)
{
	m_bfmeA = pair->m_bfmeOne;
	m_bfmeB = pair->m_bfmeTwo;
	bfmeTailBOC(1);
}
