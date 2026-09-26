// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// BFME's GeometryUpgrade has the four-base UpgradeModule layout independently
// proven by its exact constructor at 0x002D5790.  The most-derived class is
// novtable: retail destroys its AsciiString first, then the inline module bases
// restore their vtables before ObjectModule's out-of-line destructor runs.

#include "PreRTS.h"
#include "Common/AsciiString.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	void *m_moduleData;
	void *m_object;
};

class GeometryUpgradeBehaviorInterface
{
public:
	virtual void behaviorInterfaceAnchor() = 0;
};

class GeometryUpgradeBehaviorModule : public ObjectModule,
	public GeometryUpgradeBehaviorInterface
{
public:
	virtual ~GeometryUpgradeBehaviorModule() {}
};

class GeometryUpgradeMux
{
public:
	virtual void upgradeMuxAnchor() = 0;

private:
	bool m_upgradeExecuted;
};

class GeometryUpgradeModuleInterface
{
public:
	virtual void moduleInterfaceAnchor() = 0;
};

class GeometryUpgradeBase : public GeometryUpgradeBehaviorModule,
	public GeometryUpgradeMux,
	public GeometryUpgradeModuleInterface
{
public:
	virtual ~GeometryUpgradeBase() {}
};

class __declspec(novtable) GeometryUpgrade : public GeometryUpgradeBase
{
public:
	virtual ~GeometryUpgrade();

private:
	AsciiString m_upgradeName;
};

// ??1GeometryUpgrade@@UAE@XZ
GeometryUpgrade::~GeometryUpgrade()
{
}
