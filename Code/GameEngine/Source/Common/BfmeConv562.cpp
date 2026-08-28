class BfmeSubCBA
{
public:
	void bfmeOneCBA(void *what);
	unsigned char m_bfmeHead[0x50];
};

class BfmeOtherCBA
{
public:
	void bfmeTwoCBA(void *what);
};

class BfmeThingCBA
{
public:
	void bfmeGoCBA(void *what);
	unsigned char m_bfmeHead[0x104];
	BfmeSubCBA m_bfmeA;
	BfmeOtherCBA m_bfmeB;
};

void BfmeThingCBA::bfmeGoCBA(void *what)
{
	m_bfmeA.bfmeOneCBA(what);
	m_bfmeB.bfmeTwoCBA(what);
}
