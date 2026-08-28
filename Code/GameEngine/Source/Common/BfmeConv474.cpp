struct BfmeSubBJC
{
	void bfmeDoBJC(void *what);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBJC
{
public:
	void *bfmeGoBJC(void *what);
	unsigned char m_bfmeHead[0x9c];
	BfmeSubBJC m_bfmeSub;
};

void *BfmeThingBJC::bfmeGoBJC(void *what)
{
	m_bfmeSub.bfmeDoBJC(what);
	return what;
}
