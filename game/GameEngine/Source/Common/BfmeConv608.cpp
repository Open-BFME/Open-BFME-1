// bfmeVftCJA is ??_7Gen_000B5240@@6B@ at 0x010827DC, the vftable of the
// Gen_000B5240 class (see dir32_addresses.csv).
extern "C" unsigned char __identifier("??_7Gen_000B5240@@6B@")[];
#define bfmeVftCJA __identifier("??_7Gen_000B5240@@6B@")

struct BfmeThingCJA
{
	void bfmeBaseCJA(void *what);
	BfmeThingCJA *bfmeInitCJA(void *what, void *owner);
	void *volatile m_bfmeVft;
	unsigned char m_bfmeGap[0x94];
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	void *volatile m_bfmeC;
};

BfmeThingCJA *BfmeThingCJA::bfmeInitCJA(void *what, void *owner)
{
	bfmeBaseCJA(what);
	m_bfmeVft = bfmeVftCJA;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = owner;
	return this;
}
