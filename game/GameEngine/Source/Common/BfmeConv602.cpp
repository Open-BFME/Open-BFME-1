// bfmeVftCIA is ??_7Gen_000B5240@@6B@ at 0x010827DC, the vftable of the
// Gen_000B5240 class (see dir32_addresses.csv).
extern "C" unsigned char __identifier("??_7Gen_000B5240@@6B@")[];
#define bfmeVftCIA __identifier("??_7Gen_000B5240@@6B@")

struct BfmeThingCIA
{
	void bfmeBaseCIA();
	BfmeThingCIA *bfmeInitCIA(void *what);
	void *volatile m_bfmeVft;
	unsigned char m_bfmeGap[0x94];
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	void *volatile m_bfmeC;
};

BfmeThingCIA *BfmeThingCIA::bfmeInitCIA(void *what)
{
	bfmeBaseCIA();
	m_bfmeVft = bfmeVftCIA;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = what;
	return this;
}
