struct BfmeSubBJE
{
	void bfmeDoBJE(void *what);
	unsigned char m_bfmeHead[0x10];
};

class BfmeThingBJE
{
public:
	void *bfmeGoBJE(void *what);
	unsigned char m_bfmeHead[0x20];
	BfmeSubBJE m_bfmeSub;
	void *m_bfmeWhat;
};

void *BfmeThingBJE::bfmeGoBJE(void *what)
{
	void *got = m_bfmeWhat;
	m_bfmeSub.bfmeDoBJE(what);
	return got;
}
