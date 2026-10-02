extern "C" unsigned char bfmeVftCUDa[];
extern "C" unsigned char bfmeVftCUDb[];

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

struct BfmeSecondCUD
{
	void *m_bfmeVft;
};

struct BfmeThingCUD
{
	void *m_bfmeVftB;
	GenNode_006fa270 m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUD m_bfmeSecond;
};

void __fastcall bfmeGoCUD(BfmeThingCUD *p)
{
	BfmeSecondCUD *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = bfmeVftCUDa;
	p->m_bfmeVftB = bfmeVftCUDb;
	p->m_bfmeBase.unlink();
}
