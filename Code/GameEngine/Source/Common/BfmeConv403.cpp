extern "C" unsigned char bfmeVftTH[];

class BfmeThingTH
{
public:
	void bfmeBaseTH(void *what);
	BfmeThingTH *bfmeInitTH(void *what);
	void *volatile m_bfmeVft;
	void *volatile m_bfmeNext;
};

BfmeThingTH *BfmeThingTH::bfmeInitTH(void *what)
{
	m_bfmeVft = bfmeVftTH;
	m_bfmeNext = 0;
	bfmeBaseTH(what);
	return this;
}
