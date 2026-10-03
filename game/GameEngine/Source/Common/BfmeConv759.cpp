// 0x0001CB11 is retail's 5-byte ILT thunk (?j_0001cb11@@YAXXZ); the callee's
// own identity is not recovered, so the __thiscall is routed through the
// thunk's address.
extern void j_0001cb11();

class BfmeOtherDQD
{
};

class BfmeThingDQD
{
public:
	BfmeOtherDQD *bfmeGoDQD(BfmeOtherDQD *other, void *a, void *b, void *c, void *what);
};

BfmeOtherDQD *BfmeThingDQD::bfmeGoDQD(BfmeOtherDQD *other, void *a, void *b, void *c, void *what)
{
	volatile int tmp = 0;
	typedef void (BfmeOtherDQD::*Call)(void *);
	union { void (*address)(); Call member; } call = { j_0001cb11 };
	(other->*call.member)(what);
	return other;
}
