// cl: /DNDEBUG /MD
//
// Retail 0x003E6110: the seven-argument destination-query payload constructor
// used by Pathfinder::adjustDestination.

typedef int Int;
typedef unsigned char Bool;

struct Coord3D
{
	float x, y, z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class Object;
class Pathfinder;

class Player
{
public:
	unsigned char m_pad[0x2c];
	Int m_playerType;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj,
		const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class Pathfinder
{
public:
	void bfmeQuery(Object *obj, Int *radius, Bool *center);
};

class Rva003E6110Info
{
public:
	Rva003E6110Info(Pathfinder *pathfinder, Object *obj, void *arg3,
		const Coord3D *pos, const Coord3D *groupPos, Int arg6, Int arg7);

	Pathfinder * volatile m_pathfinder;
	Object * volatile m_obj;
	void * volatile m_arg3;
	Bool m_notComputer;
	Bool m_center;
	Int m_radius;
	const Coord3D * m_groupPos;
	Int m_layer;
	Int volatile m_arg6;
	Int m_pad20;
	Int m_pad24;
	Int m_zero28;
	Int volatile m_arg7;
	Coord3D m_pos;
};

Rva003E6110Info::Rva003E6110Info(Pathfinder *pathfinder, Object *obj,
	void *arg3, const Coord3D *pos, const Coord3D *groupPos, Int arg6,
	Int arg7)
{
	m_pathfinder = pathfinder;
	m_arg3 = arg3;
	m_groupPos = groupPos;
	m_arg6 = arg6;
	m_obj = obj;
	m_arg7 = arg7;
	m_zero28 = 0;

	Coord3D *destination = &m_pos;
	destination->x = pos->x;
	destination->y = pos->y;
	destination->z = pos->z;

	Int notComputer;
	if (m_obj->getControllingPlayer() != 0 &&
		m_obj->getControllingPlayer()->m_playerType == 1)
		notComputer = 0;
	else
		notComputer = 1;
	m_notComputer = notComputer;

	(*(Pathfinder * volatile *)&m_pathfinder)->bfmeQuery(m_obj, &m_radius,
		&m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(obj,
		(const Coord3D *)&m_pos);
	if (m_groupPos != 0)
		m_layer = TheTerrainLogic->getLayerForDestination(0,
			(const Coord3D *)m_groupPos);
}
