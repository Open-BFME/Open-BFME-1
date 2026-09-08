// cl: /DNDEBUG /MD /EHsc
// GiantBirdGuardReturnState::onEnter at retail RVA 0x002C0D50.

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
	unsigned char m_unreconstructed00[0x38];
	Coord3D m_position;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unreconstructed00[0x3c];
	UnsignedInt m_frame;
};

class TAiData
{
public:
	unsigned char m_unreconstructed00[0x44];
	UnsignedInt m_guardEnemyReturnScanRate;
};

class AI
{
public:
	unsigned char m_unreconstructed00[0x14];
	TAiData *m_aiData;
};

class Team;

class TeamFactory
{
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *position) const;
};

class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *position) const;
};

class GiantBirdGuardMachine
{
public:
	unsigned char m_unreconstructed00[0x44];
	Int m_teamID;
	Int m_otherID;
	PolygonTrigger *m_areaToGuard;
	Coord3D m_positionToGuard;
	Coord3D m_explicitPosition;
	unsigned char m_hasExplicitPosition;
	unsigned char m_unreconstructed69[0x03];
};

class GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned char m_unreconstructed04[0x18];
	GiantBirdGuardMachine *m_machine;
};

class GiantBirdGuardReturnState : public GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();

private:
	unsigned char m_unreconstructed20[0x04];
	unsigned char m_active;
	unsigned char m_unreconstructed25[0x03];
	UnsignedInt m_frameToSleepUntil;
	Coord3D m_position;
};

extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern TeamFactory *TheTeamFactory;
extern int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
extern void j_0000314d();
extern void j_00044c2e();
extern void j_0002a054();

// ?onEnter@GiantBirdGuardReturnState@@UAE?AW4StateReturnType@@XZ
StateReturnType GiantBirdGuardReturnState::onEnter()
{
	GiantBirdGuardReturnState *state = this;
	UnsignedInt now = TheGameLogic->getFrame();
	TAiData *aiData = TheAI->m_aiData;
	m_frameToSleepUntil = now + GetGameLogicRandomValue(
		0, aiData->m_guardEnemyReturnScanRate,
		(char *)0x010C7710, 0xABB);

	{
		GiantBirdGuardMachine *machine = state->m_machine;
		state->m_position = machine->m_positionToGuard;
		Object *target = TheGameLogic->findObjectByID(machine->m_teamID);
		if (target)
		{
			state->m_position = target->m_position;
		}
		else
		{
			typedef Team *(TeamFactory::*FindTeamCall)(Int);
			union
			{
				void *asVoid;
				FindTeamCall asMember;
			} findTeamCast;
			findTeamCast.asVoid = (void *)j_00044c2e;
			Team *team = (TheTeamFactory->*findTeamCast.asMember)(machine->m_otherID);
			if (team)
			{
				team->getEstimateTeamPosition_000EDCD0(&state->m_position);
			}
			else
			{
				GiantBirdGuardMachine *areaMachine = state->m_machine;
				PolygonTrigger *area = areaMachine->m_areaToGuard;
				if (area)
				{
					if (areaMachine->m_hasExplicitPosition)
						state->m_position = areaMachine->m_explicitPosition;
					else
						area->getCenterPoint(&state->m_position);
				}
			}
		}
	}

	typedef void (GiantBirdGuardMachine::*SetGoalPositionCall)(const Coord3D *);
	union
	{
		void *asVoid;
		SetGoalPositionCall asMember;
	} setGoalPositionCast;
	setGoalPositionCast.asVoid = (void *)j_0000314d;
	(state->m_machine->*setGoalPositionCast.asMember)(&state->m_position);
	typedef StateReturnType (GiantBirdNormalFlightState::*OnEnterCall)();
	union
	{
		void *asVoid;
		OnEnterCall asMember;
	} onEnterCast;
	onEnterCast.asVoid = (void *)j_0002a054;
	return (this->*onEnterCast.asMember)();
}
