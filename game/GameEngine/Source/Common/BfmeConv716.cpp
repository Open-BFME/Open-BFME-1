// Existing vftables at VA 01073744, 0110F9E8, 0111089C and 0111126C,
// respectively, as recorded in dir32_addresses.csv.
extern "C" unsigned char __identifier("??_7Snapshot@@6B@")[];
extern "C" unsigned char __identifier("??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@")[];
extern "C" unsigned char __identifier("??_7Rva005D4F40Poly@@6B@")[];
extern "C" unsigned char __identifier("??_7V3NodeHead@@6B@")[];

struct GenNode_006fa270
{
	void unlink();
};

struct BfmeSub1DJE
{
	void *m_bfmeVft;
};

struct BfmeSub2DJE
{
	void *m_bfmeVft;
};

struct BfmeSub3DJE
{
	void *m_bfmeVft;
};

struct BfmeThingDJE
{
	void *m_bfmeVft;
	GenNode_006fa270 m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJE m_bfme3;
	BfmeSub2DJE m_bfme2;
	BfmeSub1DJE m_bfme1;
};

void __fastcall bfmeGoDJE(BfmeThingDJE *p)
{
	BfmeSub1DJE *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = __identifier("??_7Snapshot@@6B@");
	BfmeSub2DJE *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = __identifier("??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@");
	BfmeSub3DJE *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = __identifier("??_7Rva005D4F40Poly@@6B@");
	p->m_bfmeVft = __identifier("??_7V3NodeHead@@6B@");
	p->m_bfmeBase.unlink();
}
