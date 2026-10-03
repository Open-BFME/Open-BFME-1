// These are the existing vftable definitions at the two retail addresses:
// CategoryModuleInfo<3> is explicitly instantiated in fx_particle_system.cpp,
// and V3NodeHead is emitted by RenderObjectDrawModuleDestructor.cpp (also used
// by BfmeConv2062.cpp).
extern "C" void *__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")[ ];
extern "C" void *__identifier("??_7V3NodeHead@@6B@")[ ];

// The tail call at this+4 is the 0x00013994 ILT thunk into the matched
// ?unlink@GenNode_006fa270@@QAEXXZ (see
// game/GameEngine/Source/Common/Gen_006fa270.cpp), so the node is
// re-declared here by its defining name with the member function
// declared but not defined: this TU emits no second copy of that
// COMDAT.
struct GenNode_006fa270
{
	void unlink();
};

struct BfmeSecondCUF
{
	void *m_bfmeVft;
};

struct BfmeThingCUF
{
	void *m_bfmeVftB;
	GenNode_006fa270 m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUF m_bfmeSecond;
};

void __fastcall bfmeGoCUF(BfmeThingCUF *p)
{
	BfmeSecondCUF *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = __identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@");
	p->m_bfmeVftB = __identifier("??_7V3NodeHead@@6B@");
	p->m_bfmeBase.unlink();
}
