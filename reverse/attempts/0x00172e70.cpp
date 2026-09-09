// ?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ
// partial score=0.46 date=2026-09-09
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00172E70: AIInternalMoveToState::update.
//
// This body is BFME-specific.  In particular, State keeps the machine at
// +0x1c, AIUpdate keeps its path at +0x140 and its wait/blocked fields at
// +0x31e/+0x326, and Pathfinder::updateGoal carries the retail source/line
// arguments.  Keep those facts local to this recovered sibling; the shared
// ZH headers describe a different object layout.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

enum ModelConditionFlagType
{
	MODELCONDITION_MOVING = 0x3c,
	MODELCONDITION_CLIMBING = 0x66,
	MODELCONDITION_RAPPELLING = 0x68,
	MODELCONDITION_BLOCKED = 0x92
};

#pragma comment(linker, "/alternatename:?getAdjustsDestination@AIInternalMoveToState@@IBE_NXZ=?j_00010109@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?canComputeQuickPath@AIUpdateInterface@@QAE_NXZ=?j_00038307@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLocomotorDistanceToGoal@AIUpdateInterface@@QAEMXZ=?j_000333ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayer@Object@@QBEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeCellTypeTwo@Pathfinder@@QAEHPBUCoord3D@@W4PathfindLayerEnum@@@Z=?j_0001c26f@@YAXXZ")
#pragma comment(linker, "/alternatename:?query@BfmeSub1CC_EC3@@QAEMPAX@Z=?j_000230ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPreferredHeight@Locomotor@@QBEMXZ=?j_0002ecad@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@W4PathfindLayerEnum@@PBDH@Z=?j_000294e2@@YAXXZ")
#pragma comment(linker, "/alternatename:?removeGoal@Pathfinder@@QAEXPAVObject@@@Z=?j_00015d02@@YAXXZ")

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class Object;
class PathfindCell;
class Pathfinder;

class StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

class State
{
public:
	virtual void bfmeVSlot00() = 0;
	virtual void bfmeVSlot01() = 0;
	virtual void bfmeVSlot02() = 0;
	virtual StateReturnType update() = 0;
	virtual void bfmeVSlot04() = 0;
	virtual void bfmeVSlot05() = 0;
	virtual void bfmeVSlot06() = 0;
	virtual void bfmeVSlot07() = 0;
	virtual void bfmeVSlot08() = 0;
	virtual void bfmeVSlot09() = 0;
	virtual void bfmeVSlot10() = 0;
	virtual void bfmeVSlot11() = 0;
	virtual void bfmeVSlot12() = 0;
	virtual void bfmeVSlot13() = 0;
	virtual void bfmeVSlot14() = 0;
	virtual void bfmeVSlot15() = 0;
	virtual void bfmeVSlot16() = 0;

protected:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType update();
	virtual Bool computePath() = 0;

	Bool getAdjustsDestination() const;
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->m_owner; }

protected:
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[4];
	Coord3D m_pathGoalPosition;
	UnsignedInt m_ambientPlayingHandle;
	UnsignedInt m_pathTimestamp;
	UnsignedInt m_blockedRepathTimestamp;
	Bool m_adjustDestinations;
	Bool m_waitingForPath;
	Bool m_tryOneMoreRepath;
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class BfmeThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xc0];
	UnsignedInt m_kindof[3];
};

class Locomotor
{
public:
	void *m_vptr;
	unsigned char m_pad04[0x34];
	Real m_closeEnoughDistance;
	unsigned char m_pad3c[4];
	UnsignedInt m_flags;

	Real getPreferredHeight() const;

	Bool isMovingBackwards() const
	{
		return ((m_flags >> 7) & 1) != 0;
	}
};

class PathNode
{
public:
	unsigned char m_pad00[0x0c];
	Coord3D m_position;
	PathfindLayerEnum m_layer;
};

class Path
{
public:
	unsigned char m_pad00[8];
	PathNode *m_lastNode;
};

class AIUpdateInterface
{
public:
	// BFME's update interface has the path movement calls at these complete
	// object vtable slots.  The declarations are intentionally ordinal-only.
	virtual void bfmeVSlot000() = 0;
	virtual void bfmeVSlot001() = 0;
	virtual void bfmeVSlot002() = 0;
	virtual void bfmeVSlot003() = 0;
	virtual void bfmeVSlot004() = 0;
	virtual void bfmeVSlot005() = 0;
	virtual void bfmeVSlot006() = 0;
	virtual void bfmeVSlot007() = 0;
	virtual void bfmeVSlot008() = 0;
	virtual void bfmeVSlot009() = 0;
	virtual void bfmeVSlot010() = 0;
	virtual void bfmeVSlot011() = 0;
	virtual void bfmeVSlot012() = 0;
	virtual void bfmeVSlot013() = 0;
	virtual void bfmeVSlot014() = 0;
	virtual void bfmeVSlot015() = 0;
	virtual void bfmeVSlot016() = 0;
	virtual void bfmeVSlot017() = 0;
	virtual void bfmeVSlot018() = 0;
	virtual void bfmeVSlot019() = 0;
	virtual void bfmeVSlot020() = 0;
	virtual void bfmeVSlot021() = 0;
	virtual void bfmeVSlot022() = 0;
	virtual void bfmeVSlot023() = 0;
	virtual void bfmeVSlot024() = 0;
	virtual void bfmeVSlot025() = 0;
	virtual void bfmeVSlot026() = 0;
	virtual void bfmeVSlot027() = 0;
	virtual void bfmeVSlot028() = 0;
	virtual void bfmeVSlot029() = 0;
	virtual void bfmeVSlot030() = 0;
	virtual void bfmeVSlot031() = 0;
	virtual void bfmeVSlot032() = 0;
	virtual void bfmeVSlot033() = 0;
	virtual void bfmeVSlot034() = 0;
	virtual void bfmeVSlot035() = 0;
	virtual void bfmeVSlot036() = 0;
	virtual void bfmeVSlot037() = 0;
	virtual void bfmeVSlot038() = 0;
	virtual void bfmeVSlot039() = 0;
	virtual void bfmeVSlot040() = 0;
	virtual void bfmeVSlot041() = 0;
	virtual void bfmeVSlot042() = 0;
	virtual void bfmeVSlot043() = 0;
	virtual void bfmeVSlot044() = 0;
	virtual void bfmeVSlot045() = 0;
	virtual void bfmeVSlot046() = 0;
	virtual void bfmeVSlot047() = 0;
	virtual void bfmeVSlot048() = 0;
	virtual void bfmeVSlot049() = 0;
	virtual void bfmeVSlot050() = 0;
	virtual void bfmeVSlot051() = 0;
	virtual void bfmeVSlot052() = 0;
	virtual void bfmeVSlot053() = 0;
	virtual void bfmeVSlot054() = 0;
	virtual void bfmeVSlot055() = 0;
	virtual void bfmeVSlot056() = 0;
	virtual void bfmeVSlot057() = 0;
	virtual void bfmeVSlot058() = 0;
	virtual void bfmeVSlot059() = 0;
	virtual void bfmeVSlot060() = 0;
	virtual void bfmeVSlot061() = 0;
	virtual void bfmeVSlot062() = 0;
	virtual void bfmeVSlot063() = 0;
	virtual void bfmeVSlot064() = 0;
	virtual void bfmeVSlot065() = 0;
	virtual void bfmeVSlot066() = 0;
	virtual void bfmeVSlot067() = 0;
	virtual void bfmeVSlot068() = 0;
	virtual void bfmeVSlot069() = 0;
	virtual void bfmeVSlot070() = 0;
	virtual void bfmeVSlot071() = 0;
	virtual void bfmeVSlot072() = 0;
	virtual void bfmeVSlot073() = 0;
	virtual void bfmeVSlot074() = 0;
	virtual void bfmeVSlot075() = 0;
	virtual void bfmeVSlot076() = 0;
	virtual void bfmeVSlot077() = 0;
	virtual void bfmeVSlot078() = 0;
	virtual void bfmeVSlot079() = 0;
	virtual void bfmeVSlot080() = 0;
	virtual void bfmeVSlot081() = 0;
	virtual void bfmeVSlot082() = 0;
	virtual void bfmeVSlot083() = 0;
	virtual void bfmeVSlot084() = 0;
	virtual void bfmeVSlot085() = 0;
	virtual void bfmeVSlot086() = 0;
	virtual void bfmeVSlot087() = 0;
	virtual void bfmeVSlot088() = 0;
	virtual void bfmeVSlot089() = 0;
	virtual void bfmeVSlot090() = 0;
	virtual void bfmeVSlot091() = 0;
	virtual void bfmeVSlot092() = 0;
	virtual void bfmeVSlot093() = 0;
	virtual void bfmeVSlot094() = 0;
	virtual void bfmeVSlot095() = 0;
	virtual void bfmeVSlot096() = 0;
	virtual void bfmeVSlot097() = 0;
	virtual void bfmeVSlot098() = 0;
	virtual void bfmeVSlot099() = 0;
	virtual void bfmeVSlot100() = 0;
	virtual void bfmeVSlot101() = 0;
	virtual void bfmeVSlot102() = 0;
	virtual void bfmeVSlot103() = 0;
	virtual void bfmeVSlot104() = 0;
	virtual void bfmeVSlot105() = 0;
	virtual void bfmeVSlot106() = 0;
	virtual void bfmeVSlot107() = 0;
	virtual void bfmeVSlot108() = 0;
	virtual void bfmeVSlot109() = 0;
	virtual void bfmeVSlot110() = 0;
	virtual void bfmeVSlot111() = 0;
	virtual void bfmeVSlot112() = 0;
	virtual void bfmeVSlot113() = 0;
	virtual void bfmeVSlot114() = 0;
	virtual void bfmeVSlot115() = 0;
	virtual void bfmeVSlot116() = 0;
	virtual void setLocomotorGoalPositionOnPath() = 0;
	virtual void bfmeVSlot118() = 0;
	virtual void bfmeVSlot119() = 0;
	virtual void bfmeVSlot120() = 0;
	virtual void bfmeVSlot121() = 0;
	virtual void setLocomotorGoalNone() = 0;
	virtual Bool isDoingGroundMovement() const = 0;

	Bool isWaitingForPath() const { return m_waitingForPath != 0; }
	Bool getRetryPath() const { return m_retryPath != 0; }
	Bool isBlockedAndStuck() const { return m_isBlockedAndStuck != 0; }
	Bool canComputeQuickPath();
	Real getLocomotorDistanceToGoal();
	Path *getPath() const { return m_path; }

	unsigned char m_pad004[0x13c];
	Path *m_path;
	unsigned char m_pad144[0x1c];
	UnsignedInt m_arrivalState;
	unsigned char m_pad164[4];
	Real m_pathExtraDistance;
	int m_numFramesBlocked;
	unsigned char m_pad170[0x5c];
	class BfmeSub1CC_EC3 *m_curLocomotor;
	unsigned char m_pad1d0[0x31e - 0x1d0];
	Bool m_waitingForPath;
	unsigned char m_pad31f[0x326 - 0x31f];
	Bool m_isBlockedAndStuck;
	unsigned char m_pad327[0x32e - 0x327];
	Bool m_retryPath;
};

class Object
{
public:
	void *m_vptr;
	BfmeThingTemplate *m_template;
	unsigned char m_pad008[0x30];
	Coord3D m_position;
	unsigned char m_pad044[0xcc];
	UnsignedInt m_modelConditionFlags[10];
	unsigned char m_pad138[0xcc];
	AIUpdateInterface *m_ai;

	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }
	int getLayer() const;

	void notifyModelConditionChanged();

	__forceinline void clearModelConditionState(ModelConditionFlagType condition)
	{
		UnsignedInt *word = m_modelConditionFlags + (condition >> 5);
		UnsignedInt mask = 1u << (condition & 31);
		if ((*word & mask) != 0)
		{
			*word &= ~mask;
			notifyModelConditionChanged();
		}
	}

	__forceinline void setModelConditionState(ModelConditionFlagType condition)
	{
		UnsignedInt *word = m_modelConditionFlags + (condition >> 5);
		UnsignedInt mask = 1u << (condition & 31);
		if ((*word & mask) == 0)
		{
			*word |= mask;
			notifyModelConditionChanged();
		}
	}

};

class Pathfinder
{
public:
	void updateGoal(Object *, const Coord3D *, PathfindLayerEnum,
		const char *, int);
	void removeGoal(Object *);
	Bool bfmeCellTypeTwo(const Coord3D *, PathfindLayerEnum);
};

class BfmeSub1CC_EC3
{
public:
	Real query(void *);
};

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
	Pathfinder *pathfinder() const { return m_pathfinder; }
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern const Real BfmeZeroRange;
extern void j_0003a17a();
extern "C" double sqrt(double);

extern const Real g_01076C24;

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

// Keep this static helper visible in the TU.  The retail caller and body use
// MSVC's private three-register sequence for the static AIStates helper; an
// extern cdecl declaration would put all three coordinates on the stack.
static Bool isSamePosition(const Coord3D *ourPos,
	const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
{
	Coord3D diff;
	diff.x = curTargetPos->x - prevTargetPos->x;
	diff.y = curTargetPos->y - prevTargetPos->y;

	Coord3D toTarget;
	toTarget.x = curTargetPos->x - ourPos->x;
	toTarget.y = curTargetPos->y - ourPos->y;

	Real toleranceSqr = (toTarget.x * toTarget.x +
		toTarget.y * toTarget.y) * g_01076C24;

	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
		return false;

	return true;
}

// ?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIInternalMoveToState::update()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	Path *thePath = ai->getPath();

	if (m_waitingForPath)
	{
		m_pathTimestamp = TheGameLogic->m_frame;
		if (ai->isWaitingForPath())
			return STATE_CONTINUE;

		if (thePath == 0)
			return STATE_FAILURE;

		m_waitingForPath = false;
		m_pathGoalPosition = m_goalPosition;
		if (getAdjustsDestination())
		{
#line 2522 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp"
			TheAI->pathfinder()->updateGoal(obj,
				&thePath->m_lastNode->m_position,
				thePath->m_lastNode->m_layer, __FILE__, __LINE__);
#line 452 "Code/GameEngine/Source/GameLogic/AI/AIInternalMoveToState_update_Bfme.cpp"
		}
		else
		{
			TheAI->pathfinder()->removeGoal(obj);
		}
		if (!ai->getRetryPath())
			m_tryOneMoreRepath = false;
	}

	Bool forceRecompute = false;
	if (thePath == 0)
		forceRecompute = true;
	if (ai->isBlockedAndStuck() || ai->m_numFramesBlocked > 10)
	{
		forceRecompute = true;
		m_blockedRepathTimestamp = TheGameLogic->m_frame;
	}

	if (ai->canComputeQuickPath())
	{
		BfmeThingTemplate *thing = obj->m_template;
		if (thing != 0 && thing->m_nextOverride != 0)
			thing = (BfmeThingTemplate *)thing->m_nextOverride->getFinalOverride();
		if ((thing->m_kindof[0] & 0x02000000) != 0)
		{
			m_pathTimestamp = 0;
			forceRecompute = true;
		}
	}

	if (thePath != 0)
		ai->setLocomotorGoalPositionOnPath();

	Real onPathDistToGoal = ai->getLocomotorDistanceToGoal();
	BfmeSub1CC_EC3 *curLoco = ai->m_curLocomotor;
	if (curLoco != 0 &&
		!(onPathDistToGoal >= ((Locomotor *)curLoco)->m_closeEnoughDistance))
	{
		obj->clearModelConditionState(MODELCONDITION_MOVING);
	}
	else
	{
		Pathfinder *pathfinder = TheAI->pathfinder();
		ModelConditionFlagType setConditionFlag = MODELCONDITION_MOVING;
		UnsignedInt rappellingMask = 0x100;
		if (pathfinder->bfmeCellTypeTwo(
			obj->getPosition(), (PathfindLayerEnum)obj->getLayer()))
		{
			if (ai->m_curLocomotor != 0 &&
				((Locomotor *)ai->m_curLocomotor)->isMovingBackwards())
			{
				setConditionFlag = MODELCONDITION_RAPPELLING;
				obj->clearModelConditionState(MODELCONDITION_CLIMBING);
			}
			else
			{
				setConditionFlag = MODELCONDITION_CLIMBING;
				if ((obj->m_modelConditionFlags[1] & rappellingMask) != 0)
					obj->clearModelConditionState(MODELCONDITION_RAPPELLING);
			}
		}

		if (ai->m_numFramesBlocked > 5)
		{
			obj->clearModelConditionState(MODELCONDITION_MOVING);
			obj->clearModelConditionState(MODELCONDITION_BLOCKED);
		}
		else
		{
			if (setConditionFlag == MODELCONDITION_MOVING)
			{
				obj->clearModelConditionState(MODELCONDITION_CLIMBING);
				if ((obj->m_modelConditionFlags[1] & rappellingMask) != 0)
					obj->clearModelConditionState(MODELCONDITION_RAPPELLING);
			}

			if (curLoco != 0 && curLoco->query(obj) == (Real)BfmeZeroRange)
				obj->clearModelConditionState(MODELCONDITION_MOVING);
			else
				obj->setModelConditionState(MODELCONDITION_MOVING);
			if (setConditionFlag != MODELCONDITION_MOVING)
				obj->setModelConditionState(setConditionFlag);
		}
	}

	if (forceRecompute || TheGameLogic->m_frame - m_pathTimestamp > 5)
	{
		if (forceRecompute || !isSamePosition(obj->getPosition(),
			&m_pathGoalPosition, &m_goalPosition))
		{
			if (g_012F0239 && g_012ED4FC)
				((DebugLogFunction)j_0003a17a)(g_012ED4FC,
					"CritterDesync: ComputePath2");

			if (!computePath())
				return STATE_FAILURE;
			if (ai->getPath() != 0)
				ai->setLocomotorGoalPositionOnPath();
			else
				return STATE_CONTINUE;
		}
	}

	onPathDistToGoal = ai->getLocomotorDistanceToGoal();
	curLoco = ai->m_curLocomotor;
	if (curLoco == 0)
		return STATE_CONTINUE;

	Bool closeEnoughAtTail =
		onPathDistToGoal < ((Locomotor *)curLoco)->m_closeEnoughDistance;
	Bool heightAllowsArrival = false;
	Real preferredHeight = ((Locomotor *)curLoco)->getPreferredHeight();
	if (preferredHeight < ai->m_pathExtraDistance)
	{
		preferredHeight = ((Locomotor *)curLoco)->getPreferredHeight();
		if (preferredHeight + preferredHeight > onPathDistToGoal)
			heightAllowsArrival = true;
	}

	if (heightAllowsArrival || closeEnoughAtTail)
	{
		if (ai->isDoingGroundMovement())
		{
			Coord3D goalPos = m_goalPosition;
			Path *finalPath = ai->getPath();
			if (finalPath->m_lastNode != 0)
				goalPos = finalPath->m_lastNode->m_position;

			Real dx = obj->getPosition()->x - goalPos.x;
			Real dy = obj->getPosition()->y - goalPos.y;
			Real distance = dx * dx + dy * dy;
			distance = (Real)sqrt(distance);
			if (distance > 40.0f)
				return STATE_CONTINUE;
		}

		if (getAdjustsDestination())
			ai->setLocomotorGoalNone();
		ai->m_arrivalState = 0;
		return STATE_SUCCESS;
	}

	return STATE_CONTINUE;
}
