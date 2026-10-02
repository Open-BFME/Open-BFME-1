// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameLogic/Module/UpdateModule.h"

// Registered PartTheHeavensUpdate update receiver at complete-object +0x10.
// Existing view spellings are retained; no member/helper identity is inferred.
// Identity: targets/game/reverse/identity_evidence/update-slot0.md.

class BfmePrimaryFV
{
public:
	void bfmeAdvanceFV(int delta);
};

class DecalCreate00299BB0
{
public:
	void create();
};

class BfmeLogicFV
{
public:
	unsigned char m_bfmeHeadFV[0x3c];
	int m_bfmeFrameFV;
};

class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeSecondFV
{
public:
	unsigned char m_bfmeHeadFV[0x10];
	int m_bfmeStampFV;
};

class PartTheHeavensUpdate
{
public:
	virtual UpdateSleepTime update();
};

UpdateSleepTime PartTheHeavensUpdate::update()
{
	BfmeSecondFV *state = reinterpret_cast<BfmeSecondFV *>(this);
	char *base = (char *)this;

	if (*(void **)(base - 0xc) == 0)
		return UPDATE_SLEEP_FOREVER;

	int delta = ((BfmeLogicFV *)TheGameLogic)->m_bfmeFrameFV - state->m_bfmeStampFV;

	if (delta == 0)
		((DecalCreate00299BB0 *)(base - 0x10))->create();

	((BfmePrimaryFV *)(base - 0x10))->bfmeAdvanceFV(delta);
	return UPDATE_SLEEP_NONE;
}
