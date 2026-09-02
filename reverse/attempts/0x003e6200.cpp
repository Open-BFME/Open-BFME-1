// ??0Rva003E6200Info@@QAE@PAVPathfinder@@PAVObject@@PAXPBUCoord3D@@H@Z
// partial score=0.78 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x003E6200: constructor of a BFME pathfind query payload.  Five
// arguments, ret 0x14.  Stores the pathfinder, object, a third pointer, a
// Coord3D and a fifth dword, then asks whether the object's controlling
// player is computer-controlled, fills radius/centre through Pathfinder::
// bfmeQuery, and records TerrainLogic's layer for the destination.

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
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
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
	void getRadiusAndCenter(const Object *obj, Int &radius, bool &center);
};

class Rva003E6200Info
{
public:
	Rva003E6200Info(Pathfinder *pathfinder, Object *obj, void *arg3,
		const Coord3D *pos, Int arg5);

	Pathfinder *m_pathfinder;	// 0x00
	Object *m_obj;				// 0x04
	void *m_arg3;				// 0x08
	Bool m_notComputer;			// 0x0C
	bool m_center;				// 0x0D
	Int m_radius;				// 0x10
	PathfindLayerEnum m_layer;	// 0x14
	Int m_arg5;					// 0x18
	Int m_pad1C;				// 0x1C
	Int m_pad20;				// 0x20
	Int m_zero24;				// 0x24
	Coord3D m_pos;				// 0x28
};

// ??0Rva003E6200Info@@QAE@PAVPathfinder@@PAVObject@@PAXPBUCoord3D@@H@Z
Rva003E6200Info::Rva003E6200Info(Pathfinder *pathfinder, Object *obj, void *arg3,
	const Coord3D *pos, Int arg5)
{
	Pathfinder *pf = pathfinder;
	Int v = arg5;
	Object *o = obj;
	void *a = arg3;
	const Coord3D *c = pos;

	m_obj = o;
	m_arg3 = a;
	m_pathfinder = pf;
	m_arg5 = v;
	m_zero24 = 0;

	m_pos.x = c->x;
	m_pos.y = c->y;
	m_pos.z = c->z;

	if (o->getControllingPlayer() != 0 && o->getControllingPlayer()->m_playerType == 1)
		m_notComputer = 0;
	else
		m_notComputer = 1;

	pf->getRadiusAndCenter(o, m_radius, m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(o, c);
}
