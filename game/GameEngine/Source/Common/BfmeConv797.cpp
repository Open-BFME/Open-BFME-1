extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();

class BfmeUiDZD
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeV36();
	virtual void bfmeV37();
	virtual void bfmeV38();
	virtual void bfmeV39();
	virtual void bfmeV40();
	virtual void bfmeV41();
	virtual void bfmeV42();
	virtual bool bfmeAskDZD();
};

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

struct BfmeThingDZD
{
	void bfmeGoDZD(void *unused);
	unsigned char m_bfmeHead[0x1c0];
	unsigned int m_bfmeT;
};

// Retail calls the ILT thunk at 0x00022999, owned by game/gen_small/thunks_016.cpp
// as ?j_00022999@@YAXXZ (its target, 0x0093FC00, has no ledger row of its own).
// The call is reached through a member-function pointer so it keeps its
// thiscall shape; bfmeDoDZD is never referenced by name.
extern "C" void __cdecl __identifier("?j_00022999@@YAXXZ")();
typedef void (BfmeThingDZD::*BfmeDoDZDThunk)();
union BfmeDoDZDThunkRef
{
	void *m_thunk;
	BfmeDoDZDThunk m_call;
};

void BfmeThingDZD::bfmeGoDZD(void *unused)
{
	if (reinterpret_cast<BfmeUiDZD *>(TheGameSpyInfo)->bfmeAskDZD())
	{
		BfmeDoDZDThunkRef doDZD;
		doDZD.m_thunk = (void *)&__identifier("?j_00022999@@YAXXZ");
		(this->*doDZD.m_call)();
		m_bfmeT = timeGetTime();
	}
}
