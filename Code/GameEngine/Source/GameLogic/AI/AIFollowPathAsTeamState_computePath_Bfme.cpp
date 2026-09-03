// cl: /DNDEBUG /MD /EHsc
// Retail 0x001795F0: BFME's out-of-bounds path fallback for
// AIFollowPathAsTeamState::computePath.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	Bool isInRegionNoZ(const Coord3D *point) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void getMaximumPathfindExtent(Region3D *extent) const;
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	Bool computeQuickPath(const Coord3D *destination);
	void requestPath(Coord3D *destination, Bool adjustsDestination);
	void friend_startingMove();

	unsigned char m_pad00[0x31e];
	Bool m_waitingForPath;
};

struct BfmeObject
{
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

struct BfmeStateMachine
{
	unsigned char m_pad00[0x10];
	BfmeObject *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
protected:
	virtual Bool computePath();

	unsigned char m_pad00[0x18];
	BfmeStateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x1d];
	Bool m_waitingForPath;

	Bool getAdjustsDestination() const;
};

Bool AIInternalMoveToState::computePath()
{
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	ai->requestPath(&m_goalPosition, getAdjustsDestination());
	m_waitingForPath = ai->m_waitingForPath;
	ai->friend_startingMove();
	return true;
}

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *);

class AIFollowPathAsTeamState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIFollowPathAsTeamState::computePath()
{
	if (g_012F0239 && g_012ED4FC)
	{
		((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: ComputePath33");
	}

	BfmeStateMachine *machine = m_machine;
	BfmeObject *owner = machine->m_owner;
	Coord3D position;
	position.x = owner->m_position.x;
	position.y = owner->m_position.y;
	AIUpdateInterface *ai = owner->m_ai;
	Region3D extent;
	TheTerrainLogic->getMaximumPathfindExtent(&extent);

	if (ai != 0)
	{
		if (!(extent.lo.x < position.x && position.x < extent.hi.x &&
			extent.lo.y < position.y && position.y < extent.hi.y))
		{
			if (extent.isInRegionNoZ(&m_goalPosition))
				return ai->computeQuickPath(&m_goalPosition);
		}
	}

	if (g_012F0239 && g_012ED4FC)
	{
		((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: ComputePath34");
	}
	AIUpdateInterface *fallbackAI = m_machine->m_owner->m_ai;
	fallbackAI->requestPath(&m_goalPosition, getAdjustsDestination());
	m_waitingForPath = fallbackAI->m_waitingForPath;
	fallbackAI->friend_startingMove();
	return true;
}
