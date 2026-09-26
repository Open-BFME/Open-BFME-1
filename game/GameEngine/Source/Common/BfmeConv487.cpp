struct BfmeSubBLF
{
	unsigned char m_bfmeHead[4];
};

void bfmeDoBLF(BfmeSubBLF *sub, void *what, int many);

class BfmeThingBLF
{
public:
	void bfmeGoBLF(void *what);
	unsigned char m_bfmeHead[0x174];
	BfmeSubBLF m_bfmeSub;
};

void BfmeThingBLF::bfmeGoBLF(void *what)
{
	bfmeDoBLF(&m_bfmeSub, what, 0x20);
}
