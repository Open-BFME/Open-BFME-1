// Existing vftables at VA 01073744, 0110F978, 01110898 and 0111126C,
// respectively, as recorded in dir32_addresses.csv.
extern "C" unsigned char __identifier("??_7Snapshot@@6B@")[];
extern "C" unsigned char __identifier("??_7PolymorphicVptrBase0110F978@@6B@")[];
extern "C" unsigned char __identifier("??_7Rva005D4F30Poly@@6B@")[];
extern "C" unsigned char __identifier("??_7V3NodeHead@@6B@")[];

struct GenNode_006fa270
{
	void unlink();
};

struct BfmeSub1DJD
{
	void *m_bfmeVft;
};

struct BfmeSub2DJD
{
	void *m_bfmeVft;
};

struct BfmeSub3DJD
{
	void *m_bfmeVft;
};

struct BfmeThingDJD
{
	void *m_bfmeVft;
	GenNode_006fa270 m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJD m_bfme3;
	BfmeSub2DJD m_bfme2;
	BfmeSub1DJD m_bfme1;
};

void __fastcall bfmeGoDJD(BfmeThingDJD *p)
{
	BfmeSub1DJD *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = __identifier("??_7Snapshot@@6B@");
	BfmeSub2DJD *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = __identifier("??_7PolymorphicVptrBase0110F978@@6B@");
	BfmeSub3DJD *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = __identifier("??_7Rva005D4F30Poly@@6B@");
	p->m_bfmeVft = __identifier("??_7V3NodeHead@@6B@");
	p->m_bfmeBase.unlink();
}
