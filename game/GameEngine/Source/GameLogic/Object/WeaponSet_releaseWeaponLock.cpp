// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::releaseWeaponLock, retail 0x001EBB40 size 99.
// Zero Hour's body (WeaponSet.cpp) plus BFME's owner lookup: each branch that
// drops the lock also clears model conditions 0x88/0x89/0x8A on the owner.
// Writing the clear once per branch, as the original evidently did, is what
// gives VC7.1's cross-jumped tail retail's ECX-before-last-push call setup;
// a single shared tail swaps both thiscall setups.

enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, int idx1, int idx2, int idx3);

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<304> ModelConditionFlags;

class Object
{
public:
	void clearModelConditionFlags(const ModelConditionFlags &clr);
};

class WeaponSet
{
public:
	void releaseWeaponLock(WeaponLockType lockType);

private:
	char m_pad_00[0x1C];
	WeaponLockType m_curWeaponLockedStatus;
	char m_pad_20[0x34 - 0x20];
	int m_objectId;
};

// ?releaseWeaponLock@WeaponSet@@QAEXW4WeaponLockType@@@Z
void WeaponSet::releaseWeaponLock(WeaponLockType lockType)
{
	Object *obj = TheGameLogic->findObjectByID(m_objectId);
	if (m_curWeaponLockedStatus == NOT_LOCKED)
		return;

	if (lockType == LOCKED_PERMANENTLY)
	{
		m_curWeaponLockedStatus = NOT_LOCKED;
		if (obj)
			obj->clearModelConditionFlags(ModelConditionFlags(ModelConditionFlags::kInit, 0x88, 0x89, 0x8A));
	}
	else if (lockType == LOCKED_TEMPORARILY)
	{
		if (m_curWeaponLockedStatus == LOCKED_TEMPORARILY)
		{
			m_curWeaponLockedStatus = NOT_LOCKED;
			if (obj)
				obj->clearModelConditionFlags(ModelConditionFlags(ModelConditionFlags::kInit, 0x88, 0x89, 0x8A));
		}
	}
}
