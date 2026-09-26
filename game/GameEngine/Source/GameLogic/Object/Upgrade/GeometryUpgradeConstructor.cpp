// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: GeometryUpgrade module ctor. BFME-only, no Zero Hour counterpart,
// so the body is read off retail: base call, four most-derived vtbls at
// +0/+0xC/+0x10/+0x18, then the AsciiString at +0x1C default-constructed
// (`mov [ecx],0` is its inline constructor) and cleared.
//
// Interface bases carry __declspec(novtable) so only the most-derived vtbl
// stores remain; the unwind states are 0 for the base subobject and 1 once the
// string is live.
#include "PreRTS.h"
#include "Common/AsciiString.h"

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	virtual ~BehaviorModule();

	unsigned int m_04;
	unsigned int m_08;
};

class __declspec(novtable) GeometryUpgradeIface1
{
public:
	virtual void geometryUpgradeIface1Anchor();
};

class __declspec(novtable) GeometryUpgradeIface2
{
public:
	virtual void geometryUpgradeIface2Anchor();

	unsigned int m_14;
};

class __declspec(novtable) GeometryUpgradeIface3
{
public:
	virtual void geometryUpgradeIface3Anchor();
};

class GeometryUpgradeBase : public BehaviorModule
{
public:
	GeometryUpgradeBase(Thing *thing, const ModuleData *moduleData);
};

class GeometryUpgrade : public GeometryUpgradeBase,
	public GeometryUpgradeIface1,
	public GeometryUpgradeIface2,
	public GeometryUpgradeIface3
{
public:
	GeometryUpgrade(Thing *thing, const ModuleData *moduleData);
	// Complete destructor remains in GeometryUpgradeDestructor.cpp.
	// This declaration emits the exact 0x002D58D0 scalar wrapper, whose
	// call through ILT 0x0001C1D4 reaches the real 0x002D5900 body.
	virtual ~GeometryUpgrade();

protected:
	AsciiString m_upgradeName;					///< retail this+0x1C
};

// ??0GeometryUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
GeometryUpgrade::GeometryUpgrade(Thing *thing, const ModuleData *moduleData)
	: GeometryUpgradeBase(thing, moduleData)
{
	m_upgradeName.clear();
}
