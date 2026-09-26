// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef bool Bool;

class Rva000C9C50
{
public:
	void dec();
};

class Gen_000c9c30
{
public:
	int m();
};

class Rva000C9C60DwordSlot
{
public:
	void set(int value);
};

class Gen_000D5E90
{
public:
	void bfmeRemove(void *owner, void *extra);
};

union PlayerMethods
{
	Rva000C9C50 m_counter;
	Gen_000c9c30 m_count;
	Rva000C9C60DwordSlot m_entry;
	Gen_000D5E90 m_entries;
};

class Player
{
public:
	PlayerMethods m_methods;
};

class EntryVector
{
public:
	unsigned int *begin() const { return m_begin; }
	unsigned int *end() const { return m_end; }
	int size() const { return static_cast<int>(m_end - m_begin); }
	unsigned int &operator[](int index) const { return m_begin[index]; }

private:
	unsigned int *m_begin;
	unsigned int *m_end;
};

class ModuleData
{
public:
	unsigned char m_padding[0x74];
	EntryVector m_entries;
	unsigned char m_paddingAfterEntries[4];
	Bool m_usePlayerEntries;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_padding[0x74];
	void *m_entryKey;
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")

class ObjectModule
{
public:
	virtual void objectModuleAnchor() = 0;

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
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
	virtual Bool attemptUpgrade() = 0;
	virtual Bool wouldUpgrade() const = 0;
	virtual Bool resetUpgrade() = 0;
	virtual Bool isSubObjectsUpgrade() = 0;
	virtual void forceRefreshUpgrade() = 0;
	virtual void postUpgradeCheck() = 0;
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool) = 0;
	virtual void upgradeImplementation() = 0;
	virtual void getUpgradeActivationMasks() const = 0;
	virtual void performUpgradeFX() = 0;
	virtual Bool requiresAllActivationUpgrades() const = 0;
	virtual void upgradeMuxSlot13() = 0;
	virtual void upgradeMuxSlot14() = 0;
	virtual void upgradeMuxSlot15() = 0;
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

class CostModifierUpgrade : public UpgradeModule
{
	protected:
	virtual void upgradeRemovalImplementation();
};

template <class T>
inline const T &max(const T &left, const T &right)
{
	return left > right ? left : right;
}

template <class T>
inline const T &min(const T &left, const T &right)
{
	return left < right ? left : right;
}

// ?upgradeRemovalImplementation@CostModifierUpgrade@@MAEXXZ
void CostModifierUpgrade::upgradeRemovalImplementation()
{
	if (!isAlreadyUpgraded())
		return;

	const ModuleData *moduleData = getModuleData();
	if (moduleData->m_usePlayerEntries)
	{
		Player *player = getObject()->getControllingPlayer();
		if (player == 0)
			return;
		player->m_methods.m_counter.dec();
		int entry = player->m_methods.m_count.m() - 1;
		int zero = 0;
		entry = max(entry, zero);

		int lastEntry = moduleData->m_entries.size() - 1;
		entry = min(entry, lastEntry);

		unsigned int *entries = moduleData->m_entries.begin();
		unsigned int selectedEntry = entries[entry];
		player->m_methods.m_entry.set(selectedEntry);
	}
	else
	{
		Player *player = getObject()->getControllingPlayer();
		if (player != 0)
			player->m_methods.m_entries.bfmeRemove(
				const_cast<ModuleData *>(moduleData), getObject()->m_entryKey);
		setUpgradeExecuted(false);
	}
}
