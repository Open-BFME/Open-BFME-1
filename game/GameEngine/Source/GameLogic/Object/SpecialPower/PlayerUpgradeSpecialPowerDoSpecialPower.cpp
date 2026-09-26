// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// PlayerUpgradeSpecialPower::doSpecialPower, retail RVA 0x00264100.
//
// Identity: PlayerUpgradeSpecialPower's matched constructor (0x00263F50)
// stores vtable 0x010B6558 at +0x10; slot 11 of that SpecialPowerModuleInterface
// vtable reaches this body (ILT 0x0001C45E) and slot 16 is startPowerRecharge
// (ILT 0x0000DC5B).  `this` is the interface sub-object, so the Module base is
// at -0x10 (+4 module data, +8 object).  The module data's vector<AsciiString>
// sits at +0x210 (PlayerUpgradeSpecialPowerModuleDataCtorThunk.cpp).
//
// The loop body is upstream's grant-upgrade shape
// (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/
// Object/Create/GrantUpgradeCreate.cpp:125): a missing template returns early
// (retail's je skips finishSpecialPower and lands on the vector destructor),
// and a player upgrade is granted complete.  The real
// Module/ObjectModule/BehaviorModule/SpecialPowerModule hierarchy, rather than
// a flattened `this - 0x10` view, is what puts the startPowerRecharge vtable
// temporary in EAX.

#include <vector>

#include "ascii_string.h"

typedef unsigned int UnsignedInt;

enum UpgradeType
{
	UPGRADE_TYPE_PLAYER = 0
};

enum UpgradeStatusType
{
	UPGRADE_STATUS_COMPLETE = 2
};

class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType() const { return m_type; }

private:
	void *m_vtable;
	UpgradeType m_type; // +0x4
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class Upgrade;

class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status);
};

class Object
{
public:
	Player *getControllingPlayer() const;

	char m_pad00[0x1a4];
	UnsignedInt m_disabledMask; // +0x1a4
};

class PlayerUpgradeSpecialPowerModuleData
{
public:
	char m_pad00[0x210];
	_STL::vector<AsciiString> m_upgradeNames; // +0x210
};

class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	virtual ~Module();

	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	const ModuleData *m_moduleData; // +0x4
};

class ObjectModule : public Module
{
public:
	Object *getObject() const { return m_object; }

private:
	Object *m_object; // +0x8
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// vptrs at +0x0 and +0xC, per PlayerUpgradeSpecialPower's constructor (0x00263F50)
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

// vptr at +0x10 (vtable 0x010B6558): slot 11 doSpecialPower, slot 16 startPowerRecharge
class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void doSpecialPower(UnsignedInt commandOptions) = 0;
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void startPowerRecharge() = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	void finishSpecialPower(UnsignedInt arg);
};

class PlayerUpgradeSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(UnsignedInt commandOptions);

private:
	const PlayerUpgradeSpecialPowerModuleData *getPlayerUpgradeSpecialPowerModuleData() const
	{
		return (const PlayerUpgradeSpecialPowerModuleData *)getModuleData();
	}
};

// ?doSpecialPower@PlayerUpgradeSpecialPower@@UAEXI@Z
void PlayerUpgradeSpecialPower::doSpecialPower(UnsignedInt)
{
	if (getObject()->m_disabledMask != 0)
		return;

	startPowerRecharge();
	_STL::vector<AsciiString> upgradeNames = getPlayerUpgradeSpecialPowerModuleData()->m_upgradeNames;
	for (UnsignedInt i = 0; i < upgradeNames.size(); ++i)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeNames[i]);
		if (upgrade == 0)
			return;
		if (upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER)
		{
			Player *player = getObject()->getControllingPlayer();
			player->addUpgrade(upgrade, UPGRADE_STATUS_COMPLETE);
		}
	}

	finishSpecialPower(0);
}
