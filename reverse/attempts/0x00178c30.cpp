// ?onEnter@Rva00178C30State@@UAE?AW4StateReturnType@@XZ
// partial score=0.96 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME reconstruction of the anonymous 0x00178C30 state-entry helper.
//
// The adjacent ComputePath29/30/31 bodies establish the retail move-state
// layout.  This body is kept address-derived because the retail image exposes
// only a generated thunk caller, not a trustworthy class name.  Its ABI is
// nevertheless fixed by the state fields and by the pinned ILT callees below.

typedef unsigned char Bool;

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
};

struct Rva00178C30LocalFrame
{
	Coord3D adjustedGoal;
	Coord3D checkPosition;
	unsigned char m_retailScratch[0x4c - 0x18];
};

class Object;

struct Rva00178C30StateMachine
{
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

struct Rva00178C30AIUpdate
{
	unsigned char m_pad00[0x180];
	Coord3D m_adjustedGoal;
	unsigned char m_pad18c[0x190 - 0x18c];
	unsigned char m_pad190[0x31d - 0x190];
	unsigned char m_pathRequestPending;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x204 - 0x44];
	Rva00178C30AIUpdate *m_ai;

	int getLayer();
};

class Pathfinder
{
public:
	int checkAttackView(Object *, Coord3D *);
	void updateGoal(Object *, const Coord3D *, int, const char *, int);
	Bool attackView(Object *, Coord3D *);
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

private:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;
extern unsigned char g_012F0239;
extern void *g_012ED4FC;

extern void j_0001b919(void);
extern void j_00021e27(void);
extern void j_000294e2(void);
extern void j_00033749(void);
extern void j_0003a17a(void);
extern void j_0003a391(void);

typedef int (Pathfinder::*Rva00178C30CheckAttackView)(Object *, Coord3D *);
typedef void (Pathfinder::*Rva00178C30UpdateGoal)(
	Object *, const Coord3D *, int, const char *, int);
typedef int (Object::*Rva00178C30GetLayer)();
typedef Bool (Pathfinder::*Rva00178C30AttackView)(Object *, Coord3D *);
typedef void (__cdecl *Rva00178C30CritterDesyncLog)(void *, const char *);

class AIInternalMoveToState
{
protected:
	unsigned char m_pad00[0x18];
	Rva00178C30StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x1c];
	Bool m_adjustDestinations;

public:
	virtual StateReturnType onEnter();
};

class Rva00178C30State : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType Rva00178C30State::onEnter()
{
	Object *owner = m_machine->m_owner;
	Rva00178C30LocalFrame localFrame;
	Pathfinder *pathfinder;
	Rva00178C30AIUpdate *ai;
	union
	{
		void *asVoid;
		Rva00178C30CheckAttackView asMember;
	} checkAttackViewCast;
	union
	{
		void *asVoid;
		Rva00178C30UpdateGoal asMember;
	} updateGoalCast;
	union
	{
		void *asVoid;
		Rva00178C30GetLayer asMember;
	} getLayerCast;
	union
	{
		void *asVoid;
		Rva00178C30AttackView asMember;
	} attackViewCast;

	checkAttackViewCast.asVoid = (void *)j_00033749;
	updateGoalCast.asVoid = (void *)j_000294e2;
	getLayerCast.asVoid = (void *)j_0003a391;
	attackViewCast.asVoid = (void *)j_0001b919;

	pathfinder = TheAI->pathfinder();
	if (!(pathfinder->*checkAttackViewCast.asMember)(
		owner, &localFrame.checkPosition))
	{
		register unsigned int positionX = *(unsigned int *)
			((unsigned char *)owner + 0x38);
		register unsigned int positionY = *(unsigned int *)
			((unsigned char *)owner + 0x3c);
		register unsigned int positionZ = *(unsigned int *)
			((unsigned char *)owner + 0x40);
		*(unsigned int *)((unsigned char *)&localFrame.adjustedGoal + 0x00) = positionX;
		*(unsigned int *)((unsigned char *)&localFrame.adjustedGoal + 0x04) = positionY;
		*(unsigned int *)((unsigned char *)&localFrame.adjustedGoal + 0x08) = positionZ;
		pathfinder = TheAI->pathfinder();
		(pathfinder->*updateGoalCast.asMember)(
			owner,
			&localFrame.adjustedGoal,
			(owner->*getLayerCast.asMember)(),
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",
			0x1dc9);

		pathfinder = TheAI->pathfinder();
		if ((pathfinder->*attackViewCast.asMember)(
			owner, &localFrame.adjustedGoal))
		{
			ai = owner->m_ai;
			ai->m_adjustedGoal = localFrame.adjustedGoal;
			ai->m_pathRequestPending = 0;
		}
		return STATE_FAILURE;
	}

	m_goalPosition = owner->m_position;
	if (g_012F0239 && g_012ED4FC)
	{
		((Rva00178C30CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 37");
	}
	m_adjustDestinations = 1;
	return AIInternalMoveToState::onEnter();
}
