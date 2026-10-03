// cl: /DNDEBUG /MD /EHsc

// Retail's call goes through the ILT thunk at 0x00008E68, whose ledger row is
// ?j_00008e68@@YAXXZ (game/gen_small/thunks_003.cpp).
extern void j_00008e68();

struct BfmePartBMC492
{
	unsigned char m_bfmeHead[4];
};

class BfmeSubBMC492
{
};

struct BfmeOwnerBMC492
{
	unsigned char m_bfmeHead[0x90];
	BfmeSubBMC492 m_bfmeSub;
};

class BfmeThingBMC492
{
public:
	bool bfmeCheckBMC(BfmeOwnerBMC492 *owner);
	unsigned char m_bfmeHead[8];
	BfmePartBMC492 m_bfmeA;
	unsigned char m_bfmeGap[8];
	BfmePartBMC492 m_bfmeB;
};

template <class R, class A, class B>
__forceinline R call2(void (*p)(), void *self, A a, B b)
{
	typedef R (BfmeSubBMC492::*F)(A, B);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((BfmeSubBMC492 *)self)->*u.f)(a, b);
}

// ?bfmeCheckBMC@BfmeThingBMC492@@QAE_NPAUBfmeOwnerBMC492@@@Z
bool BfmeThingBMC492::bfmeCheckBMC(BfmeOwnerBMC492 *owner)
{
	return !call2<unsigned char>(j_00008e68, &owner->m_bfmeSub, &m_bfmeA, &m_bfmeB);
}