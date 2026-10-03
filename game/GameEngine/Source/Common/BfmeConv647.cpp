extern "C" unsigned char __identifier("??_7V3Vt0110F97C@@6B@")[];
extern "C" unsigned char __identifier("??_7BfmeHolderCU@@6B@")[];

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

struct BfmeSecondCUB
{
	void *m_bfmeVft;
};

struct BfmeThingCUB
{
	void *m_bfmeVftB;
	GenNode_006fa270 m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUB m_bfmeSecond;
};

void __fastcall bfmeGoCUB(BfmeThingCUB *p)
{
	BfmeSecondCUB *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = __identifier("??_7V3Vt0110F97C@@6B@");
	p->m_bfmeVftB = __identifier("??_7BfmeHolderCU@@6B@");
	p->m_bfmeBase.unlink();
}
