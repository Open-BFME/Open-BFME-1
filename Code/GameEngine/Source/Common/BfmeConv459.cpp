struct BfmeSubBGC
{
	void bfmeDoBGC(void *what);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBGC
{
public:
	void *bfmeGoBGC(void *what);
	unsigned char m_bfmeHead[8];
	BfmeSubBGC m_bfmeSub;
};

void *BfmeThingBGC::bfmeGoBGC(void *what)
{
	m_bfmeSub.bfmeDoBGC(what);
	return what;
}
