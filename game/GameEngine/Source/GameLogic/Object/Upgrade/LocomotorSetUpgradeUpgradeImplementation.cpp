// LocomotorSetUpgrade::upgradeImplementation at retail 0x002D6290: slot 9 of the UpgradeMux table
// 0x010CCFA8, reached only through ILT 0x0000744B (its VA appears once in the image).
// LocomotorSetUpgrade's registered constructor 0x002D6160 stores that table. Slot 9 is the
// upgradeImplementation call in UpgradeMux::attemptUpgrade (0x002D9AD0).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

class BfmeZ1034
{
public:
	char m_bfmeUnused;
};

// Retail calls the ILT thunk at 0x00016DF1, owned by game/gen_small/thunks_010.cpp
// as ?j_00016df1@@YAXXZ (its target, 0x0026EC60, has no ledger row of its own).
// The call is reached through a member-function pointer so it keeps its
// thiscall shape; bfmeSet1034 is never referenced by name.
extern "C" void __cdecl __identifier("?j_00016df1@@YAXXZ")();
typedef void (BfmeZ1034::*BfmeSet1034Thunk)(char on);
union BfmeSet1034ThunkRef
{
	void *m_thunk;
	BfmeSet1034Thunk m_call;
};

struct BfmeW1034
{
	char m_bfmePad[0x204];
	BfmeZ1034 *m_bfmeZ;
};

struct BfmeV1034
{
	char m_bfmePad[0x70];
	char m_bfmeFlag;
};

class LocomotorSetUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void LocomotorSetUpgrade::upgradeImplementation()
{
	BfmeZ1034 *z = (*(BfmeW1034 **)((char *)this - 8))->m_bfmeZ;

	if (z != 0)
	{
		BfmeSet1034ThunkRef set;
		set.m_thunk = (void *)&__identifier("?j_00016df1@@YAXXZ");
		(z->*set.m_call)((char)((*(BfmeV1034 **)((char *)this - 0xc))->m_bfmeFlag == 0));
	}
}
