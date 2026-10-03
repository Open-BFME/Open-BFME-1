extern "C" unsigned char __identifier("??_7V3Vt0110F97C@@6B@")[];
extern "C" unsigned char __identifier("??_7BfmeHolderCU@@6B@")[];

struct GenNode_006fa270
{
	void unlink();
};

struct BfmeSecondCUA
{
	void *m_bfmeVft;
};

struct BfmeThingCUA
{
	void *m_bfmeVftB;
	GenNode_006fa270 m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUA m_bfmeSecond;
};

void __fastcall bfmeGoCUA(BfmeThingCUA *p)
{
	BfmeSecondCUA *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = __identifier("??_7V3Vt0110F97C@@6B@");
	p->m_bfmeVftB = __identifier("??_7BfmeHolderCU@@6B@");
	p->m_bfmeBase.unlink();
}
