struct BfmeSubBPF
{
	unsigned char m_bfmeHead[4];
};

void bfmeDoBPF(void *one, BfmeSubBPF *sub, void *two);

class BfmeThingBPF
{
public:
	void bfmeGoBPF(void *one, void *two);
	unsigned char m_bfmeHead[0x14];
	BfmeSubBPF m_bfmeSub;
};

void BfmeThingBPF::bfmeGoBPF(void *one, void *two)
{
	if (one != 0)
		bfmeDoBPF(one, &m_bfmeSub, two);
}
