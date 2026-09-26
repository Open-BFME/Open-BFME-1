struct BfmeSubBJF
{
	void bfmeDoBJF(void *one, void *two, int flag);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBJF
{
public:
	void bfmeGoBJF(void *one, void *two);
	unsigned char m_bfmeHead[0x14];
	BfmeSubBJF m_bfmeSub;
};

void BfmeThingBJF::bfmeGoBJF(void *one, void *two)
{
	m_bfmeSub.bfmeDoBJF(one, two, 1);
}
