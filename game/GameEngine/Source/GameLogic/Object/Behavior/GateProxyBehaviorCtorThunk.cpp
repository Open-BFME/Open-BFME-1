// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "GameLogic/Module/UpdateModule.h"

// GateProxyBehavior is a BFME-only module whose original header is not in the
// vendored Generals tree.  The factory registration names it directly, and its
// retail constructor calls the GateOpenAndCloseBehavior base constructor.  Keep
// the recovered ABI layout local to this TU until the module header is restored.
class __declspec(novtable) GateOpenAndCloseBehavior : public UpdateModule
{
public:
	GateOpenAndCloseBehavior(Thing *, const ModuleData *);
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;

private:
	unsigned char m_unrecoveredFields[0x2c];
};

class GateProxyBehavior : public GateOpenAndCloseBehavior
{
public:
	GateProxyBehavior(Thing *, const ModuleData *);
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;

private:
	void *m_gateProxy;
};

// ??0GateProxyBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
GateProxyBehavior::GateProxyBehavior(Thing *thing, const ModuleData *moduleData)
	: GateOpenAndCloseBehavior(thing, moduleData), m_gateProxy(0)
{
}
