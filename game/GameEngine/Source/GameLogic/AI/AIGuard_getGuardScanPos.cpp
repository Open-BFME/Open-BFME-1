// ?getGuardScanPos@AIGuardMachine@@QAEXPAUCoord3D@@@Z
// Open-BFME: clean reconstruction of retail 0x0015C330.

typedef float Real;
typedef int ObjectID;
typedef unsigned int TeamID;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3D
{
	Real x, y, z;
};

class Object;
class Team;
class PolygonTrigger;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;
#define g_rva01075350 0.0f

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

extern TeamFactory *TheTeamFactory;

class Object
{
public:
	char m_pad00[0x38];
};

// Retail ILT 0x000241FE lands on 0x000EDCD0, matched as
// Team::getEstimateTeamPosition_000EDCD0.
class Team
{
public:
	void getEstimateTeamPosition_000EDCD0(Coord3D *position) const;
};
#define getPosition(position) getEstimateTeamPosition_000EDCD0(position)

// Retail ILT 0x00007AD6 lands on 0x0018F790, matched as
// BfmeA1263::bfmeGet1263.
struct BfmeVec1263;
class BfmeA1263
{
public:
	void bfmeGet1263(BfmeVec1263 *out);
};
#define getCenter(center) bfmeGet1263((BfmeVec1263 *)(center))

class PolygonTrigger
{
};

class AIGuardMachine
{
public:
	void getGuardScanPos(Coord3D *scanPosition);

	char m_pad00[0x10];
	Object *m_owner;
	char m_pad14[0x30];
	ObjectID m_targetToGuard;
	TeamID m_teamToGuard;
	PolygonTrigger *m_areaToGuard;
	Coord3D m_positionToGuard;
	Coord3D m_areaBox;
	unsigned char m_areaFlag;
};

void AIGuardMachine::getGuardScanPos(Coord3D *scanPosition)
{
	Object *targetAddress = TheGameLogic->findObjectByID(m_targetToGuard);
	Team *targetTeam = TheTeamFactory->findTeamByID(m_teamToGuard);
	Coord3D scanAnchor = { 0.0f, 0.0f, 0.0f };

	if (targetAddress)
	{
		targetAddress = (Object *)((unsigned)targetAddress + 0x38);
		_ReadWriteBarrier();
		scanAnchor.x = ((Coord3D *)targetAddress)->x;
		scanAnchor.y = ((Coord3D *)targetAddress)->y;
		scanAnchor.z = ((Coord3D *)targetAddress)->z;
	}
	else if (targetTeam)
	{
		targetTeam->getPosition(&scanAnchor);
	}
	else
	{
		scanAnchor = m_positionToGuard;
	}

	if (m_areaToGuard)
	{
		if (m_areaFlag)
		{
			scanAnchor = m_areaBox;
		}
		else
		{
			((BfmeA1263 *)m_areaToGuard)->getCenter(&scanAnchor);
		}
	}

	if (scanAnchor.x == g_rva01075350 && scanAnchor.y == g_rva01075350)
	{
		Object *ownerPositionAddress = (Object *)((unsigned)m_owner + 0x38);
		_ReadWriteBarrier();
		scanAnchor.x = ((Coord3D *)ownerPositionAddress)->x;
		scanAnchor.y = ((Coord3D *)ownerPositionAddress)->y;
		scanAnchor.z = ((Coord3D *)ownerPositionAddress)->z;
	}

	scanPosition->x = scanAnchor.x;
	scanPosition->y = scanAnchor.y;
	scanPosition->z = scanAnchor.z;
}
