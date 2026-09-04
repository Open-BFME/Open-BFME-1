// ?getGuardScanPos@AIGuardMachine@@QAEXPAUCoord3D@@@Z
// partial score=0.72 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// AIGuardMachine::getGuardScanPos, retail 0x0015C330, 278 bytes.
// Called from lookForInnerTarget when the first scan misses. Resolves
// object / team / stored pos / area center, then falls back to the owner
// position if the result is (0, 0).
//
// Closest MSVC 7.1 shape: 276B, first 0x41 bytes match. Wall is CSE hoist of
// the first Coord3D dword ahead of `add edi, 0x38` (retail add-then-load).

typedef float Real;
typedef int ObjectID;
typedef int TeamID;
typedef bool Bool;

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

extern GameLogic *TheGameLogic;				// 0x012F0898

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

extern TeamFactory *TheTeamFactory;			// 0x012ED810

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos;							// +0x38
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
	Object *m_owner;						// +0x10
	char m_pad14[0x44 - 0x14];
	ObjectID m_targetToGuard;				// +0x44
	TeamID m_teamToGuard;					// +0x48
	PolygonTrigger *m_areaToGuard;			// +0x4C
	Coord3D m_positionToGuard;				// +0x50
	Coord3D m_areaBox;						// +0x5C
	unsigned char m_areaFlag;				// +0x68
};

void AIGuardMachine::getGuardScanPos(Coord3D *out)
{
	Object *obj = TheGameLogic->findObjectByID(m_targetToGuard);
	Team *team = TheTeamFactory->findTeamByID(m_teamToGuard);
	Coord3D pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	if (obj)
	{
		obj = (Object *)((unsigned)obj + 0x38);
		pos = *(Coord3D *)obj;
	}
	else if (team)
		team->getPosition(&pos);
	else
	{
		const Coord3D *from = &m_positionToGuard;
		pos = *from;
	}

	if (m_areaToGuard)
	{
		if (m_areaFlag)
		{
			const Coord3D *from = &m_areaBox;
			pos = *from;
		}
		else
			m_areaToGuard->getCenter(&pos);
	}

	if (pos.x == 0.0f && pos.y == 0.0f)
	{
		Object *owner = m_owner;
		owner = (Object *)((unsigned)owner + 0x38);
		pos = *(Coord3D *)owner;
	}

	out->x = pos.x;
	out->y = pos.y;
	out->z = pos.z;
}
