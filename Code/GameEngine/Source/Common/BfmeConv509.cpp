class BfmeSubBPE
{
public:
	void bfmeOneBPE();
};

class BfmeThingBPE
{
public:
	void bfmeGoBPE();
	unsigned char m_bfmeHead[0x28];
	BfmeSubBPE *m_bfmeB;
	BfmeSubBPE *m_bfmeA;
};

void BfmeThingBPE::bfmeGoBPE()
{
	BfmeSubBPE *a = m_bfmeA;
	if (a != 0)
		a->bfmeOneBPE();
	BfmeSubBPE *b = m_bfmeB;
	if (b != 0)
		b->bfmeOneBPE();
}
