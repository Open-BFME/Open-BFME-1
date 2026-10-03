class BfmeThingBVA
{
public:
	BfmeThingBVA *bfmeGoBVA(BfmeThingBVA *other);
	unsigned char m_bfmeHead[0xc];
	int m_bfmeWhat;
	bool m_bfmeFlag;
};

// Retail calls the ILT thunk at 0x00015280, owned by game/gen_small/thunks_009.cpp
// as ?j_00015280@@YAXXZ (its target, 0x00135DF0, has no ledger row of its own).
// The call is reached through a member-function pointer so it keeps its
// thiscall shape; bfmeStepBVA is never referenced by name.
extern "C" void __cdecl __identifier("?j_00015280@@YAXXZ")();
typedef void (BfmeThingBVA::*BfmeStepBVAThunk)(BfmeThingBVA *other);
union BfmeStepBVAThunkRef
{
	void *m_thunk;
	BfmeStepBVAThunk m_call;
};

BfmeThingBVA *BfmeThingBVA::bfmeGoBVA(BfmeThingBVA *other)
{
	if (this != other)
	{
		BfmeStepBVAThunkRef step;
		step.m_thunk = (void *)&__identifier("?j_00015280@@YAXXZ");
		(this->*step.m_call)(other);
		m_bfmeFlag = true;
		m_bfmeWhat = other->m_bfmeWhat;
	}
	return this;
}