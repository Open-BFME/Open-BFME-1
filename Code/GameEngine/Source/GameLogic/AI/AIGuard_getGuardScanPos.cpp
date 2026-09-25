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
#define BfmeZeroRange (*(const Real *)0x01075350)

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

class Team
{
public:
	void getPosition(Coord3D *position);
};

class PolygonTrigger
{
public:
	void getCenter(Coord3D *center);
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
			m_areaToGuard->getCenter(&scanAnchor);
		}
	}

	if (scanAnchor.x == BfmeZeroRange && scanAnchor.y == BfmeZeroRange)
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
