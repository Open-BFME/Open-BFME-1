// ?doSpecialPowerAtObject@PlayerHealSpecialPower@@UAEXPAVObject@@I@Z
// partial score=0.996 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// PlayerHealSpecialPower::doSpecialPowerAtObject, retail RVA 0x00263CA0.
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef bool Bool;

extern const Real BfmeZeroRange;

class Player;
class Object;
class Thing;

struct Rva00263CA0KindOfMask
{
	UnsignedInt words[6];
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *that) const;
	Bool isAnyKindOf(const Rva00263CA0KindOfMask &mask) const;
	Bool isKindOf(KindOfType type) const;

	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void attemptHealing(Real amount, const Object *source) = 0;

	unsigned char m_pad00[0x1a0];
	UnsignedInt m_disabledMask;
	unsigned char m_pad1a8[0x58];
	BodyModuleInterface *m_body;
	unsigned char m_pad204[0x1c];
	Real m_constructionPercent;
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary,
		const Object *secondary);
};

class ObjectCreationList
{
public:
	void create(const Object *primary, const Object *secondary,
		Int first, Int second);
};

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);
	UnsignedInt m_vtable;
	PartitionFilter *m_next;
};

struct Rva00263CA0RootFilter
{
	Rva00263CA0RootFilter()
	{
		m_next = 0;
		m_vtable = 0x01083B80;
	}
	~Rva00263CA0RootFilter()
	{
		m_vtable = 0x01083B5C;
	}
	Rva00263CA0RootFilter *link()
	{
		return this;
	}

	volatile UnsignedInt m_vtable;
	PartitionFilter * volatile m_next;
};

struct Rva00263CA0Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva00263CA0ResultData
{
	std::vector<Rva00263CA0Entry> entries;
	Rva00263CA0Entry *current;
	Int references;
};

struct Rva00263CA0WideResult
{
	Rva00263CA0ResultData *value;

	Rva00263CA0WideResult(const Rva00263CA0WideResult &other)
		: value(other.value)
	{
		++value->references;
	}
	~Rva00263CA0WideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = value->current->object;
		++value->current;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	Rva00263CA0WideResult bfmeForwardWideC(int, int, int, int, int);
};

extern BfmeWideForwardC *ThePartitionManager;

struct PlayerHealSpecialPowerModuleData
{
	unsigned char m_pad00[0x210];
	Real m_healAmount;
	Real m_healRadius;
	Rva00263CA0KindOfMask m_healAffects;
	FXList *m_healFX;
	ObjectCreationList *m_healOCL;
};

class Module
{
public:
	virtual ~Module();
	const PlayerHealSpecialPowerModuleData *getModuleData() const
	{
		return m_moduleData;
	}

private:
	const PlayerHealSpecialPowerModuleData *m_moduleData;
};

class ObjectModule : public Module
{
public:
	Object *getObject() const
	{
		return m_object;
	}

private:
	Object * volatile m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class SpecialPowerModuleInterface
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
	virtual void doSpecialPowerAtObject(Object *target, UnsignedInt commandOptions) = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void startPowerRecharge() = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
};

class Rva00268CB0
{
public:
	void invoke(Object *target);
};

#pragma comment(linker, "/alternatename:?invoke@Rva00268CB0@@QAEXPAVObject@@@Z=?j_00046c13@@YAXXZ")

#pragma comment(linker, "/alternatename:?run@Rva00268CB0PlayerHealAction@@QAEXPAVObject@@@Z=?j_00046c13@@YAXXZ")
#pragma comment(linker, "/alternatename:?create@ObjectCreationList@@QAEXPBVObject@@0HH@Z=?j_00002a59@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z=?j_0004a719@@YAXXZ")
#pragma comment(linker, "/alternatename:?isAnyKindOf@Object@@QBE_NABVRva00263CA0KindOfMask@@@Z=?j_0004250a@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Object@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")

class PlayerHealSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtObject(Object *target, UnsignedInt commandOptions);
};

void PlayerHealSpecialPower::doSpecialPowerAtObject(Object *target,
	UnsignedInt commandOptions)
{
	Object *owner = getObject();
	UnsignedInt disabledMask = owner->m_disabledMask;
	Object *volatile savedOwner;
	savedOwner = owner;
	if (disabledMask != 0)
		return;
	if (owner->getControllingPlayer() == 0)
		return;

	((Rva00268CB0 *)this)->invoke(target);
	startPowerRecharge();

	ObjectCreationList *healOCL = getModuleData()->m_healOCL;
	Object *healOwner = getObject();
	if (healOCL != 0)
		healOCL->create(healOwner, target, 0, 0);

	Rva00263CA0WideResult iterator =
		ThePartitionManager->bfmeForwardWideC(
			(int)target,
			*(Int *)&getModuleData()->m_healRadius, 0,
			(int)Rva00263CA0RootFilter().link(), 1);

	Object *other;
		while (iterator.next(other))
		{
		if (other->getRelationship(savedOwner) != (Relationship)2)
			continue;
		if ((*(UnsignedByte *)((char *)other + 0x344) & 1) != 0)
			continue;
		if (!other->isAnyKindOf(
			getModuleData()->m_healAffects))
			continue;
		if (other->isKindOf((KindOfType)0x9a))
			continue;
		if (other->isKindOf((KindOfType)7))
		{
			if (other->m_constructionPercent >= BfmeZeroRange)
			{
				if (other->m_constructionPercent < *(const Real *)0x010B6554)
					continue;
			}
		}

		BodyModuleInterface *body = other->m_body;
		if (body == 0)
			continue;

		Real amount = body->getMaxHealth() *
			getModuleData()->m_healAmount;
		if (!(amount > BfmeZeroRange))
			continue;
		other->attemptHealing(amount, 0);
		if (getModuleData()->m_healFX != 0)
			FXList::doFXObj(
				getModuleData()->m_healFX,
				other, 0);
	}
}
