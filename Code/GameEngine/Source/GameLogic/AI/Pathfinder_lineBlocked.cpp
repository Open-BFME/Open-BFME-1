// cl: /DNDEBUG /MD
//
// Retail 0x003EE850: construct the 3-arg pathfind payload at 0x003DB640,
// convert both world endpoints to cells, iterate, and return whether the
// walk reported a hit.

typedef int Int;
typedef int Bool;
typedef unsigned int size_t;

inline void *operator new(size_t, void *p)
{
	return p;
}

struct Coord3D
{
	float x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class Object;
class Pathfinder;

class Rva003DB640Info
{
public:
	Rva003DB640Info(Pathfinder *pathfinder, Object *obj, Int value);

	unsigned char m_body[0x50];
};

class Pathfinder
{
public:
	bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003DB640Info *info);
	Bool lineBlocked(Object *obj, Int value, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end);
};

// ?lineBlocked@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2@Z
Bool Pathfinder::lineBlocked(Object *obj, Int value, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x50];
	Rva003DB640Info *payload = new (storage) Rva003DB640Info(this, obj, value);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) != 0;
}
