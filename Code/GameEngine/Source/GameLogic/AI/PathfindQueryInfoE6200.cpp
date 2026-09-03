// ??0Rva003E6200Info@@QAE@PAVPathfinder@@PAVObject@@PAXPBUCoord3D@@H@Z
// partial score=0.95 date=2026-09-03
// cl: /DNDEBUG /MD
//
// Retail 0x003E6200: five-argument pathfinding query payload constructor.

typedef int Int;
typedef unsigned char Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_pad[0x2c];
	Int m_playerType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void bfmeQuery(Object *obj, Int *radius, Bool *center);
};

class Rva003E6200Info
{
public:
	Rva003E6200Info(Pathfinder *pathfinder, Object *obj, void *arg3,
		const Coord3D *pos, Int arg5);

	Pathfinder * volatile m_pathfinder;
	Object * volatile m_obj;
	void * volatile m_arg3;
	Bool m_notComputer;
	Bool m_center;
	Int m_radius;
	PathfindLayerEnum m_layer;
	Int volatile m_arg5;
	Int m_pad1C;
	Int m_pad20;
	Int volatile m_zero24;
	volatile Coord3D m_pos;
};

Rva003E6200Info::Rva003E6200Info(Pathfinder *pathfinder, Object *obj, void *arg3,
	const Coord3D *pos, Int arg5)
{
	Pathfinder *p = *(Pathfinder * volatile *)&pathfinder;
	Object *object = obj;
	void *extra = arg3;
	Int n = arg5;
	m_obj = object;
	m_arg3 = extra;
	m_pathfinder = p;
	m_arg5 = n;
	m_zero24 = 0;
	Object *o = obj;
	const Coord3D *c = pos;

	m_pos.x = pos->x;
	m_pos.y = pos->y;
	m_pos.z = pos->z;

	Int notComputer;
	if (m_obj->getControllingPlayer() != 0 && m_obj->getControllingPlayer()->m_playerType == 1)
		notComputer = 0;
	else
		notComputer = 1;
	m_notComputer = notComputer;

	(*(Pathfinder * volatile *)&m_pathfinder)->bfmeQuery(m_obj, &m_radius, &m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(o, c);
}
