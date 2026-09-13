// cl: /DNDEBUG /MD /EHsc
// readable body of ?computeBonus@Weapon@@IBEXPBVObject@@IAAVWeaponBonus@@@Z: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp

// Open-BFME5: Weapon::computeBonus, retail 0x001E2840, 96 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it, and
// Weapon::loadAmmoNow at 0x001E9D60 -- landed in the previous commit -- is one
// of its callers.
//
// The bonus is reset to six 1.0f first, through one register that carries the
// constant for all six stores. Then the object's own bonus mask at +0x2A0 is
// or-ed with the mask the caller passed, and that combined mask is offered to
// two bonus sets in turn: the global one at +0xB94 of TheWritableGlobalData and
// the weapon's own at +0x4A8 of the template at this+4. Either can be absent
// and each is tested on its own.
//
// The reset is a member on the bonus rather than an assignment from a fresh
// one: an assignment builds a temporary in the frame first, which retail has no
// room for.

typedef unsigned int UnsignedInt;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponBonus
{
public:
	void clear()
	{
		m_bfmeA = 1.0f;
		m_bfmeB = 1.0f;
		m_bfmeC = 1.0f;
		m_bfmeD = 1.0f;
		m_bfmeE = 1.0f;
		m_bfmeF = 1.0f;
	}

	Real m_bfmeA, m_bfmeB, m_bfmeC, m_bfmeD, m_bfmeE, m_bfmeF;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponBonusSet
{
public:
	void bfmeApplyBonuses(UnsignedInt mask, WeaponBonus &bonus) const; // ILT 0x0002272D
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_bfmeHead[0x2A0];
	UnsignedInt m_bfmeBonusMask;				// +0x2A0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_bfmeHead[0xB94];
	WeaponBonusSet *m_bfmeBonuses;				// +0xB94
};

extern GlobalData *TheWritableGlobalData;			// 0x012ED5C8

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	char m_bfmeHead[0x4A8];
	WeaponBonusSet *m_bfmeBonuses;				// +0x4A8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
protected:
	void computeBonus(const Object *source, UnsignedInt extra,
			WeaponBonus &bonus) const;

private:
	char m_bfmeHead[0x04];
	WeaponTemplate *m_bfmeTemplate;				// +0x04
};

// ?computeBonus@Weapon@@IBEXPBVObject@@IAAVWeaponBonus@@@Z
void Weapon::computeBonus(const Object *source, UnsignedInt extra,
		WeaponBonus &bonus) const
{
	bonus.clear();

	UnsignedInt mask = source->m_bfmeBonusMask | extra;

	WeaponBonusSet *global = TheWritableGlobalData->m_bfmeBonuses;

	if (global)
		global->bfmeApplyBonuses(mask, bonus);

	WeaponBonusSet *own = m_bfmeTemplate->m_bfmeBonuses;

	if (own)
		own->bfmeApplyBonuses(mask, bonus);
}
