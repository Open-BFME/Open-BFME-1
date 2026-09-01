// Open-BFME5 conversions.

struct BfmeBlockVKT
{
	int m_bfmeArr[10];
};

class BfmeThingVKT
{
public:
	BfmeThingVKT *bfmeInitVKT(const BfmeBlockVKT &a, const BfmeBlockVKT &b);
	void bfmeBaseVKT();
	int m_bfme00;
	BfmeBlockVKT m_bfme04;
	BfmeBlockVKT m_bfme2c;
};

BfmeThingVKT *BfmeThingVKT::bfmeInitVKT(const BfmeBlockVKT &a, const BfmeBlockVKT &b)
{
	bfmeBaseVKT();
	m_bfme04 = a;
	m_bfme2c = b;
	return this;
}

struct BfmeStateVKU
{
	BfmeBlockVKT m_bfme00;
	BfmeBlockVKT m_bfme28;
};

void __cdecl bfmeCallVKU(void *a, int b, BfmeStateVKU *c, int d);

void __cdecl bfmeGoVKU(void *a, int unused, BfmeStateVKU *b)
{
	bfmeCallVKU(a, 0, b, 0);
	b->m_bfme28 = b->m_bfme00;
}
