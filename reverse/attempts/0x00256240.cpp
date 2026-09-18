// ?onDie@UpgradeDie@@UAEXPBVDamageInfo@@@Z
// partial score=0.95 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class DamageInfo;
class UpgradeTemplate;

typedef int ObjectID;

class AsciiString
{
private:
	char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	class Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData;
	class Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void dieModuleInterfaceAnchor();
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

class DieMuxData
{
public:
	bool isDieApplicable( const class Object *object, const DamageInfo *damageInfo ) const;
};

class DieModuleData
{
public:
	const DieMuxData *getDieMuxData() const
	{
		return reinterpret_cast<const DieMuxData *>(
			reinterpret_cast<const char *>(this) + 8);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	const DieModuleData *getDieModuleData() const
	{
		return reinterpret_cast<const DieModuleData *>(getModuleData());
	}

	bool isDieApplicable( const DamageInfo *damageInfo ) const
	{
		return getDieModuleData()->getDieMuxData()->isDieApplicable(getObject(), damageInfo);
	}
};

class UpgradeDieModuleData : public DieModuleData
{
private:
	char m_data[0x34];

public:
	AsciiString m_upgradeName;
};

class Object
{
private:
	char m_data[0x78];

public:
	ObjectID m_producerID;

	ObjectID getProducerID() const { return m_producerID; }
	bool hasUpgrade( const UpgradeTemplate *upgrade ) const;
	void removeUpgrade( const UpgradeTemplate *upgrade );
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade( const AsciiString &name ) const;
};

extern GameLogic *TheGameLogic;
extern UpgradeCenter *TheUpgradeCenter;

class UpgradeDie : public DieModule
{
public:
	virtual void onDie( const DamageInfo *damageInfo );

	const UpgradeDieModuleData *getUpgradeDieModuleData() const
	{
		return reinterpret_cast<const UpgradeDieModuleData *>(getModuleData());
	}
};

// ?onDie@UpgradeDie@@UAEXPBVDamageInfo@@@Z
// Retail 0x00256240. UpgradeDie's vtable, the UpgradeToRemove field, and the
// adjacent UpgradeDie destructor establish this callback's identity.
void UpgradeDie::onDie( const DamageInfo *damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;

	Object *producer = TheGameLogic->findObjectByID(getObject()->getProducerID());
	if (producer)
	{
		const UpgradeTemplate *upgrade =
			TheUpgradeCenter->findUpgrade(getUpgradeDieModuleData()->m_upgradeName);
		if (upgrade && producer->hasUpgrade(upgrade))
			producer->removeUpgrade(upgrade);
	}
}
