// cl: /DNDEBUG /MD /EHsc

// No EH frame here, so nothing in this object is destructible -- neither the
// base nor the UpgradeModuleDataSub member gets a declared destructor.
//
// Trailing members are written in retail's store order, which is not offset
// order: 0xa0 lands before 0x98 and 0x9c, and the -1 at 0x94 comes last.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();

	int m_04;
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

	int m_08;
	int m_0c;
	UpgradeModuleDataSub m_10;
	int m_78;
	int m_7c;
	int m_80;
	int m_84;
	int m_88;
	int m_8c;
	bool m_90;
	int m_94;
	int m_98;
	int m_9c;
	int m_a0;
};

// ??0ObjectCreationUpgradeModuleData@@QAE@XZ
ObjectCreationUpgradeModuleData::ObjectCreationUpgradeModuleData()
	: m_08( 0 ), m_0c( 0 )
{
	m_78 = 0;
	m_7c = 0;
	m_80 = 0;
	m_84 = 0;
	m_88 = 0;
	m_8c = 0;
	m_90 = false;
	m_a0 = 0;
	m_98 = 0;
	m_9c = 0;
	m_94 = -1;
}
