// cl: /DNDEBUG /MD
//
// Retail 0x003EE7A0: eight-argument isLinePassable.  Fills BfmeCheckMovementInfo
// with the caller's crusher/restrictSurfaces flags and allowPinched=0, then
// walks the segment.

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

class BfmeCheckMovementInfo
{
public:
	BfmeCheckMovementInfo(Pathfinder *pathfinder, Object *obj, Int zone,
		Bool considerTransient, Bool isCrusher, Bool restrictSurfaces,
		Bool allowPinched);

	unsigned char m_body[0x58];
};

class Pathfinder
{
public:
	bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, BfmeCheckMovementInfo *info);
	Bool isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end, Bool considerTransient,
		Bool isCrusher, Bool restrictSurfaces);
};

// ?isLinePassable@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2HHH@Z
Bool Pathfinder::isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld, Bool considerTransient,
	Bool isCrusher, Bool restrictSurfaces)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x58];
	BfmeCheckMovementInfo *payload = new (storage) BfmeCheckMovementInfo(
		this, obj, zone, considerTransient, isCrusher, restrictSurfaces, 0);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}
