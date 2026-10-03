// Retail's call goes through the ILT thunk at 0x0003050D, whose ledger row is
// ?j_0003050d@@YAXXZ (game/gen_small/thunks_023.cpp).
extern void j_0003050d();

class BfmeOtherDQE
{
};

class BfmeThingDQE
{
public:
	BfmeOtherDQE *bfmeGoDQE(BfmeOtherDQE *other, void *a, void *b, void *c, void *what);
};

template <class R, class A>
__forceinline R call1(void (*p)(), void *self, A a)
{
	typedef R (BfmeOtherDQE::*F)(A);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((BfmeOtherDQE *)self)->*u.f)(a);
}

BfmeOtherDQE *BfmeThingDQE::bfmeGoDQE(BfmeOtherDQE *other, void *a, void *b, void *c, void *what)
{
	volatile int tmp = 0;
	call1<void>(j_0003050d, other, what);
	return other;
}