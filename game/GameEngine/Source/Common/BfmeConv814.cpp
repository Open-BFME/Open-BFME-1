// Both calls in each body were named for an invented type pair.  Retail proves
// the real targets (see the sibling files BfmeConv733.cpp / BfmeConv736.cpp
// for the same two conventions):
//
//  * the call at +0x0F goes through the incremental-link ILT slot 0x00001B18
//    to the matched body 0x005CFF50, ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ
//    (game/GameEngine/Source/Common/BfmeNullParticleSystemZA.cpp).  It is a
//    plain __cdecl call with an empty argument list, so ecx still holds the
//    receiver and no setup instruction is emitted.  The +0x10 the caller adds
//    is the int member of that ParticleSystemZA.
//  * the call at +0x1F reaches retail 0x00887B60,
//    ??0?$StringBase@D@@AAE@ABV0@@Z - StringBase<char>'s private copy
//    constructor in game/Libraries/Source/string/StringBase.cpp.  ecx becomes
//    the receiver and the single stack argument is the pointer to the int at
//    +0x10.  Its AAE (private) access spelling needs friendship, so - exactly
//    as BfmeConv733.cpp does - a declaration-only copy of the template that
//    grants this translation unit friendship is declared here.  No body is
//    redeclared; the copy ctor stays in StringBase.cpp.

class ParticleSystemZA
{
public:
	unsigned char m_bfmeHeadZA[0x10];
	int m_bfmeXZA;
};

// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ, defined in
// BfmeNullParticleSystemZA.cpp.
ParticleSystemZA *bfmeNullSystemZA(void);

template <typename Char>
class StringBase
{
	friend class BfmeThingEIB;
	StringBase(const StringBase<Char> &src);
};

class BfmeOtherEIB
{
public:
};

struct BfmeThingEIB
{

	BfmeOtherEIB *bfmeGoEIBa(BfmeOtherEIB *other);
	BfmeOtherEIB *bfmeGoEIBb(BfmeOtherEIB *other);
	BfmeOtherEIB *bfmeGoEIBc(BfmeOtherEIB *other);
	BfmeOtherEIB *bfmeGoEIBd(BfmeOtherEIB *other);
	BfmeOtherEIB *bfmeGoEIBe(BfmeOtherEIB *other);
	unsigned char m_bfmeHead[4];
	ParticleSystemZA *m_bfmeP;
};

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBa(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	ParticleSystemZA *p = m_bfmeP;
	if (!p)
		p = bfmeNullSystemZA();
	reinterpret_cast<StringBase<char> *>(other)->StringBase<char>::StringBase(
		*reinterpret_cast<const StringBase<char> *>(&p->m_bfmeXZA));
	return other;
}

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBb(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	ParticleSystemZA *p = m_bfmeP;
	if (!p)
		p = bfmeNullSystemZA();
	reinterpret_cast<StringBase<char> *>(other)->StringBase<char>::StringBase(
		*reinterpret_cast<const StringBase<char> *>(&p->m_bfmeXZA));
	return other;
}

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBc(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	ParticleSystemZA *p = m_bfmeP;
	if (!p)
		p = bfmeNullSystemZA();
	reinterpret_cast<StringBase<char> *>(other)->StringBase<char>::StringBase(
		*reinterpret_cast<const StringBase<char> *>(&p->m_bfmeXZA));
	return other;
}

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBd(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	ParticleSystemZA *p = m_bfmeP;
	if (!p)
		p = bfmeNullSystemZA();
	reinterpret_cast<StringBase<char> *>(other)->StringBase<char>::StringBase(
		*reinterpret_cast<const StringBase<char> *>(&p->m_bfmeXZA));
	return other;
}

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBe(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	ParticleSystemZA *p = m_bfmeP;
	if (!p)
		p = bfmeNullSystemZA();
	reinterpret_cast<StringBase<char> *>(other)->StringBase<char>::StringBase(
		*reinterpret_cast<const StringBase<char> *>(&p->m_bfmeXZA));
	return other;
}