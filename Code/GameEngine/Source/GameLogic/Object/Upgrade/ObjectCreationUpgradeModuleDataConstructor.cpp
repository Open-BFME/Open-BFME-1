// cl: /DNDEBUG /MD /EHsc

// Retail has no constructor EH frame. This raw initialization view declares
// only the required constructors; teardown is owned by the separate destructor.
//
// Trailing members are written in retail's store order, which is not offset
// order: 0xa0 lands before 0x98 and 0x9c, and the -1 at 0x94 comes last.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();

	int m_moduleTagNameKey;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	unsigned char m_body[0x78 - 0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h
class ObjectCreationUpgradeModuleData : public ModuleData
{
public:
	ObjectCreationUpgradeModuleData();

	virtual void moduleDataAnchor();

	// Named factory 0x0011D4A0 passes ILT 0x00009D59 -> 0x002D6D60.
	// Its table RVA 0x00CCD6C0 names UpgradeObject/+8, Delay/+c,
	// RemoveUpgrade/+78, GrantUpgrade/+7c, ThingToSpawn/+80, Offset/+84,
	// DestroyWhenSold/+90 and FadeInTime/+a0. Keep this constructor
	// view as raw four-byte storage: Delay and Offset are floats;
	// parseCoord3D 0x00853380 writes X/Y/Z to +84/+88/+8c in that order.
	// The custom DeathAnimAndDuration fields +94/+98/+9c remain opaque.
	int m_upgradeObject;
	int m_delay;
	UpgradeModuleDataSub m_10;
	int m_removeUpgrade;
	int m_grantUpgrade;
	int m_thingToSpawn;
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
	m_removeUpgrade = 0;
	m_grantUpgrade = 0;
	m_thingToSpawn = 0;
	m_offsetX = 0;
	m_offsetY = 0;
	m_offsetZ = 0;
	m_destroyWhenSold = false;
	m_fadeInTime = 0;
	m_98 = 0;
	m_9c = 0;
	m_94 = -1;
}
