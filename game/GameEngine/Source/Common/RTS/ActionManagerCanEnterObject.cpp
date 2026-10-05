// cl: /DNDEBUG /MD /EHsc
//
// BFME's five-argument ActionManager::canEnterObject at retail RVA 0x000C5440
// (ILT 0x0002D588), called by AIEnterState::onEnter, Player::garrisonAllUnits
// and the AIStates enter/garrison paths with the trailing Bool* out-parameter.
// The Zero Hour body (GeneralsMD ActionManager.cpp) is the skeleton; BFME adds
// the dozer/harvester health gate, the already-entering shroud bypass, the
// deployed-status test, the contain ownership gate and the NO_FREEWILL_ENTER
// tail, and drops the unmanned-reject and airfield special cases.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;

#include "../../GameLogic/command_source_type.h"

// Zero Hour's CanEnterType (Common/ActionManager.h).
enum CanEnterType
{
	CHECK_CAPACITY,
	DONT_CHECK_CAPACITY,
	COMBATDROP_INTO
};

// KindOf bit numbers, named by the retail KindOf name table at 0x012AA068.
enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_STRUCTURE = 7,
	KINDOF_INFANTRY = 8,
	KINDOF_DOZER = 14,
	KINDOF_HARVESTER = 16,
	KINDOF_MOB_NEXUS = 46,
	KINDOF_IGNORED_IN_GUI = 47,
	KINDOF_NO_FREEWILL_ENTER = 111
};

// ObjectStatus bit numbers, named by the retail status name table at 0x012A6670.
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_SOLD = 19,
	OBJECT_STATUS_DEPLOYED = 58
};

// DisabledType bit numbers, named by the retail name table at 0x012A9200.
enum DisabledType
{
	DISABLED_UNMANNED = 5
};

// Zero Hour's Relationship (Common/GameCommon.h).
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_FOGGED = 3
};

// The AI state the enter path compares against; its BFME name is not evidenced.
enum
{
	AI_STATE_ID_38 = 0x38
};

template <int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

class Object;
class Player
{
public:
	Int getPlayerIndex(void) const;
};

// Zero Hour Common/Overridable.h: the first link of the override walk
// inlines, the recursion stays out of line (ILT 0x000022BB).
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;
};

// Zero Hour Common/Override.h.  Thing reads its template through this member
// object, so the dereference is of obj+4, not obj: that is what keeps retail's
// later obj == NULL test, which a direct const ThingTemplate* member folds away.
template <class T>
class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

	operator const T *() const
	{
		return operator*();
	}

private:
	const T *m_overridable;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindof[(UnsignedInt)kind >> 5] & (1 << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	UnsignedInt m_kindof[4];
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }

	Bool isKindOf(KindOfType kind) const;

protected:
	virtual ~Thing();

	OVERRIDE<ThingTemplate> m_template;
};

class BodyModuleInterface
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual Real getHealth() const;
	virtual Real slot_014() const;
	virtual Real getMaxHealth() const;
};

class CollideModuleInterface
{
public:
	virtual void slot_000();
	virtual Bool wouldLikeToCollideWith(const Object *other) const;
};

class BehaviorModuleInterface : public BFMEVirtualSlots<1>
{
public:
	virtual CollideModuleInterface *getCollide() = 0;
	virtual void slot_008() = 0;
	virtual void slot_00c() = 0;
	virtual void slot_010() = 0;
	virtual void slot_014() = 0;
	virtual void slot_018() = 0;
	virtual void slot_01c() = 0;
	virtual void slot_020() = 0;
	virtual void slot_024() = 0;
	virtual void slot_028() = 0;
	virtual void slot_02c() = 0;
	virtual void slot_030() = 0;
	virtual void slot_034() = 0;
	virtual void slot_038() = 0;
	virtual void slot_03c() = 0;
	virtual void slot_040() = 0;
	virtual void *slot_044() = 0;
};

// Zero Hour's ObjectModule base: vtable, module data and owning object.
class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	void *m_moduleData;
	Object *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class ContainModuleInterface : public BFMEVirtualSlots<4>
{
public:
	virtual Bool isHealContain() const = 0;
	virtual void slot_014() = 0;
	virtual Bool slot_018() const = 0;
	virtual void slot_01c() = 0;
	virtual void slot_020() = 0;
	virtual void slot_024() = 0;
	virtual void slot_028() = 0;
	virtual void slot_02c() = 0;
	virtual void slot_030() = 0;
	virtual void slot_034() = 0;
	virtual void slot_038() = 0;
	virtual void slot_03c() = 0;
	virtual void slot_040() = 0;
	virtual void slot_044() = 0;
	virtual void slot_048() = 0;
	virtual void slot_04c() = 0;
	virtual void slot_050() = 0;
	virtual void slot_054() = 0;
	virtual void slot_058() = 0;
	virtual void slot_05c() = 0;
	virtual void slot_060() = 0;
	virtual void slot_064() = 0;
	virtual void slot_068() = 0;
	virtual void slot_06c() = 0;
	virtual void slot_070() = 0;
	virtual void slot_074() = 0;
	virtual void slot_078() = 0;
	virtual void slot_07c() = 0;
	virtual void slot_080() = 0;
	virtual Bool isValidContainerFor(const Object *obj, Bool checkCapacity) const = 0;
	virtual void slot_088() = 0;
	virtual void slot_08c() = 0;
	virtual void slot_090() = 0;
	virtual void slot_094() = 0;
	virtual void slot_098() = 0;
	virtual void slot_09c() = 0;
	virtual void slot_0a0() = 0;
	virtual void slot_0a4() = 0;
	virtual void slot_0a8() = 0;
	virtual void slot_0ac() = 0;
	virtual void slot_0b0() = 0;
	virtual void slot_0b4() = 0;
	virtual void slot_0b8() = 0;
	virtual void slot_0bc() = 0;
	virtual void slot_0c0() = 0;
	virtual Bool slot_0c4() const = 0;
	virtual void slot_0c8() = 0;
	virtual Player *slot_0cc() const = 0;
	virtual Bool slot_0d0(const Object *obj) const = 0;
	virtual void slot_0d4() = 0;
	virtual void slot_0d8() = 0;
	virtual void slot_0dc() = 0;
	virtual void slot_0e0() = 0;
	virtual void slot_0e4() = 0;
	virtual void slot_0e8() = 0;
	virtual void slot_0ec() = 0;
	virtual void slot_0f0() = 0;
	virtual void slot_0f4() = 0;
	virtual void slot_0f8() = 0;
	virtual void slot_0fc() = 0;
	virtual Int getContainCount(Int arg) const = 0;
	virtual void slot_104() = 0;
	virtual void slot_108() = 0;
	virtual void slot_10c() = 0;
	virtual Int getStealthUnitsContained() const = 0;
};

class StateMachine
{
public:
	Object *getGoalObject();
};

class AIUpdateInterface
{
public:
	UnsignedInt getCurrentStateID() const;
	StateMachine *getStateMachine() const { return m_stateMachine; }

private:
	char m_unmodelled00[0x30];
	StateMachine *m_stateMachine;
};

// Zero Hour's DisabledMaskType is a BitFlags over an STLport bitset; its
// single-word test is all this body reaches.  Retail inlines the unmanned test
// to one byte test; plain inline runs out of this body's inline budget and
// calls it out of line, hence __forceinline on both layers.
class DisabledMaskType
{
public:
	__forceinline Bool test(UnsignedInt pos) const
	{
		return (m_bits[pos / 32] & (1UL << (pos % 32))) != 0;
	}

private:
	UnsignedInt m_bits[1];
};

class Object : public Thing
{
public:
	Relationship getRelationship(const Object *other) const;
	Player *getControllingPlayer() const;
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
	Bool testStatus(Int status) const;
	Bool isFactionStructure() const;
	Int getTransportSlotCount() const;

	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	__forceinline Bool isDisabledByType(DisabledType type) const
	{
		return m_disabledMask.test(type);
	}
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	char m_pad008[0x1a4 - 0x08];
	DisabledMaskType m_disabledMask;
	char m_pad1a8[0x1f0 - 0x1a8];
	BehaviorModule **m_behaviors;
	char m_pad1f4[0x1fc - 0x1f4];
	ContainModuleInterface *m_contain;
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
	char m_pad208[0x344 - 0x208];
	UnsignedByte m_privateStatus;
};

static Bool isObjectShroudedForAction(const Object *source, const Object *target,
	CommandSourceType commandSource)
{
	if (target)
	{
		Int targetID = *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(target) + 0x74);
		if (targetID >= 0x05f5e0fc && targetID <= 0x05f5e0ff)
			return false;
	}

	if (source && target && source->getControllingPlayer())
	{
		if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(source->getControllingPlayer()) + 0x2c) == 0 &&
			commandSource != CMD_FROM_SCRIPT &&
			target->getShroudedStatus(source->getControllingPlayer()->getPlayerIndex()) >= OBJECTSHROUD_FOGGED)
			return true;
	}

	return false;
}

class BFMEActionManager
{
public:
	Bool canEnterObject(const Object *obj, const Object *objectToEnter,
		CommandSourceType commandSource, CanEnterType mode, Bool *pFlag);
};

Bool BFMEActionManager::canEnterObject(const Object *obj, const Object *objectToEnter,
	CommandSourceType commandSource, CanEnterType mode, Bool *pFlag)
{
	Bool dummyFlag;
	if (pFlag == 0)
		pFlag = &dummyFlag;
	*pFlag = false;

	if (obj->getTemplate()->isKindOf(KINDOF_DOZER) && obj->getTemplate()->isKindOf(KINDOF_HARVESTER))
	{
		BodyModuleInterface *body = objectToEnter->getBodyModule();
		if (body && body->slot_014() < 0.99f)
			return false;
	}

	if (obj == 0 || objectToEnter == 0)
		return false;

	if (obj == objectToEnter)
		return false;

	if (objectToEnter->isEffectivelyDead())
		return false;

	// an object already entering this target may keep going into the shroud
	AIUpdateInterface *ai = obj->getAI();
	Bool alreadyEntering = false;
	if (ai && ai->getCurrentStateID() == AI_STATE_ID_38)
		alreadyEntering = ai->getStateMachine()->getGoalObject() == objectToEnter;
	if (!alreadyEntering && isObjectShroudedForAction(obj, objectToEnter, commandSource))
		return false;

	if (obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) ||
		objectToEnter->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		return false;

	if (objectToEnter->testStatus(OBJECT_STATUS_DEPLOYED))
		return false;

	if (objectToEnter->testStatus(OBJECT_STATUS_SOLD))
		return false;

	if (obj->isKindOf(KINDOF_IGNORED_IN_GUI) || obj->isKindOf(KINDOF_MOB_NEXUS) ||
		objectToEnter->isKindOf(KINDOF_IGNORED_IN_GUI))
		return false;

	if (obj->isKindOf(KINDOF_STRUCTURE) || obj->isKindOf(KINDOF_IMMOBILE))
		return false;

	if (obj->isKindOf(KINDOF_INFANTRY) && objectToEnter->isDisabledByType(DISABLED_UNMANNED))
		return true;

	for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
	{
		CollideModuleInterface *collide = (*m)->getCollide();
		if (!collide)
			continue;

		if ((*m)->slot_044())
			continue;

		if (collide->wouldLikeToCollideWith(objectToEnter))
			return true;
	}

	ContainModuleInterface *contain = objectToEnter->getContain();
	if (!contain)
		return false;

	if (contain->isHealContain())
	{
		BodyModuleInterface *body = obj->getBodyModule();
		if (body->getHealth() == body->getMaxHealth())
			return false;
	}

	if (mode == COMBATDROP_INTO)
	{
		if (objectToEnter->isFactionStructure())
			return false;
	}
	else
	{
		Bool checkCapacity = (mode == CHECK_CAPACITY);
		Bool allowed = contain->slot_018();
		if (allowed)
		{
			if (contain->slot_0c4())
			{
				if (checkCapacity && !contain->slot_0d0(obj))
					allowed = false;
				if (obj->getControllingPlayer() != contain->slot_0cc())
					allowed = false;
			}
			else
			{
				if (obj->getRelationship(objectToEnter) != ENEMIES)
					allowed = false;
			}
		}

		if (objectToEnter->getControllingPlayer() != obj->getControllingPlayer())
		{
			Int containCount = contain->getContainCount(0);
			Int stealthContainCount = contain->getStealthUnitsContained();
			Int nonStealthContainCount = containCount - stealthContainCount;

			if (nonStealthContainCount > 0 || objectToEnter->isFactionStructure())
			{
				if (!allowed)
					return false;
				*pFlag = true;
			}

			if (stealthContainCount > 0 && nonStealthContainCount == 0)
				checkCapacity = false;
		}

		if (checkCapacity && obj->getTransportSlotCount() == 0)
			return false;

		if (*pFlag)
			checkCapacity = false;

		if (!contain->isValidContainerFor(obj, checkCapacity))
			return false;
	}

	if (objectToEnter->isKindOf(KINDOF_NO_FREEWILL_ENTER))
		return false;

	return true;
}
