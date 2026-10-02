// Existing vftables at VA 01073744, 0110F9E4, 0111082C and 0111126C,
// respectively, as recorded in dir32_addresses.csv.
extern "C" unsigned char __identifier("??_7Snapshot@@6B@")[];
extern "C" unsigned char __identifier("??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@")[];
extern "C" unsigned char __identifier("??_7Rva005D4800Poly@@6B@")[];
extern "C" unsigned char __identifier("??_7V3NodeHead@@6B@")[];

struct GenNode_006fa270
{
	void unlink();
};

struct BfmeSub1DJC
{
	void *m_bfmeVft;
};

struct BfmeSub2DJC
{
	void *m_bfmeVft;
};

struct BfmeSub3DJC
{
	void *m_bfmeVft;
};

struct BfmeThingDJC
{
	void *m_bfmeVft;
	GenNode_006fa270 m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJC m_bfme3;
	BfmeSub2DJC m_bfme2;
	BfmeSub1DJC m_bfme1;
};

void __fastcall bfmeGoDJC(BfmeThingDJC *p)
{
	BfmeSub1DJC *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = __identifier("??_7Snapshot@@6B@");
	BfmeSub2DJC *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = __identifier("??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@");
	BfmeSub3DJC *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = __identifier("??_7Rva005D4800Poly@@6B@");
	p->m_bfmeVft = __identifier("??_7V3NodeHead@@6B@");
	p->m_bfmeBase.unlink();
}
