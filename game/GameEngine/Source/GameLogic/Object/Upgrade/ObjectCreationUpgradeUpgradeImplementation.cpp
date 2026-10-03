// ObjectCreationUpgrade::upgradeImplementation at retail 0x002D6E60: slot 9 of the UpgradeMux table
// 0x010CD620, reached only through ILT 0x0001E4F7. ObjectCreationUpgrade's registered
// constructor 0x002D6D90 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// This TU's own view of the dword at +0x3C of retail's GameLogic.
// ?TheGameLogic@@3PAVGameLogic@@A -- retail 0x012F0898, defined once in
// GameLogic/System/GameLogic.cpp.  The view below is this TU's layout of it.
class RvaBfmeConv1721GameLogic
{
public:
	unsigned char m_bfmeHeadIS[0x3c];
	int m_bfmeFrameIS;
};

class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeWakeIS
{
public:
	void bfmeSetWakeIS(void *obj, int sleep);

	int m_bfmeWakeDataIS;
};

// Retail calls the ILT thunk at 0x000157DA, owned by game/gen_small/thunks_009.cpp
// as ?j_000157da@@YAXXZ.  It is reached through a member-function pointer so the
// call keeps its thiscall shape; bfmeSetWakeIS is never referenced by name.
extern "C" void __cdecl __identifier("?j_000157da@@YAXXZ")();
typedef void (BfmeWakeIS::*BfmeSetWakeISThunk)(void *obj, int sleep);
union BfmeSetWakeISThunkRef
{
	void *m_thunk;
	BfmeSetWakeISThunk m_call;
};

class BfmeDataIS
{
public:
	unsigned char m_bfmeHeadIS[0xc];
	float m_bfmeDelayIS;
};

class ObjectCreationUpgrade
{
protected:
	virtual void upgradeImplementation();
public:
	unsigned char m_bfmeHeadIS[4]; // +0x04, after the vptr
	BfmeWakeIS m_bfmeWakeIS;
	BfmeDataIS *m_bfmeDataIS;
	void *m_bfmeObjIS;
	unsigned char m_bfmeMidIS[0x14];
	int m_bfmeFrameIS;
	char m_bfmeDoneIS;
};

void ObjectCreationUpgrade::upgradeImplementation()
{
	if (m_bfmeDoneIS)
		return;

	m_bfmeFrameIS = ((RvaBfmeConv1721GameLogic *)TheGameLogic)->m_bfmeFrameIS - (int)(m_bfmeDataIS->m_bfmeDelayIS * -5.0f);
	m_bfmeDoneIS = 1;
	BfmeSetWakeISThunkRef thunk;
	thunk.m_thunk = (void *)&__identifier("?j_000157da@@YAXXZ");
	(m_bfmeWakeIS.*thunk.m_call)(m_bfmeObjIS, 1);
}
