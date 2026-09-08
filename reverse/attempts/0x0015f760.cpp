// ?onEnter@AIHarvestApproachSiteState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-09-08
// ?onEnter@AIHarvestApproachSiteState@@UAE?AW4StateReturnType@@XZ
// cl: /DNDEBUG /MD /EHsc-

typedef unsigned char Bool;
typedef float Real;

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

class LocomotorSet
{
};

class HarvestTarget
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03(int) = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual Real getValue(int, int) = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11(int) = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void setOwner(int) = 0;

	char m_pad04[0x18];
	Coord3D m_position;
};

template <int N>
class AIUpdateVirtualSlots : public AIUpdateVirtualSlots<N - 1>
{
public:
	virtual void unusedSlot(char (*)[N]) = 0;
};

template <>
class AIUpdateVirtualSlots<0>
{
};

class AIUpdateInterface : public AIUpdateVirtualSlots<81>
{
public:
	virtual HarvestTarget *getHarvestTarget() = 0;

	LocomotorSet &getLocomotorSet()
	{
		return *(LocomotorSet *)((char *)this + 0x1a8);
	}
};

class Object
{
public:
	char m_pad00[0x204];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	char m_pad00[0x10];
	Object *m_owner;
};

class HarvestRecord
{
public:
	char m_pad00[0x10];
	int m_owner;
	char m_pad14[4];
	Bool m_isFinished;
};

class TerrainLogic
{
public:
	HarvestRecord *find(HarvestRecord *, Real);
};

class Pathfinder
{
public:
	Bool adjustDestination(Object *, const LocomotorSet &, Coord3D *,
		const Coord3D * = 0);
	Bool bfmeGroundCellThreshold(const Coord3D *, Bool);
	Bool bfmeAnyBridgeAt(const Coord3D *);
};

class AI
{
public:
	char m_pad00[0x0c];
	Pathfinder *m_pathfinder;

	Pathfinder *pathfinder()
	{
		return m_pathfinder;
	}
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

class AIHarvestApproachSiteState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	char m_pad04[0x18];
	StateMachine *m_machine;
	char m_pad20[4];
	Coord3D m_goalPosition;
};

extern TerrainLogic *TheTerrainLogic;
#define TheAI (*(AI **)0x012EF214)
extern Real GetGameLogicRandomValueReal(Real, Real, char *, int);

#pragma comment(linker, "/alternatename:?find@TerrainLogic@@QAEPAVHarvestRecord@@PAV2@M@Z=?j_000226ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeAnyBridgeAt@Pathfinder@@QAEDPBUCoord3D@@@Z=?j_00012a99@@YAXXZ")
#pragma comment(linker, "/alternatename:?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ=?j_00021e27@@YAXXZ")

StateReturnType AIHarvestApproachSiteState::onEnter()
{
	register HarvestTarget *targetPointer;
	register Coord3D *position;
	register HarvestRecord *record;
	register int attempt;
	targetPointer = m_machine->m_owner->m_ai->getHarvestTarget();
	if (targetPointer == 0)
		return STATE_FAILURE;
	HarvestTarget &target = *targetPointer;

	position = (Coord3D *)((char *)m_machine + 0x24);
	if (position == 0)
		return STATE_FAILURE;

	record = TheTerrainLogic->find(
		(HarvestRecord *)position, target.getValue(0, 0));
	if (record == 0)
	{
		target.slot11(1);
		return STATE_FAILURE;
	}

	target.setOwner(record->m_owner);
	m_goalPosition = *position;
	if (record->m_isFinished)
		return AIInternalMoveToState::onEnter();

#line 95 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIHarvest.cpp"
	Real scale = GetGameLogicRandomValueReal(0.5f, 5.0f, __FILE__, __LINE__);
	Coord3D offset = {
		target.m_position.x * scale,
		target.m_position.y * scale,
		target.m_position.z * scale
	};

	attempt = 0;
	for (; attempt < 5; ++attempt)
	{
		Coord3D destination = {
			m_goalPosition.x + offset.x,
			m_goalPosition.y + offset.y,
			m_goalPosition.z + offset.z
		};
		if (!TheAI->pathfinder()->adjustDestination(m_machine->m_owner,
			m_machine->m_owner->m_ai->getLocomotorSet(),
			&destination, 0) &&
			!TheAI->pathfinder()->bfmeGroundCellThreshold(&destination, 0) &&
			!TheAI->pathfinder()->bfmeAnyBridgeAt(&destination))
		{
			m_goalPosition = destination;
			return AIInternalMoveToState::onEnter();
		}

		offset.x *= 0.5f;
		offset.y *= 0.5f;
		offset.z *= 0.5f;
	}

	return AIInternalMoveToState::onEnter();
}
