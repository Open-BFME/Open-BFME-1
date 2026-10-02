// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/gameclientxfer /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "PreRTS.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"

struct BfmeObjEVB
{
	virtual void bfmeV0();
	virtual void *bfmeGet1EVB();
	virtual void bfmeRun2EVB();
	virtual void bfmeRun3EVB();
};

// ILTs 0x00042424, 0x0001F253 and 0x00010424 reach the canonical tower,
// object-lookup and bridge helpers. Keep the existing local virtual view.

void __stdcall bfmeGoEVBa(void *a)
{
	if (!a)
		return;
	BfmeObjEVB *o = reinterpret_cast<BfmeObjEVB *>(
		BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(static_cast<Object *>(a)));
	if (!o)
		return;
	Object *p = TheGameLogic->findObjectByID(reinterpret_cast<int>(o->bfmeGet1EVB()));
	if (!p)
		return;
	BfmeObjEVB *q = reinterpret_cast<BfmeObjEVB *>(
		BridgeBehavior::getBridgeBehaviorInterfaceFromObject(p));
	if (!q)
		return;
	q->bfmeRun3EVB();
}

void __stdcall bfmeGoEVBb(void *a)
{
	if (!a)
		return;
	BfmeObjEVB *o = reinterpret_cast<BfmeObjEVB *>(
		BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(static_cast<Object *>(a)));
	if (!o)
		return;
	Object *p = TheGameLogic->findObjectByID(reinterpret_cast<int>(o->bfmeGet1EVB()));
	if (!p)
		return;
	BfmeObjEVB *q = reinterpret_cast<BfmeObjEVB *>(
		BridgeBehavior::getBridgeBehaviorInterfaceFromObject(p));
	if (!q)
		return;
	q->bfmeRun2EVB();
}

void __stdcall bfmeGoEVBc(void *a)
{
	if (!a)
		return;
	BfmeObjEVB *o = reinterpret_cast<BfmeObjEVB *>(
		BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(static_cast<Object *>(a)));
	if (!o)
		return;
	Object *p = TheGameLogic->findObjectByID(reinterpret_cast<int>(o->bfmeGet1EVB()));
	if (!p)
		return;
	BfmeObjEVB *q = reinterpret_cast<BfmeObjEVB *>(
		BridgeBehavior::getBridgeBehaviorInterfaceFromObject(p));
	if (!q)
		return;
	q->bfmeRun3EVB();
}
