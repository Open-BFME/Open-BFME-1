// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

#define OBJECT_TU_MEMBERS Object *bfmePostClosest(const Object *owner, Bool add);
#include "object.h"

extern void j_0003251f(void);
extern void j_00028f74(void);
extern void j_0002e631(void);

class HordeContainInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual Object *queryAt48(Bool unknown, const Real *position, Real range);
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual HordeContainInterface *getHordeContainInterface();
};

class Weapon
{
public:
	void *m_vtable;
	void *m_template;
};

struct BfmeObjectWeaponFields
{
	UnsignedByte m_unreconstructed_000[0x26c];
	Weapon *m_weapons[4];
	UnsignedInt m_curWeapon;
	UnsignedByte m_unreconstructed_280[4];
	void *m_hasWeapon;
};

struct BfmeKindOfCall
{
	Bool call(Int kind);
};

static Bool bfmeIsKindOf(const Object *object, Int kind)
{
	typedef Bool (BfmeKindOfCall::*Function)(Int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003251f;
	return (reinterpret_cast<BfmeKindOfCall *>(const_cast<Object *>(object))->*fn.member)(kind);
}

struct BfmeLeechRangeTemplate
{
	Bool isLeechRangeWeapon() const;
};

static Bool bfmeIsLeechRangeWeapon(const BfmeLeechRangeTemplate *object)
{
	typedef Bool (BfmeLeechRangeTemplate::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00028f74;
	return (object->*fn.member)();
}

struct BfmeAttackRangeWeapon
{
	Real getAttackRange(const Object *owner) const;
};

static Real bfmeGetAttackRange(const Weapon *weapon, const Object *owner)
{
	typedef Real (BfmeAttackRangeWeapon::*Function)(const Object *) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002e631;
	return (reinterpret_cast<const BfmeAttackRangeWeapon *>(weapon)->*fn.member)(owner);
}

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
			ContainModuleInterface *contain = (*containedBy)->m_contain;
			if (contain == 0 || contain->getHordeContainInterface() == 0)
				break;
			object = *containedBy;
			containedBy = &object->m_containedBy;
		}
		while (*containedBy);
	}

	ContainModuleInterface *contain = object->m_contain;
	if (contain != 0)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde != 0)
		{
			Real range = 0.0f;
			BfmeObjectWeaponFields *ownerFields =
				reinterpret_cast<BfmeObjectWeaponFields *>(const_cast<Object *>(owner));
			if (!add)
				range = 99999.0f;
			else if (!bfmeIsKindOf(owner, 0x6c) && ownerFields->m_hasWeapon != 0)
			{
				Weapon *weapon = ownerFields->m_weapons[ownerFields->m_curWeapon];
				if (weapon != 0 && !bfmeIsLeechRangeWeapon(
					reinterpret_cast<const BfmeLeechRangeTemplate *>(weapon->m_template)))
					range = bfmeGetAttackRange(weapon, owner);
			}

			Object *selected = horde->queryAt48(false, owner->m_cachedPos, range);
			if (selected != 0)
				return selected;
			return horde->queryAt48(false, 0, 0);
		}
	}
	return this;
}
