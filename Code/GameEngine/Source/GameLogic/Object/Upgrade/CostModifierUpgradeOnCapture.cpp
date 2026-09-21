// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail 0x002D4850: CostModifierUpgrade::onCapture(Player*, Player*),
// primary-vtable slot 9 (0x010CC5AC +0x24) -- the same behavior-callback
// slot already proven for ?onCapture@Object@@ (slot9, thiscall ret8) and
// ?onCapture@TransportContain@@ (this file copies that file's raw-cast
// style rather than reconstructing full multiple inheritance). The body
// interleaves both halves of the already-landed sibling pair in this same
// directory: the oldOwner half repeats CostModifierUpgradeRemoval.cpp's
// dec/get/clamp/set sequence (and its bfmeRemove + setUpgradeExecuted(false)
// fallback), the newOwner half repeats CostModifierUpgradeImplementation.cpp's
// inc/get/clamp/set sequence (and its bfmeAdd + setUpgradeExecuted(true)
// fallback), gated by the same ModuleData::m_usePlayerEntries flag at +0x80
// those two files already established. isAlreadyUpgraded()/setUpgradeExecuted()
// dispatch through the UpgradeMux vtable at this+0x10, matching those files'
// this-object layout (getModuleData()=this+4, getObject()=this+8).

typedef bool Bool;

class Rva000C9C50 { public: void dec(); };
class Rva000C9C40 { public: void inc(); };
class Gen_000c9c30 { public: int m(); };
class Rva000C9C60DwordSlot { public: void set(int value); };
class Gen_000D5E90
{
public:
	void bfmeAdd(void *owner, void *extra);
	void bfmeRemove(void *owner, void *extra);
};

union PlayerMethods
{
	Rva000C9C50 m_dec;
	Rva000C9C40 m_inc;
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

	int size() const { return static_cast<int>(m_end - m_begin); }

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
	unsigned char m_padding[0x74];
	void *m_entryKey;
};

class UpgradeMuxInterface
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

class CostModifierUpgrade
{
public:
	virtual void onCapture(Player *oldOwner, Player *newOwner);

private:
	const ModuleData *getModuleData() const
	{
		return *(const ModuleData *const *)((const char *)this + 4);
	}

	Object *getObject() const
	{
		return *(Object *const *)((const char *)this + 8);
	}

	UpgradeMuxInterface *getUpgradeMux() const
	{
		return (UpgradeMuxInterface *)((const char *)this + 0x10);
	}
};

// ?onCapture@CostModifierUpgrade@@UAEXPAVPlayer@@0@Z
void CostModifierUpgrade::onCapture(Player *oldOwner, Player *newOwner)
{
	UpgradeMuxInterface *upgradeMux = getUpgradeMux();
	if (!upgradeMux->isAlreadyUpgraded())
		return;

	const ModuleData *moduleData = getModuleData();
	if (moduleData->m_usePlayerEntries)
	{
		if (oldOwner)
		{
			oldOwner->m_methods.m_dec.dec();
			int entry = oldOwner->m_methods.m_count.m() - 1;
			int zero = 0;
			entry = max(entry, zero);

			int lastEntry = moduleData->m_entries.size() - 1;
			entry = min(entry, lastEntry);

			unsigned int selectedEntry = moduleData->m_entries.begin()[entry];
			oldOwner->m_methods.m_entry.set(selectedEntry);
		}

		if (newOwner)
		{
			newOwner->m_methods.m_inc.inc();
			int entry = newOwner->m_methods.m_count.m() - 1;
			int zero = 0;
			entry = max(entry, zero);

			int lastEntry = moduleData->m_entries.size() - 1;
			entry = min(entry, lastEntry);

			unsigned int selectedEntry = moduleData->m_entries.begin()[entry];
			newOwner->m_methods.m_entry.set(selectedEntry);
		}
	}
	else
	{
		if (oldOwner)
		{
			oldOwner->m_methods.m_entries.bfmeRemove(
				const_cast<ModuleData *>(moduleData), getObject()->m_entryKey);
			upgradeMux->setUpgradeExecuted(false);
		}

		if (newOwner)
		{
			newOwner->m_methods.m_entries.bfmeAdd(
				const_cast<ModuleData *>(moduleData), getObject()->m_entryKey);
			upgradeMux->setUpgradeExecuted(true);
		}
	}
}
