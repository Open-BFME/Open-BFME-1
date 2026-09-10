// ?bfmePostClosest@Object@@QAEPAV1@PBV1@_N@Z
// partial score=0.8 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// BFME attack-area post-filter, retail 0x001C70C0 (254 bytes).
//
// AIAttackAreaState::update and AIAttackState::onEnter both call this body
// through the 0x000051BE ILT after an attack-area query has identified a
// horde target.  Their call shape establishes a thiscall returning Object *
// with (const Object *, Bool) arguments.  The body walks to the outermost
// containing object whose containment module exposes the horde view, then
// asks that view's +0x48 slot to select a member using the owner's position
// and current attack range.

typedef bool Bool;
typedef float Real;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

class HordeContainInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual Object *queryAt48(Bool unknown, const Coord3D *position,
		Real range) = 0;
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class BfmeLeechRangeTemplate
{
public:
	Bool isLeechRangeWeapon() const;
};

class BfmeAttackRangeWeapon
{
public:
	Real getAttackRange(const Object *owner) const;
};

class Weapon
{
public:
	char m_unmodelled_00[4];
	BfmeLeechRangeTemplate *m_template;
};

// The three calls below are existing BFME ILT thunks.  Member-pointer casts
// preserve their thiscall ABI while keeping their targets in the ordinary
// symbol map: 0x0003251F is Object::isKindOf, 0x00028F74 is the weapon-template
// leech test, and 0x0002E631 is Weapon::getAttackRange(Object const *).
extern void j_0003251f();
extern void j_00028f74();
extern void j_0002e631();

struct BfmeKindOfCall
{
	Bool call(Int kind);
};

static __forceinline Bool bfmeIsKindOf(const Object *object, Int kind)
{
	typedef Bool (BfmeKindOfCall::*Function)(Int);
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_0003251f;
	return (reinterpret_cast<BfmeKindOfCall *>(const_cast<Object *>(object))->*fn.member)(kind);
}

static __forceinline Bool bfmeIsLeechRangeWeapon(
	const BfmeLeechRangeTemplate *object)
{
	typedef Bool (BfmeLeechRangeTemplate::*Function)() const;
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_00028f74;
	return (object->*fn.member)();
}

static __forceinline Real bfmeGetAttackRange(
	const BfmeAttackRangeWeapon *weapon, const Object *owner)
{
	typedef Real (BfmeAttackRangeWeapon::*Function)(const Object *) const;
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_0002e631;
	return (weapon->*fn.member)(owner);
}

// The Object fields used here are fixed by matched BFME Object queries and by
// the two named callers above.  This TU intentionally models only the fields
// touched by this body.
class Object
{
public:
	Object *bfmePostClosest(const Object *owner, Bool add);

private:
	char m_unmodelled_00[0x38];
	Coord3D m_position;
	char m_unmodelled_44[0x1FC - 0x44];
	ContainModuleInterface *m_contain;
	char m_unmodelled_200[0x214 - 0x200];
	Object *m_containedBy;
	char m_unmodelled_218[0x26C - 0x218];
	Weapon *m_weapons[4];
	Int m_currentWeaponSlot;
	char m_unmodelled_280[4];
	void *m_currentWeaponTemplateSet;
};

// ?bfmePostClosest@Object@@QAEPAV1@PBV1@_N@Z
Object *Object::bfmePostClosest(const Object *owner, Bool add)
{
	Object *object = this;
	if (owner == 0)
		return 0;

	if (object->m_containedBy)
	{
		register Object **containedBy = &object->m_containedBy;
		do
		{
			Object *parent = *containedBy;
			ContainModuleInterface *contain = parent->m_contain;
			if (contain == 0 || contain->getHordeContainInterface() == 0)
				break;
			object = parent;
			containedBy = &object->m_containedBy;
		}
		while (*containedBy);
	}

	ContainModuleInterface *contain = object->m_contain;
	if (contain == 0)
		return this;
	HordeContainInterface *horde = contain->getHordeContainInterface();
	if (horde == 0)
		return this;

	Real range = 0.0f;
	if (add)
		range = 0.0f;
	else
		range = 99999.0f;
	if (!bfmeIsKindOf(owner, 0x6c) && owner->m_currentWeaponTemplateSet != 0)
	{
		Weapon *weapon = owner->m_weapons[owner->m_currentWeaponSlot];
		if (weapon != 0 && !bfmeIsLeechRangeWeapon(weapon->m_template))
			range = bfmeGetAttackRange(
				reinterpret_cast<const BfmeAttackRangeWeapon *>(weapon), owner);
	}

	if (horde->queryAt48(false, &owner->m_position, range) == 0)
		return horde->queryAt48(false, 0, 0);
	return this;
}
