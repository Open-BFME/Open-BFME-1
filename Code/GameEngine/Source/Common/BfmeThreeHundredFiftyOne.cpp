extern "C" unsigned char bfmeVftTL[];

class BfmeThingTL
{
public:
	void bfmeBaseTL(void *what, int flag);
	BfmeThingTL *bfmeInitTL(void *what);
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0x50];
	void *m_bfmeWhat;
};

BfmeThingTL *BfmeThingTL::bfmeInitTL(void *what)
{
	bfmeBaseTL(what, 0);
	m_bfmeWhat = what;
	m_bfmeVft = bfmeVftTL;
	return this;
}
