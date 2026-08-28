struct BfmeSubBID
{
	void bfmeDoBID(void *what);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBID
{
public:
	BfmeThingBID *bfmeGoBID(void *what);
	unsigned char m_bfmeHead[4];
	BfmeSubBID m_bfmeSub;
};

BfmeThingBID *BfmeThingBID::bfmeGoBID(void *what)
{
	m_bfmeSub.bfmeDoBID(what);
	return this;
}
