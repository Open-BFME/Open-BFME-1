// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// BFME's GeometryUpgrade has the four-base UpgradeModule layout independently
// proven by its exact constructor at 0x002D5790.  The most-derived class is
// novtable: retail destroys its AsciiString first, then the inline module bases
// restore their vtables before ObjectModule's out-of-line destructor runs.

#include "PreRTS.h"
#include "Common/AsciiString.h"

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
