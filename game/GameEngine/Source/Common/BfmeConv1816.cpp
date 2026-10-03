extern float g_bfmeDefaultBU;

class BfmeItemVM
{
public:
	unsigned char m_bfmeHeadVM[0x10];
	int m_bfmeStateVM;
	unsigned char m_bfmeGapVM[8];
	float m_bfmeValueVM;
};

class BfmeOwnerVM
{
public:
	virtual void bfmeV0VM(void);
	virtual void bfmeV1VM(void);
	virtual void bfmeV2VM(void);
	virtual void bfmeV3VM(void);
	virtual float bfmeComputeVM(void);

	void bfmeClampVM(BfmeItemVM *item);
	// bfmeNotifyVM() is reached through the ILT thunk below, not declared here.
};

// The notify call goes through the five-byte ILT thunk at 0x0003B372, defined
// as ?j_0003b372@@YAXXZ in game/gen_small/thunks_028.cpp (target FUN_00611d40)
// and pinned for ?bfmeNotifyVM@BfmeOwnerVM@@. The thunk declares no argument of
// its own: it jumps with the thiscall `this` in ECX, so the call is spelled
// through a thiscall member pointer of the same shape.
extern void j_0003b372();

typedef void (BfmeOwnerVM::*bfmeNotifyVMThunk)(BfmeItemVM *item);

union BfmeNotifyVMThunkCast
{
	void (__cdecl *freeFunction)(BfmeItemVM *item);
	bfmeNotifyVMThunk memberFunction;
};

void BfmeOwnerVM::bfmeClampVM(BfmeItemVM *item)
{
	if (item->m_bfmeStateVM != 8)
	{
		float limit = bfmeComputeVM() - g_bfmeDefaultBU;

		const float &chosen = item->m_bfmeValueVM < limit ? item->m_bfmeValueVM : limit;

		item->m_bfmeValueVM = chosen;
	}

	BfmeNotifyVMThunkCast cast;
	cast.freeFunction = reinterpret_cast<void (__cdecl *)(BfmeItemVM *)>(&::j_0003b372);
	(this->*cast.memberFunction)(item);
}
