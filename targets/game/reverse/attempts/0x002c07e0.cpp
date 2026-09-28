// ?lookForInnerTarget@GiantBirdGuardMachine@@QAE_NXZ
// partial score=0.897 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /FAsc

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum Relationship { ENEMIES = 0 };
enum KindOfType { KINDOF_006C = 0x6C };

struct Coord3D
{
	Real x, y, z;
};

template <unsigned int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags() {}
	BitFlags(BogusInitType, Int bit);
	unsigned int m_words[(NUMBITS + 31) / 32];
};

class Object;
class Player;
class PolygonTrigger;

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	Bool isAbleToAttack() const;
	Relationship getRelationship(const Object *other) const;
	Player *getControllingPlayer() const;
	Bool bfmeIsComputerControlled() const;
	Object *bfmePostClosest(const Object *owner, Bool add);
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
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *position) const;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class Rva002BD630TeamFactory
{
public:
	void *find(Int id);
};

class AI
{
public:
	Object *findEnemyNear(Object *owner, Real range, Int flags, Int kind, Int maxCount);
};

class Rva002BD020AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *object, Int flags);
};

class BfmeThingDTJ
{
public:
	Real bfmeGoDTJ();
};

class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *position) const;
};

class PartitionFilter
{
public:
	virtual Bool allow(Object *object) { return false; }
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

static void setFilterVptr(PartitionFilter *filter, UnsignedInt vptr)
{
	*reinterpret_cast<UnsignedInt *>(filter) = vptr;
}

class __declspec(novtable) PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(const Object *object, Int flags)
	{
		m_next = 0;
		setFilterVptr(this, 0x01085DC0);
		m_object = object;
		m_flags = flags;
	}

	~PartitionFilterRelationship()
	{
		setFilterVptr(this, 0x01083B5C);
	}

	virtual Bool allow(Object *object);
	const Object *m_object;
	Int m_flags;
};

class __declspec(novtable) PartitionFilterPolygonTrigger : public PartitionFilter
{
public:
	PartitionFilterPolygonTrigger(const PolygonTrigger *trigger)
	{
		m_next = 0;
		setFilterVptr(this, 0x01095714);
		m_trigger = trigger;
	}

	~PartitionFilterPolygonTrigger()
	{
		setFilterVptr(this, 0x01083B5C);
	}

protected:
	virtual Bool allow(Object *object);

private:
	friend class GiantBirdGuardMachine;
	const PolygonTrigger *m_trigger;
};

class __declspec(novtable) Rva00C95FBCFilter : public PartitionFilter
{
public:
	Rva00C95FBCFilter()
	{
		m_next = 0;
		setFilterVptr(this, 0x01095FBC);
	}

	~Rva00C95FBCFilter()
	{
		setFilterVptr(this, 0x01083B5C);
	}
};

class __declspec(novtable) Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter()
	{
		m_next = 0;
		setFilterVptr(this, 0x01083B80);
	}

	~Rva0025ED50RootFilter()
	{
		setFilterVptr(this, 0x01083B5C);
	}
};

typedef BitFlags<192> KindOfMaskType;
#define KINDOFMASK_NONE (*(const KindOfMaskType *)0x012ED8B8)

template<> KindOfMaskType::BitFlags(KindOfMaskType::BogusInitType, Int);

class __declspec(novtable) PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const KindOfMaskType &mustBeClear,
		const KindOfMaskType &mustBeSet) throw();
	~PartitionFilterAcceptByKindOf()
	{
		setFilterVptr(this, 0x01083B5C);
	}
	virtual Bool allow(Object *object);
	KindOfMaskType m_mustBeClear;
	KindOfMaskType m_mustBeSet;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real range, Int type,
		PartitionFilter *filters);
};

class GiantBirdGuardMachine
{
public:
	Bool lookForInnerTarget();

	unsigned char m_unknown00[0x10];
	Object *m_owner;
	unsigned char m_unknown14[0x30];
	Int m_teamID;
	Int m_otherID;
	PolygonTrigger *m_area;
	Coord3D m_position;
	unsigned char m_unknown5C[0x0C];
	Bool m_explicitPosition;
	unsigned char m_unknown69[3];
	Int m_field6C;
	Int m_guardMode;
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheBfmeTeamFactory (*(Rva002BD630TeamFactory **)0x012ED810)
#define TheBfmeAI (*(AI **)0x012EF214)
#define TheBfmePartitionManager (*(PartitionManager **)0x012ED5B8)

Bool GiantBirdGuardMachine::lookForInnerTarget()
{
	Object *owner = m_owner;
	if (!owner->isAbleToAttack())
		return false;

	StateMachine *attackMachine = *(StateMachine **)(
		(char *)*(void **)((char *)owner + 0x204) + 0x30);
	Object *currentTarget = attackMachine->getGoalObject();
	if (currentTarget && currentTarget->getRelationship(owner) == ENEMIES)
	{
		m_field6C = *(Int *)((char *)currentTarget + 0x74);
		return true;
	}

	Team *team = *(Team **)((char *)owner + 0x23C);
	if (*(Bool *)((char *)(*(void **)((char *)team + 4)) + 0x1C2))
	{
		currentTarget = team->getTeamTargetObject();
		if (currentTarget)
		{
			m_field6C = *(Int *)((char *)currentTarget + 0x74);
			return true;
		}
	}

	Object *guardTarget = TheBfmeGameLogic->findObjectByID(m_teamID);
	Rva002BD630TeamFactory *teamFactory = TheBfmeTeamFactory;
	Team *guardTeam = (Team *)teamFactory->find(m_otherID);
	Coord3D position;
	if (guardTarget)
	{
		position = *(Coord3D *)((char *)guardTarget + 0x38);
	}
	else if (guardTeam)
	{
		guardTeam->getEstimateTeamPosition_000EDCD0(&position);
	}
	else
	{
		position = m_position;
	}

	PolygonTrigger *area = m_area;
	{
	Real range = Rva002BD020AI::getAdjustedVisionRangeForObject(owner, 7);
	PartitionFilterRelationship relationshipFilter(owner, 1);
	PartitionFilterPolygonTrigger areaFilter(area);
	Bool canUseAIFind = true;

	if (area)
	{
		UnsignedInt scanRate = *(UnsignedInt *)((char *)*(void **)((char *)*(void **)0x012EF214 + 0x14) + 0x40);
		UnsignedInt changedFrame = *(UnsignedInt *)((char *)TheBfmeGameLogic + 0x16C);
		UnsignedInt scanLimit = scanRate + changedFrame;
		if (*(UnsignedInt *)((char *)TheBfmeGameLogic + 0x3C) < scanLimit)
			canUseAIFind = false;

		relationshipFilter.link(&areaFilter);
		range = ((BfmeThingDTJ *)area)->bfmeGoDTJ();
		area->getCenterPoint(&position);
	}

	Rva00C95FBCFilter flyingFilter;
	if (m_guardMode == 2)
		relationshipFilter.link(&flyingFilter);
	Rva0025ED50RootFilter rootFilter;
	relationshipFilter.link(&rootFilter);
	KindOfMaskType mustBeSet;
	mustBeSet.m_words[0] = 0;
	mustBeSet.m_words[1] = 0;
	mustBeSet.m_words[2] = 0;
	mustBeSet.m_words[3] = 0;
	mustBeSet.m_words[4] = 0;
	mustBeSet.m_words[5] = 0;
	volatile unsigned int *thirdWord = &mustBeSet.m_words[2];
	*thirdWord |= 0x200000;
	PartitionFilterAcceptByKindOf kindFilter(KINDOFMASK_NONE, mustBeSet);
	relationshipFilter.link(&kindFilter);

	Object *target = 0;
	if (canUseAIFind && !owner->bfmeIsComputerControlled())
	{
		Int kind = *(Int *)((char *)*(void **)((char *)owner + 0x204) + 0x70);
		target = TheBfmeAI->findEnemyNear(owner, range, 0x4A, kind, 0);
		if (!target && owner->getControllingPlayer() &&
			*(unsigned char *)((char *)owner->getControllingPlayer() + 0x29D))
			target = TheBfmeAI->findEnemyNear(owner, range, 0x4A, 0, 0);
	}

	if (!target || (area && !areaFilter.PartitionFilterPolygonTrigger::allow(target)))
		target = TheBfmePartitionManager->getClosestObject(&position, 99999.0f, 1,
			&relationshipFilter);

	if (target && target->isKindOf((KindOfType)0x6C))
	{
		target = target->bfmePostClosest(owner, false);
		if (target)
		{
			m_field6C = *(Int *)((char *)target + 0x74);
			return true;
		}
	}
	}

	if (m_explicitPosition)
	{
		PartitionFilterRelationship fallbackRelationship(owner, 1);
		PartitionFilterPolygonTrigger fallbackArea(area);
		if (area)
			fallbackRelationship.link(&fallbackArea);
		Rva0025ED50RootFilter fallbackRoot;
		fallbackRelationship.link(&fallbackRoot);
		KindOfMaskType fallbackMask(KindOfMaskType::kInit, 53);
		PartitionFilterAcceptByKindOf fallbackKind(KINDOFMASK_NONE, fallbackMask);
		fallbackRelationship.link(&fallbackKind);
		Rva00C95FBCFilter fallbackFlying;
		Object *target = 0;
		if (m_guardMode == 2)
			fallbackRelationship.link(&fallbackFlying);

		target = TheBfmePartitionManager->getClosestObject(&m_position, 99999.0f, 1,
			&fallbackRelationship);
		if (target)
		{
			m_field6C = *(Int *)((char *)target + 0x74);
			return true;
		}
	}

	return false;
}
