// ?d_0015ca00@@YAXXZ
// partial score=0.99 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// BFME reconstruction of AIGuardReturnState::onEnter at retail 0x0015CA00.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D &Sub(const Coord3D &left, const Coord3D &right)
	{
		x = left.x - right.x;
		y = left.y - right.y;
		z = left.z - right.z;
		return *this;
	}

	float GetLengthEstimate() const;
};

class Object;

class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return m_frame;
	}

private:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class AIData
{
public:
	unsigned char m_pad00[0x44];
	UnsignedInt m_guardEnemyReturnScanRate;
};

class Pathfinder
{
public:
	Bool adjustDestination(Object *owner, const class LocomotorSet &locomotors,
		Coord3D *destination, const Coord3D *source = 0);
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

	AIData *getAiData() const
	{
		return m_aiData;
	}

private:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
	unsigned char m_pad10[4];
	AIData *m_aiData;
};

extern AI *TheAI;

class LocomotorSet
{
	unsigned char m_data[4];
};

template<int N>
class AIUpdateVirtualSlots : public AIUpdateVirtualSlots<N - 1>
{
public:
	virtual void unusedSlot(char (*)[N]);
};

template<>
class AIUpdateVirtualSlots<0>
{
};

class AIUpdateInterface : public AIUpdateVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const;

	void destroyPath();

	const LocomotorSet &getLocomotorSet() const
	{
		return m_locomotorSet;
	}

private:
	unsigned char m_pad04[0x1a8 - 4];
	LocomotorSet m_locomotorSet;
};

class AIUpdateCallTarget
{
public:
	void destroyPath();
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const unsigned char *>(this) + 0x38);
	}

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *reinterpret_cast<AIUpdateInterface *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x204);
	}

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x204 - 0x44];
	AIUpdateInterface * volatile m_aiUpdate;
};

class StateMachine
{
public:
	virtual void unusedSlot();
	void setGoalPosition(const Coord3D *position);
	unsigned char m_pad04[0x0c];
	Object *m_owner;
};

class AIGuardMachine : public StateMachine
{
public:
	void getGuardScanPos(Coord3D *out);
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

protected:
	StateMachine *getMachine() const
	{
		return m_machine;
	}

	Object *getMachineOwner() const
	{
		return m_machine->m_owner;
	}

	protected:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x1c];
	Bool m_adjustsDestination;
	unsigned char m_pad4d[3];
};

class AIGuardReturnState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	UnsignedInt m_nextReturnScanTime;
};

extern int GetGameLogicRandomValue(int minimum, int maximum, char *file, int line);
extern float g_bfmeK1266C;
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0000314d();
extern void j_000065e1();
extern void j_00017099();
extern void j_00036aa2();
extern void j_0003a17a();

StateReturnType AIGuardReturnState::onEnter()
{
	UnsignedInt now = TheBfmeGameLogic->getFrame();
#line 900 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIGuard.cpp"
	m_nextReturnScanTime = now + GetGameLogicRandomValue(
		0, TheAI->getAiData()->m_guardEnemyReturnScanRate, __FILE__, __LINE__);

	{
		Coord3D goalPosition;
		typedef Coord3D *(AIGuardMachine::*GetGuardScanPosCall)(Coord3D *);
		union
		{
			void *asVoid;
			GetGuardScanPosCall asMember;
		} getGuardScanPosCast;
		getGuardScanPosCast.asVoid = (void *)j_00017099;
		Coord3D *scanPosition = (reinterpret_cast<AIGuardMachine *>(m_machine)->*
			getGuardScanPosCast.asMember)(&goalPosition);
		m_goalPosition = *scanPosition;
	}

	register Object *owner = getMachineOwner();
	Coord3D &goal = m_goalPosition;
	if (!owner)
		goto doEnter;
	{
		Coord3D delta;
		delta.x = owner->getPosition()->x;
		delta.y = owner->getPosition()->y;
		delta.z = owner->getPosition()->z;
		delta.x -= goal.x;
		delta.y -= goal.y;
		delta.z -= goal.z;
		typedef float (Coord3D::*GetLengthEstimateCall)() const;
		union
		{
			void *asVoid;
			GetLengthEstimateCall asMember;
		} getLengthEstimateCast;
		getLengthEstimateCast.asVoid = (void *)j_00036aa2;
		if ((delta.*getLengthEstimateCast.asMember)() < g_bfmeK1266C)
			goto doEnter;
		}
	goto returnSuccess;

doEnter:
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	if (ai)
	{
		if (ai->isDoingGroundMovement())
		{
			TheAI->pathfinder()->adjustDestination(getMachineOwner(),
				ai->getLocomotorSet(), &goal, 0);
		}
		typedef void (AIUpdateCallTarget::*DestroyPathCall)();
		union
		{
			void *asVoid;
			DestroyPathCall asMember;
		} destroyPathCast;
		destroyPathCast.asVoid = (void *)j_000065e1;
		(reinterpret_cast<AIUpdateCallTarget *>(ai)->*
			destroyPathCast.asMember)();
	}

	typedef void (StateMachine::*SetGoalPositionCall)(const Coord3D *);
	union
	{
		void *asVoid;
		SetGoalPositionCall asMember;
	} setGoalPositionCast;
	setGoalPositionCast.asVoid = (void *)j_0000314d;
	(reinterpret_cast<StateMachine *>(m_machine)->*
		setGoalPositionCast.asMember)(&goal);

	if (g_012F0239 && g_012ED4FC)
	{
		typedef void (__cdecl *CritterDesyncLog)(void *, const char *);
		((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 3");
	}
	m_adjustsDestination = true;
	return AIInternalMoveToState::onEnter();

returnSuccess:
	return STATE_SUCCESS;
}
