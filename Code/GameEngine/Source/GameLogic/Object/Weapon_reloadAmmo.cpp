// cl: /DNDEBUG /MD /EHsc
// readable body of ?reloadAmmo@Weapon@@QAEXPBVObject@@@Z: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp
// Open-BFME: Weapon::reloadAmmo, retail 0x001E9DE0, 95 bytes.
//
// The reference's three lines: a default WeaponBonus, computeBonus, then
// reloadWithBonus. Nearly all of it is the bonus block -- the same six 1.0f
// fields Weapon_getAttackRange.cpp measured, filling the whole 0x18-byte
// local.
//
// reloadWithBonus takes the source object, the bonus by reference and a false,
// in that order.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponBonus
{
public:
	enum Field
	{
		DAMAGE = 0,
		RADIUS,
		RANGE,
		RATE_OF_FIRE,
		PRE_ATTACK,
		BFME_SIXTH_FIELD,

		FIELD_COUNT			// keep last
	};

	WeaponBonus()
	{
		clear();
	}

	inline void clear()
	{
		for (int i = 0; i < FIELD_COUNT; ++i)
			m_field[i] = 1.0f;
	}

private:
	Real m_field[FIELD_COUNT];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	void reloadAmmo(const Object *sourceObj);

protected:
	void computeBonus(const Object *source, UnsignedInt extraBonusFlags, WeaponBonus &bonus) const;	// ILT 0x00024591
	void reloadWithBonus(const Object *sourceObj, const WeaponBonus &bonus, Bool loadInstantly);	// ILT 0x0003A0DA
};

void Weapon::reloadAmmo(const Object *sourceObj)
{

	WeaponBonus bonus;
	computeBonus(sourceObj, 0, bonus);
	reloadWithBonus(sourceObj, bonus, false);
}
