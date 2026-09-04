// ?lookForInnerTarget@AIGuardMachine@@QAE_NXZ
// partial score=0.55 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// AIGuardMachine::lookForInnerTarget, retail 0x0015D530, 2514 bytes.
// ZH twin in AIGuard.cpp is present-unmatched; BFME expands it with a linked
// filter list, a goal-object early out, team-id position, and a second scan.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef int ObjectID;
typedef int TeamID;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0,
	GUARDMODE_GUARD_WITHOUT_PURSUIT = 1,
	GUARDMODE_GUARD_FLYING_UNITS_ONLY = 2
};

class Object;
class Team;
class TeamPrototype;
class PolygonTrigger;
class StateMachine;
class AIUpdateInterface;
class Weapon;
class WeaponTemplate;
class Module;
class Overridable;

struct Coord3D
{
	Real x, y, z;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt m_pad00[0x0F];
	UnsignedInt m_frame;					// +0x3C
};

extern GameLogic *TheGameLogic;				// 0x012F0898

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

extern TeamFactory *TheTeamFactory;			// 0x012ED810

class AI
{
public:
	char m_pad00[0x14];
	struct AiData
	{
		char m_pad[0x40];
		UnsignedInt m_guardEnemyScanRate;	// +0x40
	} *m_aiData;							// +0x14
};

extern AI *TheAI;							// 0x012EF214

class MemoryPoolFactory
{
public:
	void *createMemoryPool(const char *name, int a, int b, int c);
};

extern MemoryPoolFactory *TheMemoryPoolFactory;	// 0x012ED600

class PartitionFilter
{
public:
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *obj) { return true; }
	PartitionFilter *m_next;
};

class FilterList
{
public:
	FilterList() : m_head(0) {}
	~FilterList() {}
	FilterList *append(PartitionFilter *filter);
	PartitionFilter *m_head;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(const Object *obj, Int flags)
		: m_obj(obj), m_flags(flags), m_extra(0)
	{
		m_next = 0;
	}
	const Object *m_obj;
	Int m_flags;
	char m_extra;
};

class PartitionFilterPossibleToAttack : public PartitionFilter
{
public:
	PartitionFilterPossibleToAttack(Int attackType, const Object *obj, Int cmd)
		: m_obj(obj), m_attackType(attackType), m_cmd(cmd)
	{
		m_next = 0;
	}
	const Object *m_obj;
	Int m_attackType;
	Int m_cmd;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *obj);
	~PartitionFilterSameMapStatus();
	const Object *m_obj;
};

class PartitionFilterPolygonTrigger : public PartitionFilter
{
public:
	PartitionFilterPolygonTrigger(const PolygonTrigger *area)
		: m_area(area)
	{
		m_next = 0;
	}
	const PolygonTrigger *m_area;
};

class PartitionFilterIsFlying : public PartitionFilter
{
public:
	PartitionFilterIsFlying() { m_next = 0; }
};

class PartitionFilterRejectByKindOf
{
public:
	PartitionFilterRejectByKindOf(const void *mustBeSet, Int flags);
	~PartitionFilterRejectByKindOf();
	char m_pad[0x20];
};

class PartitionFilterLineOfSight : public PartitionFilter
{
public:
	PartitionFilterLineOfSight(const Coord3D *pos, const Object *obj)
		: m_pos(pos), m_obj(obj)
	{
		m_next = 0;
	}
	const Coord3D *m_pos;
	const Object *m_obj;
};

class PartitionFilterCollect : public PartitionFilter
{
public:
	PartitionFilterCollect() : m_begin(0), m_end(0), m_cap(0) { m_next = 0; }
	~PartitionFilterCollect();
	ObjectID *m_begin;
	ObjectID *m_end;
	ObjectID *m_cap;
};

class BfmeWideResult
{
public:
	BfmeWideResult() : m_value(0) {}
	BfmeWideResult(const BfmeWideResult &that) : m_value(that.m_value) {}
	~BfmeWideResult() {}
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateInRange(Coord3D *pos, Real range, Int from, FilterList *filters, Int sorted);
	Object *getClosestObject(Coord3D *pos, Real range, Int from, FilterList *filters);
};

extern PartitionManager *ThePartitionManager;	// 0x012ED5B8

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	Overridable *m_next;
};

class ThingTemplate : public Overridable
{
public:
	char m_pad[0xD8];
	UnsignedInt m_statusD8;					// +0xD8
	UnsignedInt m_statusD4;					// actually +0xD4 used separately
};

class Object
{
public:
	Bool isAbleToAttack() const;
	Relationship getRelationship(const Object *that) const;
	Module *findModule(int nameKey);
	Weapon *getCurrentWeapon(int *slot);
	Int getScaleKind() const;
	Object *resolveContained(Int flag, Object *viewer);

	char m_pad00[0x38];
	Coord3D m_pos;							// +0x38
	char m_pad3C[0x74 - 0x44];
	ObjectID m_id;							// +0x74
	char m_pad78[0x204 - 0x78];
	AIUpdateInterface *m_ai;				// +0x204
	char m_pad208[0x23C - 0x208];
	Team *m_team;							// +0x23C
};

class AIUpdateInterface
{
public:
	char m_pad[0x30];
	StateMachine *m_machine;				// +0x30
};

class StateMachine
{
public:
	Object *getGoalObject();
};

class Team
{
public:
	Object *getTeamTargetObject();
	void getPosition(Coord3D *out);
	TeamPrototype *m_proto;					// +4
};

class TeamPrototype
{
public:
	char m_pad[0x1C2];
	unsigned char m_attackCommonTarget;		// +0x1C2
};

class PolygonTrigger
{
public:
	Real getRadius();
	void getCenter(Coord3D *out);
};

class Weapon
{
public:
	WeaponTemplate *m_template;				// +4
};

class WeaponTemplate
{
public:
	unsigned char isHijackGuard();			// 0x001E1770-like byte at +4
};

class Module
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual Bool slot18();
};

class BfmeGap951
{
public:
	Real gapTo(const Coord3D *pos);
};

class KindOfBox
{
public:
	void setMask(const void *mask, Int flags);
	char m_pad[0x20];
};

extern void *g_kindOfMask;					// 0x012ED8B8
extern int g_nameKeyOnce;					// 0x012EF284
extern int g_moduleNameKey;					// 0x012EF280
extern const char g_moduleName[];			// 0x01085EC0

Real _bfme_getStdGuardRange(const Object *obj);
Bool bfmePointInArea(const void *box, const Object *obj);
extern "C" double atan2(double y, double x);

class AIGuardMachine
{
public:
	Bool lookForInnerTarget();

	char m_pad00[0x10];
	Object *m_owner;						// +0x10
	char m_pad14[0x44 - 0x14];
	ObjectID m_targetToGuard;				// +0x44
	TeamID m_teamToGuard;					// +0x48
	PolygonTrigger *m_areaToGuard;			// +0x4C
	Coord3D m_positionToGuard;				// +0x50
	Int m_areaA;							// +0x5C
	Int m_areaB;							// +0x60
	Real m_areaC;							// +0x64
	unsigned char m_areaFlag;				// +0x68
	char m_pad69[3];
	ObjectID m_nemesisToAttack;				// +0x6C
	GuardMode m_guardMode;					// +0x70
	UnsignedInt m_nextScanFrame;			// +0x74
};

Bool AIGuardMachine::lookForInnerTarget()
{
	Object *owner = m_owner;
	if (!owner->isAbleToAttack())
		return false;

	Object *goal = owner->m_ai->m_machine->getGoalObject();
	if (goal && goal->getRelationship(owner) == ENEMIES)
	{
		m_nemesisToAttack = goal->m_id;
		return true;
	}

	if (owner->m_team->m_proto->m_attackCommonTarget)
	{
		Object *teamVictim = owner->m_team->getTeamTargetObject();
		if (teamVictim)
		{
			m_nemesisToAttack = teamVictim->m_id;
			return true;
		}
	}

	Object *targetToGuard = TheGameLogic->findObjectByID(m_targetToGuard);
	Team *guardTeam = TheTeamFactory->findTeamByID(m_teamToGuard);
	Coord3D pos;
	if (targetToGuard)
		pos = targetToGuard->m_pos;
	else if (guardTeam)
		guardTeam->getPosition(&pos);
	else
		pos = m_positionToGuard;

	PolygonTrigger *area = m_areaToGuard;

	PartitionFilterRelationship fRel(owner, 1);
	PartitionFilterPossibleToAttack fAttack(2, owner, 0);
	PartitionFilterSameMapStatus fMap(owner);
	PartitionFilterRejectByKindOf fKind(g_kindOfMask, 2);
	KindOfBox kindBox;
	kindBox.setMask(g_kindOfMask, 2);
	PartitionFilterRelationship fRel2(owner, 0);
	PartitionFilterPolygonTrigger fPoly(area);
	PartitionFilterIsFlying fFly;
	PartitionFilterLineOfSight fLos(&pos, owner);
	PartitionFilterCollect collect;
	Coord3D centerScratch;
	(void)centerScratch;

	FilterList filters;
	filters.append(&fMap);
	filters.append(&fRel);
	filters.append((PartitionFilter *)&fKind);

	Real visionRange = _bfme_getStdGuardRange(owner);
	Bool scanOk = true;
	if (area)
	{
		UnsignedInt checkFrame = m_nextScanFrame + TheAI->m_aiData->m_guardEnemyScanRate;
		if (TheGameLogic->m_frame < checkFrame)
			scanOk = false;
		else
			m_nextScanFrame = TheGameLogic->m_frame;
		filters.append(&fPoly);
		visionRange = area->getRadius();
		area->getCenter(&pos);
	}

	if (m_guardMode == GUARDMODE_GUARD_FLYING_UNITS_ONLY)
		filters.append(&fFly);

	Weapon *weapon = owner->getCurrentWeapon(0);
	if (weapon)
	{
		WeaponTemplate *wt = weapon->m_template;
		if (!wt->isHijackGuard() && owner->getScaleKind() != 1)
			filters.append(&fLos);
	}

	filters.append(&collect);
	filters.append((PartitionFilter *)&kindBox);

	if ((g_nameKeyOnce & 1) == 0)
	{
		g_nameKeyOnce |= 1;
		g_moduleNameKey = (int)TheMemoryPoolFactory->createMemoryPool(g_moduleName, 0, 0, 0);
	}

	Object *target = 0;
	if (scanOk)
	{
		BfmeWideResult iter = ThePartitionManager->iterateInRange(&pos, visionRange, 1, &filters, 1);
		void *cur = iter.m_value;
		(void)cur;
		if (!target && collect.m_begin != collect.m_end)
		{
			ObjectID *it = collect.m_begin;
			while (it != collect.m_end)
			{
				Object *cand = TheGameLogic->findObjectByID(*it);
				if (cand)
				{
					if (target)
					{
						Real dOld = ((BfmeGap951 *)target)->gapTo(&pos);
						Real dNew = ((BfmeGap951 *)cand)->gapTo(&pos);
						if (dNew < dOld)
							target = cand;
					}
					else
						target = cand;
				}
				++it;
			}
		}
	}

	if (!target && !area)
	{
		Real dx = pos.x - owner->m_pos.x;
		Real dy = pos.y - owner->m_pos.y;
		Real limit = visionRange;
		if (dx * dx + dy * dy <= limit * limit)
			target = ThePartitionManager->getClosestObject(&owner->m_pos, limit, 1, &filters);
	}

	if (target)
	{
		target = target->resolveContained(1, owner);
		if (target)
		{
			m_nemesisToAttack = target->m_id;
			return true;
		}
	}

	if (area && m_areaFlag)
	{
		double a0 = atan2((double)m_areaC, (double)m_areaA);
		double a1 = atan2((double)m_areaC, (double)m_areaB);
		double a2 = atan2((double)m_areaC, (double)pos.x);
		(void)a0;
		(void)a1;
		(void)a2;
		Int box[3];
		box[0] = (Int)a0;
		box[1] = (Int)a2;
		box[2] = (Int)a1;
		if (!bfmePointInArea(box, (Object *)area))
		{
			PartitionFilterRelationship fRelB(owner, 1);
			PartitionFilterPossibleToAttack fAttackB(2, owner, 0);
			PartitionFilterSameMapStatus fMapB(owner);
			FilterList filtersB;
			filtersB.append(&fRelB);
			filtersB.append(&fAttackB);
			filtersB.append(&fMapB);
			if (m_guardMode == GUARDMODE_GUARD_FLYING_UNITS_ONLY)
			{
				PartitionFilterIsFlying fFlyB;
				filtersB.append(&fFlyB);
			}
			BfmeWideResult iterB = ThePartitionManager->iterateInRange(&pos, visionRange, 1, &filtersB, 1);
			(void)iterB;
		}
	}

	return false;
}
