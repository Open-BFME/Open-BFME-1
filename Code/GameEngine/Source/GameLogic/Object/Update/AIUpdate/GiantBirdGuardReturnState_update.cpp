// cl: /DNDEBUG /MD /EHsc
// GiantBirdGuardReturnState::update at retail RVA 0x002C0E70.
// The return-state vtable slot 6 points to this body, and its adjacent name
// getter returns GiantBirdGuardReturnState.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

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

	float GetLengthEstimate() const;
	void set( const Coord3D *position )
	{
		x = position->x;
		y = position->y;
		z = position->z;
	}
	void sub( const Coord3D *position )
	{
		x -= position->x;
		y -= position->y;
		z -= position->z;
	}
};

struct CoordPair
{
	Coord3D goal;
	Coord3D delta;
};

class Object
{
public:
	unsigned char m_unreconstructed00[ 0x38 ];
	Coord3D m_position;
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );
	unsigned char m_unreconstructed00[ 0x3c ];
	UnsignedInt m_frame;
};

class TAiData
{
public:
	unsigned char m_pad00[ 4 ];
	float m_structureSeconds;
	float m_teamSeconds;
	int m_resourcesWealthy;
	int m_resourcesPoor;
	UnsignedInt m_forceIdleFramesCount;
	float m_structuresWealthyMod;
	float m_teamWealthyMod;
	float m_structuresPoorMod;
	float m_teamPoorMod;
	float m_teamResourcesToBuild;
	float m_guardInnerModifierAI;
	float m_guardOuterModifierAI;
	float m_guardInnerModifierHuman;
	float m_guardOuterModifierHuman;
	UnsignedInt m_guardChaseUnitFrames;
	UnsignedInt m_guardEnemyScanRate;
	UnsignedInt m_guardEnemyReturnScanRate;
};

class AI
{
public:
	unsigned char m_unreconstructed00[ 0x14 ];
	TAiData *m_aiData;
};

class Team;

class TeamFactory
{
public:
	void *find( Int id );
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0( Coord3D *position ) const;
};

class GiantBirdGuardMachine
{
public:
	Bool updateStateMachine();
	void setGoalPosition( const Coord3D *position );

	unsigned char m_unreconstructed00[ 0x44 ];
	Int m_teamID;
	Int m_otherID;
};

class GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();
};

class BfmeThingTBB
{
public:
	void bfmeUseTBB( Int value );
};

class GiantBirdGuardReturnState : public GiantBirdNormalFlightState
{
public:
	virtual StateReturnType update();

private:
	unsigned char m_unreconstructed04[ 0x18 ];
	GiantBirdGuardMachine *m_machine;
	unsigned char m_unreconstructed20[ 4 ];
	unsigned char m_active;
	unsigned char m_unreconstructed25[ 3 ];
	UnsignedInt m_frameToSleepUntil;
	Coord3D m_position;
};

extern float g_bfmeDirectionWeight1285;

#define TheBfmeGameLogic ( *(GameLogic **)0x012F0898 )
#define TheBfmeAI ( *(AI **)0x012EF214 )
#define TheBfmeTeamFactory ( *(TeamFactory **)0x012ED810 )

extern void j_0000314d();
extern void j_0001284b();
extern void j_0001f253();
extern void j_0002a054();
extern void j_0002f527();
extern void j_00036aa2();
extern void j_0003d609();
extern void j_00044c2e();
extern void j_000241fe();

typedef Bool (GiantBirdGuardMachine::*UpdateStateMachineCall)();
typedef void (GiantBirdGuardMachine::*SetGoalPositionCall)( const Coord3D * );
typedef void *(TeamFactory::*FindTeamCall)( Int );
typedef Coord3D *(Team::*EstimateTeamPositionCall)( Coord3D * ) const;
typedef Object *(GameLogic::*FindObjectByIDCall)( Int );
typedef float (Coord3D::*GetLengthEstimateCall)() const;
typedef void (BfmeThingTBB::*UseTBBCall)( Int );
typedef StateReturnType (GiantBirdNormalFlightState::*OnEnterCall)();
typedef StateReturnType (GiantBirdGuardReturnState::*FallbackCall)();

StateReturnType GiantBirdGuardReturnState::update()
{
	UnsignedInt now = TheBfmeGameLogic->m_frame;
	if (now >= m_frameToSleepUntil)
	{
		m_frameToSleepUntil = now + TheBfmeAI->m_aiData->m_guardEnemyReturnScanRate;

		union
		{
			void *asVoid;
			UpdateStateMachineCall asMember;
		} updateStateMachineCast;
		updateStateMachineCast.asVoid = (void *)j_0002f527;
		if ((m_machine->*updateStateMachineCast.asMember)())
			return STATE_FAILURE;
	}

	GiantBirdGuardMachine *machine = m_machine;
	Object *object = TheBfmeGameLogic->findObjectByID( machine->m_teamID );
	CoordPair positions;
	if (object)
	{
		positions.goal = *(Coord3D *)( (char *)object + 0x38 );
	}
	else
	{
		union
		{
			void *asVoid;
			FindTeamCall asMember;
		} findTeamCast;
		findTeamCast.asVoid = (void *)j_00044c2e;
		Team *team = (Team *)(TheBfmeTeamFactory->*findTeamCast.asMember)( machine->m_otherID );
		if (team)
		{
			union
			{
				void *asVoid;
				EstimateTeamPositionCall asMember;
			} estimateTeamPositionCast;
			estimateTeamPositionCast.asVoid = (void *)j_000241fe;
			(team->*estimateTeamPositionCast.asMember)( &positions.goal );
		}
		else
			goto fallback;
	}

	positions.delta.set( &m_position );
	positions.delta.sub( &positions.goal );

	union
	{
		void *asVoid;
		GetLengthEstimateCall asMember;
	} getLengthEstimateCast;
	getLengthEstimateCast.asVoid = (void *)j_00036aa2;
	if ((positions.delta.*getLengthEstimateCast.asMember)() > g_bfmeDirectionWeight1285)
	{
		m_position = positions.goal;
		union
		{
			void *asVoid;
			SetGoalPositionCall asMember;
		} setGoalPositionCast;
		setGoalPositionCast.asVoid = (void *)j_0000314d;
		(m_machine->*setGoalPositionCast.asMember)( &m_position );

		union
		{
			void *asVoid;
			UseTBBCall asMember;
		} useTBBCast;
		useTBBCast.asVoid = (void *)j_0001284b;
		BfmeThingTBB *thing = (BfmeThingTBB *)this;
		(thing->*useTBBCast.asMember)( 0 );

		union
		{
			void *asVoid;
			OnEnterCall asMember;
		} onEnterCast;
		onEnterCast.asVoid = (void *)j_0002a054;
		return (this->*onEnterCast.asMember)();
	}

fallback:
	{
		union
		{
			void *asVoid;
			FallbackCall asMember;
		} fallbackCast;
		fallbackCast.asVoid = (void *)j_0003d609;
		return (this->*fallbackCast.asMember)();
	}
}
