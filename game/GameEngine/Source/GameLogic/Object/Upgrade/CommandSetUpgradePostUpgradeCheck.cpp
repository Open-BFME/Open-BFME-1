// cl: /DNDEBUG /MD /EHsc
//
// CommandSetUpgrade's slot 6 in the UpgradeMux secondary vtable.  The
// constructor at 0x002D41A0 installs that table at complete-object +0x10, and
// Object::updateUpgradeModules calls the same slot with no explicit argument.
// BFME therefore differs from the later Zero Hour declaration here: this body
// builds the current player/object mask itself, after running the neighboring
// per-class removal hook, and sends that mask through attemptUpgrade.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object;

struct UpgradeMaskType
{
	UnsignedInt m_bits[6];

	UpgradeMaskType()
	{
	}

	__forceinline void set(const UpgradeMaskType &other)
	{
		m_bits[0] |= other.m_bits[0];
		m_bits[1] |= other.m_bits[1];
		m_bits[2] |= other.m_bits[2];
		m_bits[3] |= other.m_bits[3];
		m_bits[4] |= other.m_bits[4];
		m_bits[5] |= other.m_bits[5];
	}

	__forceinline void setObjectCompletedUpgrades(const Object &object);
};

class Player
{
public:
	UpgradeMaskType getCompletedUpgradeMask() const
	{
		return m_upgradesCompleted;
	}

private:
	unsigned char m_unmodelled_000[0x8c];
	UpgradeMaskType m_upgradesCompleted;
};

class Object
{
public:
	Player *getControllingPlayer() const;

	const UpgradeMaskType &getObjectCompletedUpgradeMask() const
	{
		return m_objectUpgradesCompleted;
	}

private:
	friend struct UpgradeMaskType;
	unsigned char m_unmodelled_000[0x224];
	UpgradeMaskType m_objectUpgradesCompleted;
};

// Local convenience for the six inlined ORs. MSVC also emits an unreferenced
// 72-byte copy; that separate helper has no matching retail body.
// ?setObjectCompletedUpgrades@UpgradeMaskType@@QAEXABVObject@@@Z absent-from-retail
__forceinline void UpgradeMaskType::setObjectCompletedUpgrades(const Object &object)
{
	m_bits[0] |= object.m_objectUpgradesCompleted.m_bits[0];
	m_bits[1] |= object.m_objectUpgradesCompleted.m_bits[1];
	m_bits[2] |= object.m_objectUpgradesCompleted.m_bits[2];
	m_bits[3] |= object.m_objectUpgradesCompleted.m_bits[3];
	m_bits[4] |= object.m_objectUpgradesCompleted.m_bits[4];
	m_bits[5] |= object.m_objectUpgradesCompleted.m_bits[5];
}

class ModuleData;

class ObjectModule
{
public:
	virtual void objectModuleAnchor() = 0;

protected:
	Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual Bool attemptUpgrade(const UpgradeMaskType &keyMask) = 0;
	virtual Bool wouldUpgrade(const UpgradeMaskType &keyMask) const = 0;
	virtual Bool resetUpgrade(const UpgradeMaskType &keyMask) = 0;
	virtual Bool isSubObjectsUpgrade() = 0;
	virtual void forceRefreshUpgrade() = 0;
	virtual void rva002D43A0PostUpgradeCheck() = 0;
	virtual void upgradeRemovalImplementation() = 0;

private:
	Bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor() = 0;
};

class UpgradeModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
};

class CommandSetUpgrade : public UpgradeModule
{
public:
	virtual void rva002D43A0PostUpgradeCheck();
};

// ?rva002D43A0PostUpgradeCheck@CommandSetUpgrade@@UAEXXZ
void CommandSetUpgrade::rva002D43A0PostUpgradeCheck()
{
	upgradeRemovalImplementation();

	UpgradeMaskType mask(getObject()->getControllingPlayer()->getCompletedUpgradeMask());
	mask.setObjectCompletedUpgrades(*getObject());
	attemptUpgrade(mask);
}
