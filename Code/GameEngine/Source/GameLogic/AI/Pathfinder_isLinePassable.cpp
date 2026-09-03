// cl: /DNDEBUG /MD
//
// Retail 0x003EE8D0: Pathfinder convenience overload that fills BFME's
// BfmeCheckMovementInfo with crusher=0, restrictSurfaces=1, allowPinched=1
// and walks the segment.  Returns whether the cell iterator reported no hit.

typedef int Int;
typedef int Bool;
typedef unsigned int size_t;

inline void *operator new(size_t, void *p)
{
	return p;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, BfmeCheckMovementInfo *info);
	Bool isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end, Bool considerTransient);
};

// ?isLinePassable@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2H@Z
Bool Pathfinder::isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld, Bool considerTransient)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x58];
	BfmeCheckMovementInfo *payload = new (storage) BfmeCheckMovementInfo(
		this, obj, zone, considerTransient, 0, 1, 1);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}
