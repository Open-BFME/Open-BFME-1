// ?scanClosestTarget@CommandButtonHuntUpdate@@IAEPAVObject@@XZ
// Retail RVA 0x0028AE90, 974 bytes, plain ret at 0x0028B25E.
//
// IDENTITY. The matched caller CommandButtonHuntUpdate::huntSpecialPower
// (0x0028B490, CommandButtonHuntUpdate_huntSpecialPower.cpp) calls a protected
// `Object *scanClosestTarget()` through retail ILT 0x00047CBC, whose five bytes
// are `jmp 0x0028AE90`; the helper is called with no argument and its result is
// tested against null and passed straight to doCommandButtonAtObject, so the
// name and the `Object *` return type are witnessed, not guessed.
//
// ABI NOTES proved by the bytes.
//  * The module keeps its data pointer at +0x04, its owner at +0x08 and the
//    command button at +0x24 (this is the same UpdateModule/CommandButton
//    layout the matched caller uses).
//  * BFME returns the reference-counted BfmeWideResult, not the retained ZH
//    ObjectIterator: the payload is vector(start,end,capacity) at +0x00, the
//    item cursor at +0x0C and the reference count at +0x10, entries are eight
//    bytes, and the 0x80 byte capacity test in the unwind path is 16 entries.
//    AutoFindHealingUpdateScanClosestTarget.cpp witnesses the same descriptor
//    and the same `next()` shape.
//  * next() is a member of BfmeWideResult (not of the payload) and reads
//    through m_value; the postfix `(m_value->m_cursor++)->m_object` is what
//    makes the frontend keep the pre-increment cursor live across the store and
//    emit the `mov ecx,edx` copy at +0x1EF. A payload-level `++m_cursor` with
//    a separate local collapses that copy and costs two bytes.
//  * The ownership test is written with `me` on the left: retail encodes
//    `cmp eax,edi` after the second getControllingPlayer call, which is the
//    second operand as the register destination.
//  * Overridable::friend_getFinalOverride is the ZH inline-recursive walk (two
//    levels inline, the third through ILT 0x00048C61); Object carries a vptr
//    so m_template is at +4, and getTemplate returns 0 early for a null
//    template. The filters are the BFME virtual-destructor classes
//    (ScriptConditions.cpp model), unwound alive, relationship, map-status;
//    the kind-of filter temporary is throw() (retail never stores EH state 4)
//    and is passed through link().
//  * getSpecialPowerType values 0x17/0x19 mark a place-explosive hunt and 0x1d
//    a capture building; the scan range doubles as the priority base, the
//    third bfmeForwardWideC argument is the zero default and the distance
//    calculation argument of getClosestObject is 1.
// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <bitset>
#include <math.h>

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags(BogusInitType, Int idx)
	{
		m_bits._Unchecked_set((size_t)idx);
	}
};

typedef BitFlags<192> KindOfMaskType;

// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B, VA 0x012ED8B8
extern const KindOfMaskType KINDOFMASK_NONE;

enum KindOfType
{
	KINDOF_MINE = 54
};

// BFME filters (same model as ScriptConditions.cpp Rva00327D30): virtual
// destructor, allow, getPlayerMask, then next at +4.
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

// vtable 0x01083B70; out-of-line ctor at ILT 0x000382FD.
class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear) throw();
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

// vtable 0x01085DD0
class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

// vtable 0x01083B80
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

// ZH PartitionFilterAlive; the BFME table name stays address-derived.
typedef Rva0025ED50RootFilter PartitionFilterAlive;

// vtable 0x01085DC0
class PartitionFilterRelationship : public PartitionFilter
{
public:
	enum RelationshipAllowTypes
	{
		ALLOW_ENEMIES = 1,
		ALLOW_NEUTRAL = 2,
		ALLOW_ALLIES = 4
	};

	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

// vtable 0x01097144 (three slots: destructor, allow, getPlayerMask).
class PlayerFilter0028AE90 : public PartitionFilter
{
public:
	PlayerFilter0028AE90(Player *player) : m_player(player) {}
	virtual ~PlayerFilter0028AE90() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Player *m_player;
};

struct BfmeWideResultItem
{
	Object *m_object;
	UnsignedInt m_distance;
};

void __cdecl bfmeFreeScalar(void *block);
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

struct BfmeWideResultPayload
{
	std::vector<BfmeWideResultItem> m_items;
	BfmeWideResultItem *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	BfmeWideResultPayload *m_value;

	~BfmeWideResult()
	{
		BfmeWideResultPayload *&payload = m_value;
		--payload->m_refCount;
		if (payload->m_refCount == 0)
			delete payload;
	}

	Object *next()
	{
		if (m_value->m_cursor == m_value->m_items.end())
			return 0;
		return (m_value->m_cursor++)->m_object;
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
		if (m_template == 0)
			return 0;
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate->m_nextOverride)
			thingTemplate = (const ThingTemplate *)
				thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}
	void doCommandButtonAtObject(const CommandButton *commandButton, Object *object,
		CommandSourceType source, Bool playVoiceResponse);

	private:
	void *m_vftable;
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

// Both bodies are matched elsewhere; retail reaches them through their
// incremental-link thunks, so reference the thunks directly, as retail spells
// them (CommandButtonHuntUpdate_huntSpecialPower.cpp does the same for its
// ILTs). Each caller below builds a local member pointer to its thunk.
extern void j_0001641e();
extern void j_00017bca();

// ?scanClosestTarget@CommandButtonHuntUpdate@@IAEPAVObject@@XZ
Object *CommandButtonHuntUpdate::scanClosestTarget()
{
	const CommandButtonHuntUpdateModuleData *data =
		(const CommandButtonHuntUpdateModuleData *)m_moduleData;
	Object *me = getObject();
	const SpecialPowerTemplate *spTemplate =
		m_commandButton->getSpecialPowerTemplate();
	if (spTemplate == 0)
		return 0;

	Bool isCaptureBuilding = (spTemplate->getSpecialPowerType() == (SpecialPowerType)0x1d);
	Bool isPlaceExplosive = false;
	if (spTemplate->getSpecialPowerType() == (SpecialPowerType)0x17)
		isPlaceExplosive = true;
	if (spTemplate->getSpecialPowerType() == (SpecialPowerType)0x19)
		isPlaceExplosive = true;

	PartitionFilterAlive aliveFilter;
	PartitionFilterRelationship filterTeam(me, PartitionFilterRelationship::ALLOW_ENEMIES, false);
	Rva0025ED50ObjectFilter filterMapStatus(me);
	aliveFilter.link(&filterMapStatus);
	if (!isCaptureBuilding)
		aliveFilter.link(&filterTeam);

	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		(Int)(const void *)me->getPosition(), *(const Int *)&data->m_scanRange,
		0, (Int)(const void *)&aliveFilter, 1);

	Object *bestTarget = 0;
	Int effectivePriority = 0;
	Int actualPriority = 0;
	const AttackPriorityInfo *info = 0;
	AIUpdateInterface *ai = *(AIUpdateInterface **)((unsigned char *)me + 0x204);
	if (ai)
		info = ai->m_attackInfo;

	SpecialPowerModuleInterface *mod = me->getSpecialPowerModule(spTemplate);
	if (mod)
	{
		Object *other;
		while ((other = result.next()) != 0)
		{
			if (isCaptureBuilding)
			{
				if (me->getControllingPlayer() == other->getControllingPlayer())
					continue;
				if (me->getRelationship(other) == RELATIONSHIP_ALLIES)
					continue;
			}
			union { void (*fn)(); Bool (ActionManager::*call)(const Object *, const Object *,
			CommandSourceType, const SpecialPowerTemplate *, UnsignedInt, Bool); }
			canDoSpecialPowerAtObject = { j_00017bca };
		if (!(TheActionManager->*canDoSpecialPowerAtObject.call)(
				me, other, CMD_FROM_AI, spTemplate, 0, true))
				continue;
			if (isPlaceExplosive)
			{
				Real range = spTemplate->getViewObjectRange();
				Object *mine;
				{
					PlayerFilter0028AE90 filterPlayer(me->getControllingPlayer());
					mine = ThePartitionManager->getClosestObject(
						other->getPosition(), range, 1,
						PartitionFilterAcceptByKindOf(
							KindOfMaskType(KindOfMaskType::kInit, KINDOF_MINE),
							KINDOFMASK_NONE).link(&filterPlayer));
				}
				if (mine)
					continue;
			}
			Real dist = (Real)sqrt(me->getDistanceSquared(other));
			Int curPriority = (Int)(data->m_scanRange - dist);
			if (info)
			{
				union { void (*fn)(); Int (AttackPriorityInfo::*call)(
					const ThingTemplate *) const; } getPriority = { j_0001641e };
				curPriority = (info->*getPriority.call)(other->getTemplate());
			}
			if (curPriority == 0)
				continue;
			Int modifier = (Int)(dist /
				TheAI->m_aiData->m_attackPriorityDistanceModifier);
			Int modPriority = curPriority - modifier;
			if (modPriority < 1)
				modPriority = 1;
			if (modPriority > effectivePriority)
			{
				effectivePriority = modPriority;
				actualPriority = curPriority;
				bestTarget = other;
			}
			if (modPriority == effectivePriority && curPriority > actualPriority)
			{
				effectivePriority = modPriority;
				actualPriority = curPriority;
				bestTarget = other;
			}
		}
	}
	return bestTarget;
}
