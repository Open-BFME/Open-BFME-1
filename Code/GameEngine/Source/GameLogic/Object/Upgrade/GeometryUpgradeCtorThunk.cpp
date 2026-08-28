// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
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

protected:
	AsciiString m_upgradeName;					///< retail this+0x1C
};

// ??0GeometryUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
GeometryUpgrade::GeometryUpgrade(Thing *thing, const ModuleData *moduleData)
	: GeometryUpgradeBase(thing, moduleData)
{
	m_upgradeName.clear();
}
