// Open-BFME5 conversions.

struct BfmeNodeIC;

class BfmeThingIC
{
public:
	void bfmeDoIC(void *v, BfmeNodeIC *n);
	void *m_bfmeVal;
};

struct BfmeNodeIC
{
	char m_bfmePad[0x28];
	BfmeNodeIC *m_bfmeNext;
};

void __stdcall bfmeGoIC(BfmeNodeIC *n, BfmeThingIC *t)
{
	while (n) {
		t->bfmeDoIC(t->m_bfmeVal, n);
		n = n->m_bfmeNext;
	}
}
