// cl: /DNDEBUG /MD /EHsc
// readable body of ?getAttackRange@Weapon@@QBEMPBVObject@@@Z: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp
// Open-BFME: Weapon::getAttackRange, retail 0x001E2B50, 98 bytes.
//
// The reference's three-line body -- a default WeaponBonus, computeBonus, then
// the template's own getAttackRange -- with two BFME differences the frame
// shows outright.
//
// WeaponBonus has six fields here, not the reference's five: the inlined
// constructor writes 1.0f six times across the whole 0x18-byte local block,
// and there is nothing else in the frame for the extra dword to be.
//
// And WeaponTemplate::getAttackRange takes three arguments rather than the
// bonus alone. The pushes are, in argument order, the source object, the
// bonus, and source+0x38, the object position this tree already reads at that
// offset -- so BFME's range depends on where the shooter is standing.
//
// m_template at this+0x04, leaving +0x00 to the pool object's vptr, is the
// `mov ecx, [esi+4]` that sets up that call.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D { Real x, y, z; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition(void) const { return &m_position; }

private:
	char m_slice_pad[0x38];			// retail this+0x00 .. +0x37, untouched
	Coord3D m_position;			// this+0x38
};

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
class WeaponTemplate
{
public:
	Real getAttackRange(const Object *source, const WeaponBonus &bonus, const Coord3D *sourcePos) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	Real getAttackRange(const Object *source) const;

protected:
	void computeBonus(const Object *source, UnsignedInt extraBonusFlags, WeaponBonus &bonus) const;

private:
	char m_slice_pad[4];			// retail this+0x00, the pool object's vptr
	const WeaponTemplate *m_template;	// this+0x04
};

Real Weapon::getAttackRange(const Object *source) const
{ 
	WeaponBonus bonus;
	computeBonus(source, 0, bonus);
	return m_template->getAttackRange(source, bonus, source->getPosition()); 
}
