// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x0014DAB0, 1122 B, SEH frame, ret 0xC.  AIAttackAreaState::update
// (0x0017E900, AIAttackAreaState_update_Bfme.cpp) reaches it on TheAI through
// ILT 0x0001D7B9 with (polygon trigger, owner, AttackPriorityInfo).  It is the
// BFME polygon-area form of ZH AI::findClosestEnemy (ai.cpp): the same
// isAbleToAttack punt, live-enemy/buildings/stealth/status/attack filters
// (BFME links them into a chain instead of an array), the special-module
// shortcut, the getDefaultAttackInfo split, and the priority loop with the
// contained-units pass through rva0014b880PriorityMaximum and the
// attackPriorityDistanceModifier scaling.  The search runs over the trigger's
// bounding region instead of a range.  The method name is not recovered, so
// it keeps its address; filters without a witnessed class name are named by
// their vtable address.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <math.h>
#include "PreRTS.h"
#include "Common/BitFlags.h"


class Object;
class ThingTemplate;
class PolygonTrigger;

// The trigger's integer bounding rectangle is copied out by the body at
// 0x0018F830 (ILT 0x0000FEE8); its ledger row carries only an opaque name.
struct BfmeVec4CMB
{
	IRegion2D m_bounds;
};
class BfmeThingCMB
{
public:
	void bfmeGoCMB(BfmeVec4CMB *bounds);
};

class AttackPriorityInfo
{
public:
	Int getPriority(const ThingTemplate *thingTemplate) const;
};

// The template chain walk is retail's own Overridable::getFinalOverride (ILT
// 0x000022BB), spelled on the real upstream class. Its body is a recursive
// inline, so a direct call makes MSVC expand the first level; retail expands no
// level. Taking the member's ADDRESS forces the body out of line, leaving the
// single rel32 call the ledger records at 0x000022BB.
struct BfmeTemplateNextOverride
{
	void *m_vptr;
	const Overridable *m_nextOverride;
};

static __forceinline const Overridable *bfmeGetFinalOverride(const Overridable *o)
{
	typedef const Overridable *(Overridable::*FinalOverrideCall)(void) const;
	FinalOverrideCall walk = &Overridable::getFinalOverride;
	return (o->*walk)();
}

struct Rva0014B880Candidate;
struct Rva0014B880Context
{
	Int m_priority;
	const AttackPriorityInfo *m_info;
};
void __cdecl rva0014b880PriorityMaximum(Rva0014B880Candidate *candidate,
	Rva0014B880Context *context);
typedef void (__cdecl *ContainIterateFunc)(Rva0014B880Candidate *, Rva0014B880Context *);

class ContainModule0014DAB0
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49)
	virtual Bool querySlot50(Object *source, Object **result);
	SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58)
	SLOT(59) SLOT(60) SLOT(61) SLOT(62)
	virtual void iterateContained(ContainIterateFunc func, Rva0014B880Context *context, Bool reverse);
#undef SLOT
};

struct SpecialOwner0014DAB0
{
	unsigned char m_pad[0x1fc];
	ContainModule0014DAB0 *m_module;
};

class Object
{
public:
	Bool isAbleToAttack() const;
	Object *bfmePostClosest(const Object *other, Bool flag);
	Real getDistanceSquared(const Object *other) const;
	const ThingTemplate *getTemplate() const
	{
		const Overridable *t = m_template;
		if (t == 0)
			return 0;
		const Overridable *next =
			reinterpret_cast<const BfmeTemplateNextOverride *>(t)->m_nextOverride;
		return (const ThingTemplate *)(next ? bfmeGetFinalOverride(next) : t);
	}

	void *m_vptr;
	const Overridable *m_template;
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_pos;
	unsigned char m_pad44[0x94 - 0x44];
	unsigned char m_flags94;
	unsigned char m_pad95[0x1fc - 0x95];
	ContainModule0014DAB0 *m_contain;
	unsigned char m_pad200[0x214 - 0x200];
	SpecialOwner0014DAB0 *m_special;
};

// ScriptEngine::getDefaultAttackInfo, an address-of-field getter at 0x00336C20
// (ILT 0x0000B59B) whose ledger row keeps an opaque name.
class Rva00336C20FieldAddress
{
public:
	char *get();
};
extern Rva00336C20FieldAddress *TheScriptEngine;
static inline const AttackPriorityInfo *getDefaultAttackInfo()
{
	return (const AttackPriorityInfo *)TheScriptEngine->get();
}

// The filter-chain test at 0x009F2A70: this filter and every linked one.
class BfmeThingEQ
{
public:
	unsigned char bfmeAskEQ(void *object);
};

struct TAiData0014DAB0
{
	unsigned char m_pad[0x54];
	Real m_attackPriorityDistanceModifier;
};

class AI
{
public:
	Object *rva0014DAB0(PolygonTrigger *area, Object *me, const AttackPriorityInfo *info);

	unsigned char m_pad[0x14];
	TAiData0014DAB0 *m_aiData;
};
extern AI *TheAI;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	PartitionFilter *link(PartitionFilter *next);
	Bool allowChain(Object *other)
	{
		return reinterpret_cast<BfmeThingEQ *>(this)->bfmeAskEQ(other) != 0;
	}
	PartitionFilter *m_next;
};

class PartitionFilter01095734 : public PartitionFilter
{
public:
	PartitionFilter01095734(const Object *obj) : m_obj(obj) {}
	virtual ~PartitionFilter01095734() {}
	virtual Bool allow(Object *);
	const Object *m_obj;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class PartitionFilterRejectBuildings : public PartitionFilter
{
public:
	PartitionFilterRejectBuildings(const Object *obj);
	virtual ~PartitionFilterRejectBuildings() {}
	virtual Bool allow(Object *);
	const Object *m_obj;
	Bool m_acquireEnemies;
};

class VptrZeroHead
{
public:
	VptrZeroHead() : m_unmodelled_04(0) {}
	virtual ~VptrZeroHead() {}
	UnsignedInt m_unmodelled_04;
};

class Rva001DCBB0Filter : public VptrZeroHead
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);
	virtual ~Rva001DCBB0Filter() {}
	void *m_player;
	unsigned char m_match;
};

typedef BitFlags<86> ObjectStatusMask0014DAB0;

class PartitionFilterRejectByObjectStatus : public PartitionFilter
{
public:
	PartitionFilterRejectByObjectStatus(const ObjectStatusMask0014DAB0 &mustSet,
		const ObjectStatusMask0014DAB0 &mustClear)
		: m_mustSet(mustSet), m_mustClear(mustClear) {}
	virtual ~PartitionFilterRejectByObjectStatus() {}
	virtual Bool allow(Object *);
	ObjectStatusMask0014DAB0 m_mustSet;
	ObjectStatusMask0014DAB0 m_mustClear;
};

class PartitionFilter010956C4 : public PartitionFilter
{
public:
	PartitionFilter010956C4(Int kind, const Object *obj, Int source)
		: m_obj(obj), m_kind(kind), m_source(source) {}
	virtual ~PartitionFilter010956C4() {}
	virtual Bool allow(Object *);
	const Object *m_obj;
	Int m_kind;
	Int m_source;
};

class PartitionFilterPolygonTrigger : public PartitionFilter
{
public:
	PartitionFilterPolygonTrigger(const PolygonTrigger *trigger) : m_trigger(trigger) {}
	virtual ~PartitionFilterPolygonTrigger() {}
	virtual Bool allow(Object *);
	const PolygonTrigger *m_trigger;
};

struct IterEntry0014DAB0 { Object *object; UnsignedInt word04; };
struct IterData0014DAB0
{
	std::vector<IterEntry0014DAB0> entries;
	IterEntry0014DAB0 *current;
	Int references;
};
struct BfmeWideResult
{
	IterData0014DAB0 *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	__forceinline ~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
	Object *next()
	{
		if (value->current == value->entries.end())
			return 0;
		return (value->current++)->object;
	}
};

// ThePartitionManager's region iterator (0x009F29E0) and region closest-object
// query (0x009F2700); the first keeps its ledger view, the second is pinned
// by address because its ledger view has no return value.
class BfmeWideForwardB
{
public:
	BfmeWideResult bfmeForwardWideB(int region, int order, int filter, int flag);
};
class PartitionManager : public BfmeWideForwardB
{
public:
	Object *rva009F2700(const Coord3D *pos, const Region3D *region,
		Real maxDist, Int flag, PartitionFilter *filter);
};
extern PartitionManager *ThePartitionManager;

Object *AI::rva0014DAB0(PolygonTrigger *area, Object *me, const AttackPriorityInfo *info)
{
	if (!me->isAbleToAttack())
		return 0;

	PartitionFilter01095734 filterObvious(me);
	Rva0025ED50RootFilter filterRoot;
	PartitionFilterRejectBuildings filterBldgs(me);
	Rva001DCBB0Filter filterStealth(me, 0);
	PartitionFilterRejectByObjectStatus filterStatus(
		ObjectStatusMask0014DAB0(ObjectStatusMask0014DAB0::kInit, 49),
		ObjectStatusMask0014DAB0(ObjectStatusMask0014DAB0::kInit, 0));
	PartitionFilter010956C4 filterAttack(2, me, 0);

	filterObvious.link(&filterAttack);
	filterObvious.link((PartitionFilter *)&filterBldgs);
	filterObvious.link((PartitionFilter *)&filterStealth);
	filterObvious.link(&filterStatus);
	filterObvious.link(&filterRoot);

	PartitionFilterPolygonTrigger filterArea(area);

	ContainModule0014DAB0 *module;
	if ((me->m_flags94 & 0x10) != 0 && me->m_special != 0 &&
		(module = me->m_special->m_module) != 0)
	{
		Object *target;
		if (module->querySlot50(me, &target))
		{
			if (target == 0)
				return 0;
			filterObvious.link(&filterArea);
			if (!filterObvious.allowChain(target))
				return 0;
			if (target != 0 && info != 0 && info != getDefaultAttackInfo())
			{
				if (info->getPriority(reinterpret_cast<const Thing *>(target)->getTemplate()) == 0)
					return 0;
			}
			return target;
		}
	}

	BfmeVec4CMB bounds;
	reinterpret_cast<BfmeThingCMB *>(area)->bfmeGoCMB(&bounds);
	Region3D region;
	region.lo.x = (Real)bounds.m_bounds.lo.x;
	region.lo.y = (Real)bounds.m_bounds.lo.y;
	region.hi.x = (Real)bounds.m_bounds.hi.x;
	region.hi.y = (Real)bounds.m_bounds.hi.y;

	if (info == 0 || info == getDefaultAttackInfo())
	{
		filterObvious.link(&filterArea);
		Object *closest = ThePartitionManager->rva009F2700(&me->m_pos,
			&region, 9999.9f, 1, &filterObvious);
		if (closest != 0)
			return closest->bfmePostClosest(me, true);
		return 0;
	}

	Object *bestEnemy;
	Int effectivePriority;
	Int actualPriority;
	BfmeWideResult iter = ThePartitionManager->bfmeForwardWideB((int)&region, 1,
		(int)(PartitionFilter *)&filterObvious, 0);
	bestEnemy = 0;
	effectivePriority = 0;
	actualPriority = 0;
	Object *theEnemy;
	while ((theEnemy = iter.next()) != 0)
	{
		Int curPriority = info->getPriority(theEnemy->getTemplate());
		if (curPriority == 0)
			continue;

		ContainModule0014DAB0 *contain = theEnemy->m_contain;
		if (contain != 0)
		{
			Rva0014B880Context priorityInfo;
			priorityInfo.m_priority = curPriority;
			priorityInfo.m_info = info;
			contain->iterateContained(rva0014b880PriorityMaximum, &priorityInfo, true);
			if (priorityInfo.m_priority > curPriority)
				curPriority = priorityInfo.m_priority;
		}

		Real distSqr = me->getDistanceSquared(theEnemy);
		Real dist = sqrt(distSqr);
		Int modifier = (Int)(dist / TheAI->m_aiData->m_attackPriorityDistanceModifier);
		Int modPriority = curPriority - modifier;
		if (modPriority < 1)
			modPriority = 1;
		if (modPriority > effectivePriority ||
			(modPriority == effectivePriority && curPriority > actualPriority))
		{
			if (filterArea.allowChain(theEnemy))
			{
				effectivePriority = modPriority;
				actualPriority = curPriority;
				bestEnemy = theEnemy;
			}
		}
	}

	Object *result = bestEnemy ? bestEnemy->bfmePostClosest(me, true) : 0;
	return result;
}
