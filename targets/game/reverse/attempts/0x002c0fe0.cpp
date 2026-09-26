// ?d_002c0fe0@@YAXXZ
// partial score=0.6 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
// GiantBirdGuardIdleState::update at retail RVA 0x002C0FE0, 290 bytes.
// Vtable 0x010C7BB8 (GiantBirdGuardMachineCtor.cpp) slot 6 (ILT 0x0043A55D)
// reaches this body, matching the same slot GiantBirdGuardReturnState::update
// occupies on its own vtable 0x010C7CB8; the m_int24/m_tail28 fields declared
// there for GiantBirdGuardIdleState are this body's m_frameToSleepUntil and
// m_position (Coord3D, 0x0C bytes at +0x28).

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
	unsigned char m_pad00[ 0x40 ];
	UnsignedInt m_guardEnemyScanRate;
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
	Bool lookForInnerTarget();

	unsigned char m_unreconstructed00[ 0x10 ];
	void *m_notifyChain;
	unsigned char m_unreconstructed14[ 0x44 - 0x14 ];
	Int m_teamID;
	Int m_otherID;
};

class GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();
};

class GiantBirdGuardIdleState : public GiantBirdNormalFlightState
{
public:
	virtual StateReturnType update();

private:
	unsigned char m_unreconstructed04[ 0x18 ];
	GiantBirdGuardMachine *m_machine;
	unsigned char m_unreconstructed20[ 4 ];
	UnsignedInt m_frameToSleepUntil;
	Coord3D m_position;
};

#define TheBfmeGameLogic ( *(GameLogic **)0x012F0898 )
#define TheBfmeAI ( *(AI **)0x012EF214 )
#define TheBfmeTeamFactory ( *(TeamFactory **)0x012ED810 )

extern void j_00044c2e();
extern void j_000241fe();

typedef void *(TeamFactory::*FindTeamCall)( Int );
typedef Coord3D *(Team::*EstimateTeamPositionCall)( Coord3D * ) const;

typedef void ( GiantBirdGuardMachine::*NotifySlot8 )( Int );

StateReturnType GiantBirdGuardIdleState::update()
{
	UnsignedInt now = TheBfmeGameLogic->m_frame;
	if (now < m_frameToSleepUntil)
		return (StateReturnType)( m_frameToSleepUntil - now );

	m_frameToSleepUntil = now + TheBfmeAI->m_aiData->m_guardEnemyScanRate;

	GiantBirdGuardMachine *machine = m_machine;
	void *chain = *reinterpret_cast<void **>(
		reinterpret_cast<char *>( machine ) + 0x10 );
	void *deeper = *reinterpret_cast<void **>(
		reinterpret_cast<char *>( chain ) + 0x204 );
	void *flag = *reinterpret_cast<void **>(
		reinterpret_cast<char *>( deeper ) + 0x218 );

	if (flag != 0)
	{
		void *slot8 = ( *reinterpret_cast<void ***>( machine ) )[ 8 ];
		union
		{
			void *asVoid;
			NotifySlot8 asMember;
		} notifyCast;
		notifyCast.asVoid = slot8;
		(machine->*notifyCast.asMember)( 0x138C );
		return (StateReturnType)( m_frameToSleepUntil - now );
	}

	if (machine->lookForInnerTarget())
		return STATE_SUCCESS;

	Object *object = TheBfmeGameLogic->findObjectByID( machine->m_teamID );

	union
	{
		void *asVoid;
		FindTeamCall asMember;
	} findTeamCast;
	findTeamCast.asVoid = (void *)j_00044c2e;
	Team *team = (Team *)(TheBfmeTeamFactory->*findTeamCast.asMember)( machine->m_otherID );

	Coord3D goal;
	if (object == 0)
	{
		if (team == 0)
			return (StateReturnType)( m_frameToSleepUntil - now );

		union
		{
			void *asVoid;
			EstimateTeamPositionCall asMember;
		} estimateTeamPositionCast;
		estimateTeamPositionCast.asVoid = (void *)j_000241fe;
		(team->*estimateTeamPositionCast.asMember)( &goal );
	}
	else
	{
		goto compute_from_object;
	}

distance_check:
	{
		float dx = m_position.x - goal.x;
		if (dx * dx > *(float *)0x01096418)
		{
			m_position = goal;
			return STATE_FAILURE;
		}

		float dy = m_position.y - goal.y;
		if (dy * dy > *(float *)0x01096418)
		{
			m_position = goal;
			return STATE_FAILURE;
		}

		return (StateReturnType)( m_frameToSleepUntil - now );
	}

compute_from_object:
	goal = *(Coord3D *)( (char *)object + 0x38 );
	goto distance_check;
}
