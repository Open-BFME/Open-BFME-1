// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source
// stlport
// readable body of ?lookForInnerTarget@GiantBirdGuardMachine@@: game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardMachine.cpp
//
// GiantBirdGuardMachine::lookForInnerTarget, retail 0x002C07E0 (1106 bytes).
//
// Identity: the matched GiantBirdGuardReturnState::update calls this body
// through ILT 0x0002F527 on its machine, and the matched constructor at
// 0x002C05C0 builds GiantBirdGuardMachine on AIGuardMachine. The body is
// Zero Hour's AIGuardMachine::lookForInnerTarget (AIGuard.cpp) with BFME's
// additions, all read from the retail body:
//  * an enemy goal object of the owner's AI state machine is taken first;
//  * the guard position also falls back to the team to guard (+0x48), as in
//    the matched AIGuardMachine::getGuardScanPos (0x0015C330);
//  * the filters are linked (PartitionFilter::link) rather than put in an
//    array: enemies, the guard area, flying-only, the 0x01083B80 root filter
//    and a kind filter rejecting UNATTACKABLE;
//  * a non-computer owner first asks AI::findEnemyNear (flags 0x4A), and the
//    partition query only runs when that finds nothing or the result lies
//    outside the guard area; the scan waits until the trigger-area frame
//    plus the guard scan rate has passed;
//  * a HORDE target is resolved to a member (Object::bfmePostClosest);
//  * failing all that, an area guard with the +0x68 flag set searches the
//    area once more with a 99999 range.
// Kind names come from retail's KindOf name table at VA 0x012AA068
// (53 UNATTACKABLE, 108 HORDE).
//
// Shape notes, each measured against the retail bytes: the vision range is a
// function-scope local (inside the first filter block it stops VC7.1 sharing
// the two filter sets' stack slots), the first block's mask is a default mask
// with one bit set while the second calls the out-of-line one-index kInit
// constructor, the guard-area filter's allow is a direct call on the local,
// and the scan-rate term is the left operand of the frame sum.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;
typedef float Real;
typedef unsigned int TeamID;

#define NULL 0

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};
#define BFME_HAVE_COORD3D

enum KindOfType
{
	KINDOF_UNATTACKABLE = 53,
	KINDOF_HORDE = 108
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Team;
class Player;
class AIUpdateInterface;

#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType t) const; \
	const Coord3D *getPosition() const { return &m_cachedPos; }
#define OBJECT_TU_MEMBERS \
	Int getID() const { return m_id; } \
	Team *getTeam() const { return m_team; } \
	AIUpdateInterface *getAI() const { return m_ai; } \
	Bool isAbleToAttack() const; \
	Relationship getRelationship(const Object *that) const; \
	Bool bfmeIsComputerControlled() const; \
	Player *getControllingPlayer() const; \
	Object *bfmePostClosest(const Object *that, Bool flag);
#include "GameLogic/Object/object.h"

class StateMachine
{
public:
	Object *getGoalObject();
};

class AIUpdateInterface
{
public:
	StateMachine *getStateMachine() const { return m_stateMachine; }
	Int getInt70() const { return m_int70; }

private:
	UnsignedByte m_unmodelled00[0x30];
	StateMachine *m_stateMachine;					///< +0x30
	UnsignedByte m_unmodelled34[0x3c];
	Int m_int70;										///< +0x70
};

class Player
{
public:
	Bool getFlag29D() const { return m_flag29d != 0; }

private:
	UnsignedByte m_unmodelled000[0x29d];
	UnsignedByte m_flag29d;
};

struct TeamTemplateInfoView
{
	UnsignedByte m_unmodelled000[0x1c2];
	Bool m_attackCommonTarget;
};

class TeamPrototype
{
public:
	const TeamTemplateInfoView *getTemplateInfo() const { return (const TeamTemplateInfoView *)this; }
};

class Team
{
public:
	const TeamPrototype *getPrototype() const { return m_proto; }
	Object *getTeamTargetObject();
	void getPosition(Coord3D *position);

private:
	void *m_vptr;
	TeamPrototype *m_proto;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	UnsignedInt getFrame() const { return m_frame; }
	UnsignedInt getFrameObjectsChangedTriggerAreas() const { return m_frameObjectsChangedTriggerAreas; }

private:
	UnsignedByte m_unmodelled000[0x3c];
	UnsignedInt m_frame;								///< +0x3C
	UnsignedByte m_unmodelled040[0x12c];
	UnsignedInt m_frameObjectsChangedTriggerAreas;		///< +0x16C
};

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

struct TAiData
{
	UnsignedByte m_unmodelled00[0x40];
	UnsignedInt m_guardEnemyScanRate;					///< +0x40
};

class AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *obj, Int factorsToConsider);
	Object *findEnemyNear(Object *obj, Real range, Int flags, Int a, Int b);
	const TAiData *getAiData() const { return m_aiData; }

private:
	UnsignedByte m_unmodelled00[0x14];
	TAiData *m_aiData;									///< +0x14
};

class PolygonTrigger
{
public:
	Real getRadius() const;
	void getCenterPoint(Coord3D *pOutCenter) const;
};

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags() {}
	BitFlags(BogusInitType k, Int idx1);
	void set(Int i) { m_bits.set(i); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *obj) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	enum RelationshipAllowTypes
	{
		ALLOW_ALLIES = (1 << ALLIES),
		ALLOW_ENEMIES = (1 << ENEMIES),
		ALLOW_NEUTRAL = (1 << NEUTRAL)
	};
	PartitionFilterRelationship(const Object *obj, Int flags, Bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *objOther);
	virtual Int getPlayerMask();

	const Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class PartitionFilterPolygonTrigger : public PartitionFilter
{
public:
	PartitionFilterPolygonTrigger(const PolygonTrigger *trigger) : m_trigger(trigger) {}
protected:
	virtual Bool allow(Object *other);

	const PolygonTrigger *m_trigger;

	friend class GiantBirdGuardMachine;
};

class PartitionFilterIsFlying : public PartitionFilter
{
public:
	PartitionFilterIsFlying() {}
	virtual Bool allow(Object *objOther);
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *obj);
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);
	virtual Bool allow(Object *obj);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1,
	FROM_BOUNDINGSPHERE_2D = 2,
	FROM_BOUNDINGSPHERE_3D = 3
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, Real maxDist,
		DistanceCalculationType dc, PartitionFilter *filters);
};

extern GameLogic *TheGameLogic;
extern TeamFactory *TheTeamFactory;
extern AI *TheAI;
extern PartitionManager *ThePartitionManager;

enum GuardMode
{
	GUARDMODE_NORMAL = 0,
	GUARDMODE_GUARD_WITHOUT_PURSUIT = 1,
	GUARDMODE_GUARD_FLYING_UNITS_ONLY = 2
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
// BFME offsets as in AIGuard_getGuardScanPos.cpp.
class AIGuardMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *findTargetToGuardByID() { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() { return TheTeamFactory->findTeamByID(m_teamToGuard); }
	const Coord3D *getPositionToGuard() const { return &m_positionToGuard; }
	const PolygonTrigger *getAreaToGuard() const { return m_areaToGuard; }
	GuardMode getGuardMode() const { return m_guardMode; }
	void setNemesisID(Int id) { m_nemesisToAttack = id; }

protected:
	UnsignedByte m_unmodelled00[0x10];
	Object *m_owner;									///< +0x10 StateMachine owner
	UnsignedByte m_unmodelled14[0x30];
	Int m_targetToGuard;								///< +0x44
	TeamID m_teamToGuard;								///< +0x48
	const PolygonTrigger *m_areaToGuard;				///< +0x4C
	Coord3D m_positionToGuard;							///< +0x50
	Coord3D m_areaBox;									///< +0x5C
	Bool m_areaFlag;									///< +0x68
	Int m_nemesisToAttack;								///< +0x6C
	GuardMode m_guardMode;								///< +0x70
};

class GiantBirdGuardMachine : public AIGuardMachine
{
public:
	Bool lookForInnerTarget(void);
};

// ?lookForInnerTarget@GiantBirdGuardMachine@@QAE_NXZ
Bool GiantBirdGuardMachine::lookForInnerTarget(void)
{
	Object *owner = getOwner();
	if (!owner->isAbleToAttack())
		return false;

	Object *goal = owner->getAI()->getStateMachine()->getGoalObject();
	if (goal && goal->getRelationship(owner) == ENEMIES)
	{
		setNemesisID(goal->getID());
		return true;
	}

	// Check if team auto targets same victim.
	if (owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget)
	{
		Object *teamVictim = owner->getTeam()->getTeamTargetObject();
		if (teamVictim)
		{
			setNemesisID(teamVictim->getID());
			return true;
		}
	}

	Object *targetToGuard = findTargetToGuardByID();
	Team *teamToGuard = findTeamToGuardByID();
	Coord3D pos;
	if (targetToGuard)
		pos = *targetToGuard->getPosition();
	else if (teamToGuard)
		teamToGuard->getPosition(&pos);
	else
		pos = *getPositionToGuard();

	const PolygonTrigger *area = getAreaToGuard();
	Object *target = NULL;
	Real visionRange = AI::getAdjustedVisionRangeForObject(owner, 7);
	{
		PartitionFilterRelationship f1(owner, PartitionFilterRelationship::ALLOW_ENEMIES, false);
		PartitionFilterPolygonTrigger f3(area);
		Bool scan = true;
		if (area)
		{
			UnsignedInt checkFrame = TheAI->getAiData()->m_guardEnemyScanRate
				+ TheGameLogic->getFrameObjectsChangedTriggerAreas();
			if (TheGameLogic->getFrame() < checkFrame)
				scan = false;
			f1.link(&f3);
			visionRange = area->getRadius();
			area->getCenterPoint(&pos);
		}

		PartitionFilterIsFlying f4;
		if (getGuardMode() == GUARDMODE_GUARD_FLYING_UNITS_ONLY)
			f1.link(&f4);
		Rva0025ED50RootFilter root;
		f1.link(&root);
		KindOfMaskType unattackable;
		unattackable.set(KINDOF_UNATTACKABLE);
		PartitionFilterAcceptByKindOf kindFilter(KINDOFMASK_NONE, unattackable);
		f1.link(&kindFilter);

		if (scan)
		{
			if (!owner->bfmeIsComputerControlled())
			{
				target = TheAI->findEnemyNear(owner, visionRange, 0x4a,
					owner->getAI()->getInt70(), 0);
				if (!target && owner->getControllingPlayer()
					&& owner->getControllingPlayer()->getFlag29D())
					target = TheAI->findEnemyNear(owner, visionRange, 0x4a, 0, 0);
			}
			if (!target || (area && !f3.allow(target)))
				target = ThePartitionManager->getClosestObject(&pos, visionRange,
					FROM_CENTER_3D, &f1);
		}
	}

	if (target)
	{
		if (target->isKindOf(KINDOF_HORDE))
			target = target->bfmePostClosest(owner, false);
		if (target)
		{
			setNemesisID(target->getID());
			return true;
		}
	}

	if (area && m_areaFlag)
	{
		PartitionFilterRelationship f1(owner, PartitionFilterRelationship::ALLOW_ENEMIES, false);
		PartitionFilterPolygonTrigger f3(area);
		f1.link(&f3);
		Rva0025ED50RootFilter root;
		f1.link(&root);
		PartitionFilterAcceptByKindOf kindFilter(KINDOFMASK_NONE,
			KindOfMaskType(KindOfMaskType::kInit, KINDOF_UNATTACKABLE));
		f1.link(&kindFilter);
		PartitionFilterIsFlying f4;
		if (getGuardMode() == GUARDMODE_GUARD_FLYING_UNITS_ONLY)
			f1.link(&f4);
		target = ThePartitionManager->getClosestObject(&pos, 99999.0f, FROM_CENTER_3D, &f1);
		if (target)
		{
			setNemesisID(target->getID());
			return true;
		}
	}

	return false;
}
