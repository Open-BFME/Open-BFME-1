class BfmeSubFCB
{
public:
	char m_bfmeUnused;
};

// Retail calls the ILT thunk at 0x00043135, owned by game/gen_small/thunks_032.cpp
// as ?j_00043135@@YAXXZ (its target, 0x005CD6B0, has no ledger row of its own).
// The call is reached through a member-function pointer so it keeps its
// thiscall shape; bfmeCallFCB is never referenced by name.
extern "C" void __cdecl __identifier("?j_00043135@@YAXXZ")();
typedef void (BfmeSubFCB::*BfmeCallFCBThunk)(void *value, int kind);
union BfmeCallFCBThunkRef
{
	void *m_thunk;
	BfmeCallFCBThunk m_call;
};

class Rva0020E100Owner
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void finish();

	void forwardAndFinish();

private:
	char m_pad04[0x20 - 0x04];
	void *m_value;
	int m_kind;
};

void Rva0020E100Owner::forwardAndFinish()
{
	BfmeSubFCB *helper = *reinterpret_cast<BfmeSubFCB **>(reinterpret_cast<char *>(this) - 8);
	BfmeCallFCBThunkRef callFCB;
	callFCB.m_thunk = (void *)&__identifier("?j_00043135@@YAXXZ");
	(helper->*callFCB.m_call)(m_value, m_kind);
	finish();
}
