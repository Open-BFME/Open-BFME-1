// ?scanClosestTarget@CommandButtonHuntUpdate@@IAEPAVObject@@XZ
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

#include <math.h>

// CommandButtonHuntUpdate::huntSpecialPower, retail 0x0028B490, 133 bytes.
// The module stores its data pointer at +0x04, its owner at +0x08, and its
// command button at +0x24. The three calls below use the retail thunks for the
// override walk, special-ability lookup, and target scan.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum SpecialPowerType
{
	SPECIAL_POWER_INVALID = 0
};

class Object;
class Player;
class ThingTemplate;
class SpecialAbilityUpdate;
class SpecialPowerModuleInterface;
class SpecialPowerTemplate;
class AttackPriorityInfo;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum Relationship
{
	RELATIONSHIP_ENEMIES = 0,
	RELATIONSHIP_NEUTRAL = 1,
	RELATIONSHIP_ALLIES = 2
};

template <int N>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags()
	{
		for (int i = 0; i != 6; ++i)
			m_words[i] = 0;
	}

	BitFlags(int, int index)
	{
		for (int i = 0; i != 6; ++i)
			m_words[i] = 0;
		m_words[index >> 5] |= 1u << (index & 31);
	}

	UnsignedInt m_words[6];
};

typedef BitFlags<192> KindOfMaskType;

enum KindOfType
{
	KINDOF_MINE = 54
};

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);

	UnsignedInt m_vptr;
	PartitionFilter *m_next;
};

class PartitionFilterAlive : public PartitionFilter
{
public:
	PartitionFilterAlive()
	{
		m_next = 0;
		m_vptr = 0x01083B80;
	}
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *object)
	{
		m_next = 0;
		m_vptr = 0x01085DD0;
		m_object = object;
	}

	const Object *m_object;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(const Object *object, Int flags, Bool state)
	{
		m_next = 0;
		m_vptr = 0x01085DC0;
		m_object = object;
		m_flags = flags;
		m_state = state;
	}

	const Object *m_object;
	Int m_flags;
	Bool m_state;
};

class PartitionFilterSamePlayer : public PartitionFilter
{
public:
	PartitionFilterSamePlayer(const Player *player)
	{
		m_next = 0;
		m_vptr = 0x01097144;
		m_player = player;
	}

	const Player *m_player;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);
};

struct BfmeWideResultItem
{
	Object *m_object;
	UnsignedInt m_distance;
};

class BfmeWideVector
{
public:
	BfmeWideResultItem *m_start;
	BfmeWideResultItem *m_finish;
	BfmeWideResultItem *m_end;

	BfmeWideResultItem *finish() const
	{
		return m_finish;
	}
};

struct BfmeWideResultPayload
{
	BfmeWideVector m_items;
	BfmeWideResultItem *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	BfmeWideResultPayload *m_value;

	~BfmeWideResult()
	{
		BfmeWideResultPayload *payload = m_value;
		--payload->m_refCount;
		if (payload->m_refCount == 0)
		{
			::operator delete(payload->m_items.m_start);
			::operator delete(payload);
		}
	}
};

class BfmeWideResultSource
{
public:
	BfmeWideResult bfmeMakeWideResult(Int, Int, Int, Int, Int, Int);
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int, Int, Int, Int, Int);

private:
	unsigned char m_padding[0x0c];
	BfmeWideResultSource *m_source;
};

class PartitionManager : public BfmeWideForwardC
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

class ActionManager
{
public:
	Bool canDoSpecialPowerAtObject(const Object *source, const Object *target,
		CommandSourceType commandSource, const SpecialPowerTemplate *templateObject,
		UnsignedInt flags, Bool force);
};

class AI
{
public:
	class AIData
	{
	public:
		unsigned char m_padding[0x54];
		Real m_attackPriorityDistanceModifier;
	};

	unsigned char m_padding[0x14];
	AIData *m_aiData;
};

extern PartitionManager *ThePartitionManager;
extern ActionManager *TheActionManager;
extern AI *TheAI;

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

protected:
	void *m_moduleData;
	Object *m_object;
};

class PB_Iface1
{
public:
	virtual void slot();
};

class PB_Iface2
{
public:
	virtual void slot();
};

class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
protected:
	Object *getObject() const
	{
		return m_object;
	}

private:
	UnsignedInt m_f14;
	int m_f18;
	int m_f1c;
};

class CommandButtonHuntUpdateModuleData
{
public:
	unsigned char m_unmodelled[8];
	UnsignedInt m_scanFrames;
	Real m_scanRange;
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *getFinalOverride();
	const Overridable *getFinalOverride() const;
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFO() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}

	SpecialPowerType getSpecialPowerType() const
	{
		return getFO()->m_specialPowerType;
	}

	Real getViewObjectRange() const
	{
		return getFO()->m_viewObjectRange;
	}

	private:
	unsigned char m_unmodelled[0x14 - 8];
	SpecialPowerType m_specialPowerType;
	unsigned char m_padding[0x10c - 0x18];
	Real m_viewObjectRange;
};

class ThingTemplate : public Overridable
{
};

class CommandButton
{
public:
	const SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return m_specialPowerTemplate;
	}

private:
	unsigned char m_unmodelled[0x34];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class SpecialAbilityUpdateInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual Bool isActive() const = 0;
};

class SpecialAbilityUpdateBase
{
public:
	virtual void slot() = 0;

protected:
	unsigned char m_unmodelled[0x1c];
};

class SpecialAbilityUpdate : public SpecialAbilityUpdateBase,
	public SpecialAbilityUpdateInterface
{
};

class AttackPriorityInfo
{
public:
	Int getPriority(const ThingTemplate *thingTemplate) const;
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;
	unsigned char m_padding[0x6c];
	const AttackPriorityInfo *m_attackInfo;
};

class Object
{
public:
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *object) const;
	Real getDistanceSquared(const Object *object) const;
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *templateObject) const;
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (const ThingTemplate *)
				thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}
	void doCommandButtonAtObject(const CommandButton *commandButton, Object *object,
		CommandSourceType source, Bool playVoiceResponse);

	private:
	ThingTemplate *m_template;
};

class CommandButtonHuntUpdate : public UpdateModule
{
	protected:
	UpdateSleepTime huntSpecialPower(AIUpdateInterface *ai);

	Object *scanClosestTarget();

private:
	void *m_commandButtonName;
	const CommandButton *m_commandButton;
};

UpdateSleepTime CommandButtonHuntUpdate::huntSpecialPower(AIUpdateInterface *ai)
{
	Object *obj = getObject();
	const CommandButtonHuntUpdateModuleData *data =
		(const CommandButtonHuntUpdateModuleData *)m_moduleData;
	if (!ai->isIdle())
	{
		return (UpdateSleepTime)data->m_scanFrames;
	}

	const SpecialPowerTemplate *spTemplate = m_commandButton->getSpecialPowerTemplate();
	if (spTemplate)
	{
		SpecialAbilityUpdate *spUpdate = obj->findSpecialAbilityUpdate(
			spTemplate->getSpecialPowerType());
		if (spUpdate == 0)
			return UPDATE_SLEEP_FOREVER;
		if (spUpdate->isActive())
			return (UpdateSleepTime)data->m_scanFrames;
	}

	Object *victim = scanClosestTarget();
	if (victim)
	{
		obj->doCommandButtonAtObject(m_commandButton, victim, CMD_FROM_AI, false);
	}
	return (UpdateSleepTime)data->m_scanFrames;
}

Object *CommandButtonHuntUpdate::scanClosestTarget()
{
	const CommandButtonHuntUpdateModuleData *data =
		(const CommandButtonHuntUpdateModuleData *)m_moduleData;
	Object *me = getObject();

	PartitionFilterAlive aliveFilter;
	PartitionFilterSameMapStatus filterMapStatus(me);
	PartitionFilterRelationship filterTeam(me, 1, false);
	PartitionFilter *filters = aliveFilter.link(&filterMapStatus);

	Bool isCaptureBuilding = false;
	Bool isPlaceExplosive = false;
	const SpecialPowerTemplate *spTemplate =
		m_commandButton->getSpecialPowerTemplate();
	if (spTemplate->getSpecialPowerType() == (SpecialPowerType)0x1d)
		isCaptureBuilding = true;
	if (spTemplate->getSpecialPowerType() == (SpecialPowerType)0x17 ||
		spTemplate->getSpecialPowerType() == (SpecialPowerType)0x19)
		isPlaceExplosive = true;
	if (!isCaptureBuilding)
		filters->link(&filterTeam);

	Int positionBits = (Int)(const void *)me->getPosition();
	Int rangeBits = *(const Int *)&data->m_scanRange;

	BfmeWideResult result =
		ThePartitionManager->bfmeForwardWideC(
			positionBits, rangeBits, 0, (Int)(const void *)filters, 1);

	AIUpdateInterface *ai =
		*(AIUpdateInterface **)((unsigned char *)me + 0x204);
	const AttackPriorityInfo *info = ai ? ai->m_attackInfo : 0;
	if (!me->getSpecialPowerModule(spTemplate))
		return 0;

	Object *bestTarget = 0;
	Int effectivePriority = 0;
	Int actualPriority = 0;
	BfmeWideResultPayload *payload = result.m_value;
	for (BfmeWideResultItem *item = payload->m_cursor;
		item != payload->m_items.finish(); ++item)
	{
		Object *other = item->m_object;
		payload->m_cursor = item + 1;
		if (!other)
			continue;
		if (isCaptureBuilding)
		{
			if (me->getControllingPlayer() == other->getControllingPlayer())
				continue;
			if (me->getRelationship(other) == RELATIONSHIP_ALLIES)
				continue;
		}
		if (!TheActionManager->canDoSpecialPowerAtObject(
			me, other, CMD_FROM_AI, spTemplate, 0, true))
			continue;
		if (isPlaceExplosive)
		{
			Real range = spTemplate->getViewObjectRange();
			PartitionFilterSamePlayer filterPlayer(me->getControllingPlayer());
			KindOfMaskType mustBeSet(KindOfMaskType::kInit, KINDOF_MINE);
			KindOfMaskType mustBeClear;
			PartitionFilterAcceptByKindOf filterKind(mustBeSet, mustBeClear);
			if (ThePartitionManager->getClosestObject(
				(const Coord3D *)((const unsigned char *)other + 0x38), range,
				2, filterKind.link(&filterPlayer)))
				continue;
		}
		Real distance = (Real)sqrt(me->getDistanceSquared(other));
		Int curPriority = (Int)(data->m_scanRange - distance);
		if (info)
			curPriority = info->getPriority(other->getTemplate());
		if (curPriority == 0)
			continue;
		Int modifier = (Int)(distance /
			TheAI->m_aiData->m_attackPriorityDistanceModifier);
		Int modPriority = curPriority - modifier;
		if (modPriority < 1)
			modPriority = 1;
		if (modPriority > effectivePriority ||
			(modPriority == effectivePriority && curPriority > actualPriority))
		{
			effectivePriority = modPriority;
			actualPriority = curPriority;
			bestTarget = other;
		}
	}
	return bestTarget;
}
