// Existing vftables at VA 01073744, 01073760, 0111081C and 0111126C,
// respectively, as recorded in dir32_addresses.csv.
extern "C" unsigned char __identifier("??_7Snapshot@@6B@")[];
extern "C" unsigned char __identifier("??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@")[];
extern "C" unsigned char __identifier("??_7Rva005D47A0Poly@@6B@")[];
extern "C" unsigned char __identifier("??_7V3NodeHead@@6B@")[];

struct GenNode_006fa270
{
	void unlink();
};

struct BfmeSub1DJB
{
	void *m_bfmeVft;
};

struct BfmeSub2DJB
{
	void *m_bfmeVft;
};

struct BfmeSub3DJB
{
	void *m_bfmeVft;
};

struct BfmeThingDJB
{
	void *m_bfmeVft;
	GenNode_006fa270 m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJB m_bfme3;
	BfmeSub2DJB m_bfme2;
	BfmeSub1DJB m_bfme1;
};

void __fastcall bfmeGoDJB(BfmeThingDJB *p)
{
	BfmeSub1DJB *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = __identifier("??_7Snapshot@@6B@");
	BfmeSub2DJB *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = __identifier("??_7?$CategoryModuleInfo@$0A@@FXParticleSystem@@6B@");
	BfmeSub3DJB *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = __identifier("??_7Rva005D47A0Poly@@6B@");
	p->m_bfmeVft = __identifier("??_7V3NodeHead@@6B@");
	p->m_bfmeBase.unlink();
}
