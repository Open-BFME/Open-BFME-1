// ?isRva0016FD30RangeAndAngleValid@Rva0016FD30StateView@@QAE_NXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWMath
// Address-derived state view; the class identity remains unproven.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}

	void sub(const Coord3D &that)
	{
		x -= that.x;
		y -= that.y;
		z -= that.z;
	}
};

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

class StateMachine;
class Object;
class Weapon;
class WeaponTemplate;

class StateMachine
{
public:
	unsigned char m_prefix[0x10];
	Object *m_owner;
	Object *getGoalObject();
};

class Thing
{
public:
	unsigned char m_prefix[0x38];
	Coord3D m_cachedPos;
	Real bfmeRelativeAngleTo(const Coord3D *position) const;
};

class Object : public Thing
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
};

class Weapon
{
public:
	unsigned char m_prefix[0x04];
	WeaponTemplate *m_template;
};

class WeaponTemplate
{
public:
	unsigned char m_prefix[0x20];
	Real m_aimDelta;
	Real getUnmodifiedAttackRange() const;
};

struct Rva0016FD30StateView
{
	unsigned char m_prefix[0x1c];
	StateMachine *m_machine;
	Bool isRva0016FD30RangeAndAngleValid();
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentWeapon@Object@@QAEPAVWeapon@@PAW4WeaponSlotType@@@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getUnmodifiedAttackRange@WeaponTemplate@@QBEMXZ=?j_00030f03@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeRelativeAngleTo@Thing@@QBEMPBUCoord3D@@@Z=?j_00049413@@YAXXZ")

Bool Rva0016FD30StateView::isRva0016FD30RangeAndAngleValid()
{
	StateMachine *machine = m_machine;
	Object *owner = machine->m_owner;
	Object *goal = machine->getGoalObject();
	if (!owner || !goal)
		return false;

	Weapon *weapon = owner->getCurrentWeapon(0);
	if (!weapon)
		return false;

	Coord3D delta;
	delta.set(owner->m_cachedPos);
	delta.sub(goal->m_cachedPos);

	Real attackRange = weapon->m_template->getUnmodifiedAttackRange();
	if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <
		attackRange * attackRange)
	{
		Real angleLimit = weapon->m_template->m_aimDelta;
		if (angleLimit < *(const Real *)0x010977F0)
			angleLimit = 0.035f;

		if (owner->bfmeRelativeAngleTo(&goal->m_cachedPos) < angleLimit)
			return true;
	}

	return false;
}
