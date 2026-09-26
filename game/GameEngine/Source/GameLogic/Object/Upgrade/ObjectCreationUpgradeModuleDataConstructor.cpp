// cl: /DNDEBUG /MD /EHsc

// Trailing members are written in retail's store order, which is not offset
// order: 0xa0 lands before 0x98 and 0x9c, and the -1 at 0x94 comes last.

// The three strings destroy their buffers through retail 0x00887940.
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData() {}
	virtual void moduleDataAnchor();

	int m_moduleTagNameKey;
};

class UpgradeModuleDataSub
{
public:
	// Retail emits no cleanup frame around this call in the owner constructor.
	__declspec(nothrow) UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_body[0x78 - 0x10];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h
class ObjectCreationUpgradeModuleData : public ModuleData
{
public:
	ObjectCreationUpgradeModuleData();
	virtual ~ObjectCreationUpgradeModuleData();

	virtual void moduleDataAnchor();

	// Named factory 0x0011D4A0 passes ILT 0x00009D59 -> 0x002D6D60.
	// Its table RVA 0x00CCD6C0 names UpgradeObject/+8, Delay/+c,
	// RemoveUpgrade/+78, GrantUpgrade/+7c, ThingToSpawn/+80, Offset/+84,
	// DestroyWhenSold/+90 and FadeInTime/+a0. Keep Delay and Offset as
	// raw four-byte storage: both are floats;
	// parseCoord3D 0x00853380 writes X/Y/Z to +84/+88/+8c in that order.
	// The custom DeathAnimAndDuration fields +94/+98/+9c remain opaque.
	int m_upgradeObject;
	int m_delay;
	UpgradeModuleDataSub m_10;
	AsciiString m_removeUpgrade;
	AsciiString m_grantUpgrade;
	AsciiString m_thingToSpawn;
	int m_offsetX;
	int m_offsetY;
	int m_offsetZ;
	bool m_destroyWhenSold;
	int m_94;
	int m_98;
	int m_9c;
	int m_fadeInTime;
};

// ??0ObjectCreationUpgradeModuleData@@QAE@XZ
ObjectCreationUpgradeModuleData::ObjectCreationUpgradeModuleData()
	: m_upgradeObject( 0 ), m_delay( 0 )
{
	m_offsetX = 0;
	m_offsetY = 0;
	m_offsetZ = 0;
	m_destroyWhenSold = false;
	m_fadeInTime = 0;
	m_98 = 0;
	m_9c = 0;
	m_94 = -1;
}

// ??1ObjectCreationUpgradeModuleData@@UAE@XZ
class __declspec(novtable) ObjectCreationUpgradeModuleData;

ObjectCreationUpgradeModuleData::~ObjectCreationUpgradeModuleData()
{
}
