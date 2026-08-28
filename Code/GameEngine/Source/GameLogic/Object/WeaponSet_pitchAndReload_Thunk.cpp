// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::isAnyWithinTargetPitch and WeaponSet::reloadAllAmmo,
// retail 0x001EADC0 and 0x001EAE20.
//
// Both Zero Hour bodies unchanged. They are here rather than in WeaponSet.cpp
// for the reason WeaponSet_isOutOfAmmo_Thunk.cpp already records: each loop runs
// to 4 where ZH's WEAPONSLOT_COUNT is 3, and correcting that constant is a
// header change that widens m_weapons[WEAPONSLOT_COUNT] from twelve bytes to
// sixteen -- moving everything the nine matched rows in WeaponSet.cpp read after
// it. WeaponSet.cpp keeps both bodies as present-unmatched, the same way it
// keeps isOutOfAmmo.
//
// Two offsets come straight off the bytes: m_weapons at +0x08 (`lea esi,[ecx+8]`
// in both), and m_hasPitchLimit at +0x2c (`mov al,[ecx+0x2c]`, the early-out).
//
// The three callees are pinned at their incremental-link thunks in
// reverse/symbols.csv. loadAmmoNow and reloadAmmo are worth a note because the
// two bodies they front are byte-identical apart from one immediate: 0x001E9D60
// and 0x001E9DE0 both build a WeaponBonus, call computeBonus, and tail into
// reloadWithBonus -- one pushing 1 for its last argument and the other pushing
// 0. That is `reloadWithBonus(sourceObj, bonus, true)` against
// `reloadWithBonus(sourceObj, bonus, false)`, so 0x001E9D60 is loadAmmoNow and
// 0x001E9DE0 is reloadAmmo, independently of what this call site assumes.

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	bool isWithinTargetPitch(const Object *source, const Object *victim) const;	///< ILT 0x00005533
	void loadAmmoNow(const Object *sourceObj);									///< ILT 0x0000FED4
	void reloadAmmo(const Object *sourceObj);									///< ILT 0x00033C03
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponSet
{
public:
	void reloadAllAmmo(const Object *obj, bool now);

private:
	bool isAnyWithinTargetPitch(const Object *obj, const Object *victim) const;

	char m_unreconstructed_00[8];
	Weapon *m_weapons[4];					///< retail this+0x08; BFME has four slots
	char m_unreconstructed_18[0x2c - 0x18];
	bool m_hasPitchLimit;					///< retail this+0x2c
};

// ?isAnyWithinTargetPitch@WeaponSet@@ABE_NPBVObject@@0@Z
bool WeaponSet::isAnyWithinTargetPitch(const Object *obj, const Object *victim) const
{
	if (!m_hasPitchLimit)
		return true;

	for( int i = 0; i < 4;	i++ )
	{
		const Weapon* weapon = m_weapons[ i ];
		if (weapon && weapon->isWithinTargetPitch(obj, victim))
		{
			return true;
		}
	}
	return false;
}

// ?reloadAllAmmo@WeaponSet@@QAEXPBVObject@@_N@Z
void WeaponSet::reloadAllAmmo(const Object *obj, bool now)
{
	for( int i = 0; i < 4;	i++ )
	{
		Weapon* weapon = m_weapons[i];
		if (weapon != 0)
		{
			if (now)
				weapon->loadAmmoNow(obj);
			else
				weapon->reloadAmmo(obj);
		}
	}
}
