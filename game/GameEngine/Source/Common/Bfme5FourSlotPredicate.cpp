// Checks four enabled slots and succeeds when one slot's object accepts the
// supplied value for the owner's current source.

class BfmeFourSlotSource;

class Object;

// BFME's matched Weapon overload at 0x001E8930 has a trailing int slot.
class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *target,
		int extra) const;
};

enum WeaponSlotType {};

// Retail calls 0x3C8E9 -> 0x001EAF90, the matched
// WeaponSet::getWeaponInWeaponSlot (WeaponSet.cpp).
class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType wslot) const;
};

class BfmeFourSlotSource
{
public:
	WeaponSet *bfmeTable(void) { return &m_table; }

	char m_prefix[0x264];
	WeaponSet m_table;
};

class BfmeFourSlotFlags
{
public:
	char m_prefix[0x3c];
	unsigned int m_enabled;
};

class BfmeFourSlotOwner
{
public:
	bool bfmeAnyAccepts(int value);

private:
	char m_prefix[8];
	BfmeFourSlotFlags *m_flags;
	char m_gap[4];
	BfmeFourSlotSource *m_source;
};

// ?bfmeAnyAccepts@BfmeFourSlotOwner@@QAE_NH@Z
bool BfmeFourSlotOwner::bfmeAnyAccepts(int value)
{
	for (int index = 0; index < 4; ++index)
	{
		BfmeFourSlotSource *source = m_source;
		Weapon *entry = source->bfmeTable()->getWeaponInWeaponSlot((WeaponSlotType)index);
		if (entry != 0 &&
			(m_flags->m_enabled & (1 << index)) != 0 &&
			entry->isWithinAttackRange(
				reinterpret_cast<const Object *>(m_source),
				reinterpret_cast<const Object *>(value), 0))
		{
			return true;
		}
	}
	return false;
}
