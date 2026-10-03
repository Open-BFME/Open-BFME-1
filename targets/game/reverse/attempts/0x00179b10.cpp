// ?update@AIFollowPathAsTeamState@@UAE?AW4StateReturnType@@XZ
// partial score=0.5827 date=2026-10-03
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME ?update@AIFollowPathAsTeamState@@UAE?AW4StateReturnType@@XZ at retail
// RVA 0x00179B10 (1517 bytes).
//
// BANK ONLY. Native STLport vector access improves the served 1515B/655dif
// to 1520B/627dif against full1517B through RET17A0FC, quality0.5827.
// Loop threading/cold update block placement and x87 dx retention remain wrong.
// Guard, redundant pointer test, count accessor, direct/template sqr controls
// did not improve the served bank; explicit labels worsened native vector.
// Inherited semantic names, hand-written Object/State/AI views, dynamic slot
// contracts and all56 relocation bindings remain unaudited for promotion.
// Vtable layout alone does not establish the old asserted source identity.

#include <math.h>
#include <vector>

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;
class CRCParameterCheck;
class LocomotorSet;

extern Bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

struct Coord3DBase
{
	Real x;
	Real y;
	Real z;
};

struct Coord3D : public Coord3DBase
{
	void add(const Coord3DBase *other);			// 0x000B6570
	Coord3D &Scale(Real scale);				// 0x0014FFD0
};

Real normalizeAngle(Real angle);
inline Real sqr(Real x) { return x * x; }

#define BFME_SLOT(n) virtual void slot##n() = 0;

class BfmeCurrentState
{
public:
	BFME_SLOT(000) BFME_SLOT(004) BFME_SLOT(008) BFME_SLOT(00c)
	BFME_SLOT(010) BFME_SLOT(014) BFME_SLOT(018)
	virtual Bool isIdle() const = 0;			// +0x1c
};

class StateMachine
{
public:
	BFME_SLOT(000) BFME_SLOT(004) BFME_SLOT(008) BFME_SLOT(00c)
	virtual StateReturnType updateStateMachine() = 0;	// +0x10
	BFME_SLOT(014) BFME_SLOT(018) BFME_SLOT(01c)
	virtual StateReturnType setState(UnsignedInt state) = 0;	// +0x20
	BFME_SLOT(024) BFME_SLOT(028) BFME_SLOT(02c)
	BFME_SLOT(030) BFME_SLOT(034)
	virtual void setGoalObject(Object *object) = 0;		// +0x38

	Object *getGoalObject();				// 0x000A1490
	void setGoalPosition(const Coord3D *pos);		// 0x000A0880

	unsigned char m_pad04[0x10 - 4];
	Object *m_owner;					// +0x10
	unsigned char m_pad14[0x1c - 0x14];
	BfmeCurrentState *m_currentState;			// +0x1c

	Bool isInIdleState() const
	{
		return m_currentState ? m_currentState->isIdle() : true;
	}
};

struct Rva0016FFD0Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Rva0016FFD0Path
{
public:
 Rva0016FFD0Coord3D *getPoint(int index) {
  if (index >= 0) {
   if ((unsigned)index < m_points.size())
    return &m_points[index];
  }
  return 0;
 }
 unsigned char m_pad00[0x44];
 std::vector<Rva0016FFD0Coord3D> m_points;
};

class AIUpdateInterface
{
public:
	BFME_SLOT(000) BFME_SLOT(004) BFME_SLOT(008) BFME_SLOT(00c)
	BFME_SLOT(010) BFME_SLOT(014) BFME_SLOT(018) BFME_SLOT(01c)
	BFME_SLOT(020) BFME_SLOT(024) BFME_SLOT(028) BFME_SLOT(02c)
	BFME_SLOT(030) BFME_SLOT(034) BFME_SLOT(038) BFME_SLOT(03c)
	BFME_SLOT(040) BFME_SLOT(044) BFME_SLOT(048) BFME_SLOT(04c)
	BFME_SLOT(050) BFME_SLOT(054) BFME_SLOT(058) BFME_SLOT(05c)
	BFME_SLOT(060) BFME_SLOT(064) BFME_SLOT(068) BFME_SLOT(06c)
	BFME_SLOT(070) BFME_SLOT(074) BFME_SLOT(078) BFME_SLOT(07c)
	BFME_SLOT(080) BFME_SLOT(084) BFME_SLOT(088) BFME_SLOT(08c)
	BFME_SLOT(090) BFME_SLOT(094) BFME_SLOT(098) BFME_SLOT(09c)
	BFME_SLOT(0a0) BFME_SLOT(0a4) BFME_SLOT(0a8) BFME_SLOT(0ac)
	BFME_SLOT(0b0) BFME_SLOT(0b4) BFME_SLOT(0b8) BFME_SLOT(0bc)
	BFME_SLOT(0c0) BFME_SLOT(0c4) BFME_SLOT(0c8) BFME_SLOT(0cc)
	BFME_SLOT(0d0) BFME_SLOT(0d4) BFME_SLOT(0d8) BFME_SLOT(0dc)
	BFME_SLOT(0e0) BFME_SLOT(0e4) BFME_SLOT(0e8) BFME_SLOT(0ec)
	BFME_SLOT(0f0) BFME_SLOT(0f4) BFME_SLOT(0f8) BFME_SLOT(0fc)
	BFME_SLOT(100) BFME_SLOT(104) BFME_SLOT(108) BFME_SLOT(10c)
	BFME_SLOT(110) BFME_SLOT(114) BFME_SLOT(118) BFME_SLOT(11c)
	BFME_SLOT(120) BFME_SLOT(124) BFME_SLOT(128) BFME_SLOT(12c)
	BFME_SLOT(130) BFME_SLOT(134) BFME_SLOT(138) BFME_SLOT(13c)
	BFME_SLOT(140) BFME_SLOT(144) BFME_SLOT(148) BFME_SLOT(14c)
	BFME_SLOT(150) BFME_SLOT(154) BFME_SLOT(158) BFME_SLOT(15c)
	BFME_SLOT(160) BFME_SLOT(164) BFME_SLOT(168) BFME_SLOT(16c)
	BFME_SLOT(170) BFME_SLOT(174) BFME_SLOT(178) BFME_SLOT(17c)
	BFME_SLOT(180) BFME_SLOT(184) BFME_SLOT(188) BFME_SLOT(18c)
	BFME_SLOT(190) BFME_SLOT(194) BFME_SLOT(198) BFME_SLOT(19c)
	BFME_SLOT(1a0) BFME_SLOT(1a4) BFME_SLOT(1a8) BFME_SLOT(1ac)
	BFME_SLOT(1b0) BFME_SLOT(1b4) BFME_SLOT(1b8) BFME_SLOT(1bc)
	BFME_SLOT(1c0) BFME_SLOT(1c4) BFME_SLOT(1c8) BFME_SLOT(1cc)
	BFME_SLOT(1d0) BFME_SLOT(1d4) BFME_SLOT(1d8) BFME_SLOT(1dc)
	BFME_SLOT(1e0)
	virtual void setSlot1E4(Real value) = 0;		// +0x1e4
	BFME_SLOT(1e8)
	virtual Bool isDoingGroundMovement() = 0;		// +0x1ec

	Object *checkForCrateToPickup();			// 0x00272F70
	Object *getNextMoodTarget(Bool calm, Bool alwaysAttack);	// ILT 0x00003F58
	Real getCurLocomotorSpeed();				// 0x0026EC30
	void setDesiredSpeed(Real speed);			// 0x0026EDC0
	void friend_startingMove();				// 0x0026F0E0

	Rva0016FFD0Path *getPath() { return m_path; }

	unsigned char m_pad04[0x30 - 4];
	Rva0016FFD0Path *m_path;				// +0x30
	unsigned char m_pad34[0x48 - 0x34];
	int m_field48;						// +0x48
	unsigned char m_pad4c[0x194 - 0x4c];
	int m_currentGoalPathIndex;				// +0x194
	unsigned char m_pad198[0x1a8 - 0x198];
	unsigned char m_locomotorSet[0x335 - 0x1a8];		// +0x1a8
	Bool m_field335;					// +0x335
};

// Matched AIUpdateInterface helpers under their address-derived ledger names.
class Rva0016FFD0PathOwner
{
public:
	Rva0016FFD0Coord3D *getPoint(int index);		// 0x0016FFD0
};
class Rva0026F110
{
public:
	void set();						// 0x0026F110
};
class Rva0026F930
{
public:
	void set(UnsignedInt value);				// 0x0026F930
};
class Rva0026FE90DwordSlot
{
public:
	void set(int value);					// 0x0026FE90
};

class Thing
{
public:
	void setOrientation(Real angle);			// 0x00132E40
	Real bfmeRelativeAngleTo(const Coord3D *pos) const;	// 0x00150510
	Real getOrientation() const { return m_orientation; }

	unsigned char m_pad00[0x38];
	Coord3D m_position;					// +0x38
	Real m_orientation;					// +0x44
};

class Object : public Thing
{
public:
	void notifyModelConditionChanged();			// 0x001BE1C0

	unsigned char m_pad48[0x114 - 0x48];
	UnsignedInt m_bfmeFlags114;				// +0x114
	unsigned char m_pad118[0x204 - 0x118];
	AIUpdateInterface *m_ai;				// +0x204
};

enum PathfindLayerEnum { LAYER_INVALID = 0 };

class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet,
		Coord3D *dest, const Coord3D *groupDest);	// 0x003F6090
};

// Five-argument BFME updateGoal (ILT 0x000294E2, debug file and line).
class BfmeIdlePathfinder
{
public:
	void updateGoal(Object *obj, const Coord3D *goal, int layer,
		const char *file, int line);
};

class AI
{
public:
	unsigned char m_pad00[0xc];
	Pathfinder *m_pathfinder;
	Pathfinder *pathfinder() { return m_pathfinder; }
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;

class State
{
public:
	BFME_SLOT(000) BFME_SLOT(004) BFME_SLOT(008) BFME_SLOT(00c)
	BFME_SLOT(010) BFME_SLOT(014)
	virtual StateReturnType update() = 0;			// +0x18
	BFME_SLOT(01c) BFME_SLOT(020) BFME_SLOT(024) BFME_SLOT(028)
	BFME_SLOT(02c) BFME_SLOT(030) BFME_SLOT(034) BFME_SLOT(038)
	BFME_SLOT(03c) BFME_SLOT(040)
	virtual Bool computePath() = 0;				// +0x44

	unsigned char m_pad04[0x1c - 4];
	StateMachine *m_machine;				// +0x1c

	StateMachine *getMachine() { return m_machine; }
	Object *getMachineOwner() { return m_machine->m_owner; }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType update();			// ILT 0x000488F6

	unsigned char m_pad20[4];
	Coord3D m_goalPosition;					// +0x24
	unsigned char m_pad30[0x4c - 0x30];
	Bool m_adjustsDestination;				// +0x4c

	Bool getAdjustsDestination() const;			// 0x001724B0
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
};

class Rva0016F7C0State
{
public:
	Bool rva0016F7C0();					// 0x0016F7C0
};

class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();

	int m_index;						// +0x50
	int m_retryCount;					// +0x54
	Bool m_adjustFinal;					// +0x58
	Bool m_adjustFinalOverride;				// +0x59
	Bool m_field5A;						// +0x5a
	Bool m_field5B;						// +0x5b
	int m_field5C;						// +0x5c
	StateMachine *m_attackMoveMachine;			// +0x60
	Real m_field64;						// +0x64
	Bool m_field68;						// +0x68
};

#undef BFME_SLOT

StateReturnType AIFollowPathAsTeamState::update()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->m_ai;
	Bool resumed = false;

	if (m_attackMoveMachine)
	{
		Bool forceRetarget = false;
		if (!m_attackMoveMachine->isInIdleState())
		{
			Object *goal = getMachineGoalObject();
			if (goal && goal != m_attackMoveMachine->getGoalObject())
				m_attackMoveMachine->setGoalObject(goal);
			m_attackMoveMachine->updateStateMachine();
			if (m_attackMoveMachine == 0 || !m_attackMoveMachine->isInIdleState())
				return STATE_CONTINUE;
			forceRetarget = true;
			resumed = true;
			ai->m_field48 = m_field5C;
		}

		if (m_attackMoveMachine->isInIdleState())
		{
			Object *crate = ai->checkForCrateToPickup();
			if (crate)
			{
				m_attackMoveMachine->setGoalObject(crate);
				m_attackMoveMachine->setState(0x27);
				return STATE_CONTINUE;
			}

			Object *victim = ai->getNextMoodTarget(!forceRetarget, false);
			if (victim)
			{
				((Rva0026F110 *)ai)->set();
				m_attackMoveMachine->setGoalObject(victim);
				m_attackMoveMachine->setState(0x0a);
				ai->m_field48 = 2;
				ai->m_field335 = true;
				return STATE_CONTINUE;
			}
		}
	}

	getMachine()->setGoalPosition(&m_goalPosition);
	StateReturnType status = STATE_SUCCESS;

	if (m_field68)
	{
		if (normalizeAngle(m_field64 - obj->getOrientation()) < 0.31415927f)
		{
			obj->setOrientation(m_field64);
			return STATE_SUCCESS;
		}
		ai->setSlot1E4(m_field64);
		return STATE_CONTINUE;
	}

	if (m_field5A)
	{
		if (obj->m_bfmeFlags114 & 0x10000000)
		{
			obj->m_bfmeFlags114 &= ~0x10000000;
			obj->notifyModelConditionChanged();
		}
	}
	else
	{
		status = AIInternalMoveToState::update();
		if (status == STATE_FAILURE)
		{
			if (m_retryCount > 0)
				m_retryCount--;
			else
				status = STATE_SUCCESS;
		}
		else if (status != STATE_SUCCESS && !resumed)
		{
			return status;
		}
	}

	if (!m_field5A && status == STATE_SUCCESS)
	{
		if (m_field5B && m_index > 0)
			m_index--;
		Rva0016FFD0Coord3D *turnTo = ((Rva0016FFD0PathOwner *)ai)->getPoint(m_index + 1);
		if (turnTo)
		{
			Real speed = getMachineOwner()->m_ai->getCurLocomotorSpeed();
			if (ai->isDoingGroundMovement())
				ai->setDesiredSpeed(speed);
			Real angle = obj->bfmeRelativeAngleTo((const Coord3D *)turnTo);
			Real facing = normalizeAngle(obj->getOrientation() + angle);
			ai->setSlot1E4(facing);
		}
		m_index++;
		ai->m_currentGoalPathIndex = m_index;
		m_field5A = (turnTo != 0);
	}

	if (m_field5A && !((Rva0016F7C0State *)this)->rva0016F7C0())
		return STATE_CONTINUE;

	m_field5A = false;
	m_field5B = false;

	Object *owner = getMachineOwner();
	const Coord3D *ownerPos = &owner->m_position;
	Coord3D start;
	start.x = ownerPos->x;
	start.y = ownerPos->y;
	AIUpdateInterface *ownerAI = owner->m_ai;
	Rva0016FFD0Coord3D *pos = ((Rva0016FFD0PathOwner *)ownerAI)->getPoint(m_index);

	Bool tooClose = true;
	while (pos && tooClose)
	{
		Real dx = pos->x - start.x;
		Real dy = pos->y - start.y;
		tooClose = false;
		if (sqr(dx) + sqr(dy) < 100.0f)
			tooClose = true;
		int next = m_index + 1;
		Rva0016FFD0Coord3D *nextPos = ownerAI->getPath()->getPoint(next);
		if (nextPos && (nextPos->x - pos->x) * dx + (nextPos->y - pos->y) * (pos->y - start.y) < 0.0f)
			tooClose = true;
		if (tooClose)
		{
			m_index = next;
			pos = ownerAI->getPath()->getPoint(next);
		}
	}

	((Rva0026F930 *)ownerAI)->set(0);
	if (pos == 0)
	{
		m_field68 = true;
		ownerAI->setSlot1E4(m_field64);
		return STATE_CONTINUE;
	}

	ownerAI->friend_startingMove();
	m_goalPosition = *(const Coord3D *)pos;
	int index = m_index;
	Rva0016FFD0Coord3D *nextPos = ((Rva0016FFD0PathOwner *)ownerAI)->getPoint(index + 1);
	if (nextPos)
	{
		Real dx = nextPos->x - pos->x;
		Real dy = nextPos->y - pos->y;
		Real offset = (Real)sqrt(dx * dx + dy * dy);
		if (((Rva0016FFD0PathOwner *)ownerAI)->getPoint(index + 2))
			offset += 40.0f;
		((Rva0026FE90DwordSlot *)ownerAI)->set(*(int *)&offset);
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"CritterDesync: setAdjustDestination(FALSE) 47");
		setAdjustsDestination(false);
	}
	else
	{
		((Rva0026FE90DwordSlot *)ownerAI)->set(0);
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"CritterDesync: setAdjustDestination(m_adjustFinal=%s && (m_adjustFinalOverride=%s || ai->isDoingGroundMovement()=%s) 48",
				m_adjustFinal ? "TRUE" : "FALSE",
				m_adjustFinalOverride ? "TRUE" : "FALSE",
				ownerAI->isDoingGroundMovement() ? "TRUE" : "FALSE");
		setAdjustsDestination(m_adjustFinal && (m_adjustFinalOverride || ownerAI->isDoingGroundMovement()));
		if (getAdjustsDestination())
		{
			if (!TheAI->pathfinder()->adjustDestination(getMachineOwner(),
				*(const LocomotorSet *)ownerAI->m_locomotorSet, &m_goalPosition, 0))
			{
				if (--m_retryCount > 0)
				{
					m_goalPosition.add(ownerPos);
					m_goalPosition.Scale(0.5f);
					m_field5B = true;
				}
				else
				{
					return STATE_FAILURE;
				}
			}
			Object *goalOwner = getMachineOwner();
			((BfmeIdlePathfinder *)TheAI->pathfinder())->updateGoal(goalOwner, &m_goalPosition,
				TheTerrainLogic->getLayerForDestination(goalOwner, &m_goalPosition),
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x20a1);
		}
	}

	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: ComputePath35");
	computePath();
	return STATE_CONTINUE;
}
