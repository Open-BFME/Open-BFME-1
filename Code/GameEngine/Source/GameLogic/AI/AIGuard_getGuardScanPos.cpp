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
	void getPosition(Coord3D *out);
};

class PolygonTrigger
{
public:
	void getCenter(Coord3D *out);
};

class AIGuardMachine
{
public:
	void getGuardScanPos(Coord3D *out);

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

void AIGuardMachine::getGuardScanPos(Coord3D *out)
{
	Object *obj = TheGameLogic->findObjectByID(m_targetToGuard);
	Team *team = TheTeamFactory->findTeamByID(m_teamToGuard);
	Coord3D pos = { 0.0f, 0.0f, 0.0f };

	if (obj)
	{
		obj = (Object *)((unsigned)obj + 0x38);
		_ReadWriteBarrier();
		pos.x = ((Coord3D *)obj)->x;
		pos.y = ((Coord3D *)obj)->y;
		pos.z = ((Coord3D *)obj)->z;
	}
	else if (team)
	{
		team->getPosition(&pos);
	}
	else
	{
		pos = m_positionToGuard;
	}

	if (m_areaToGuard)
	{
		if (m_areaFlag)
		{
			pos = m_areaBox;
		}
		else
		{
			m_areaToGuard->getCenter(&pos);
		}
	}

	if (pos.x == BfmeZeroRange && pos.y == BfmeZeroRange)
	{
		Object *owner = (Object *)((unsigned)m_owner + 0x38);
		_ReadWriteBarrier();
		pos.x = ((Coord3D *)owner)->x;
		pos.y = ((Coord3D *)owner)->y;
		pos.z = ((Coord3D *)owner)->z;
	}

	out->x = pos.x;
	out->y = pos.y;
	out->z = pos.z;
}
