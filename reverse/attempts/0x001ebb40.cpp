// ?releaseWeaponLock@WeaponSet@@QAEXW4WeaponLockType@@@Z
// partial score=0.92 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::releaseWeaponLock, retail 0x001EBB40 size 99.
// Focused TU: WeaponSet.cpp keeps the ZH body (lock word only). BFME also
// looks up the owner via TheGameLogic and clears three model-condition bits
// (0x88/0x89/0x8A) through BitFlags<304>'s three-index ctor.
//
// 99/99B, two thiscall adjacent-swaps remain: lea ecx / push kInit on the
// BitFlags ctor, and mov ecx,edi / push eax on clearModelConditionFlags.

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

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, int idx1, int idx2, int idx3);

private:
	int m_words[10];
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
	WeaponLockType cur = m_curWeaponLockedStatus;
	int none = 0;
	if (cur == (WeaponLockType)none)
		return;
	if (lockType != LOCKED_PERMANENTLY)
	{
		if (lockType != LOCKED_TEMPORARILY)
			return;
		if (cur != lockType)
			return;
	}
	if (obj == (Object *)none)
	{
		m_curWeaponLockedStatus = (WeaponLockType)none;
		return;
	}
	m_curWeaponLockedStatus = (WeaponLockType)none;
	ModelConditionFlags::BogusInitType init = (ModelConditionFlags::BogusInitType)none;
	obj->clearModelConditionFlags(ModelConditionFlags(init, 0x88, 0x89, 0x8A));
}
