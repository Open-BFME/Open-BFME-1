// cl: /DNDEBUG /MD
//
// Retail 0x003EE970: construct the 3-arg pathfind payload at 0x003E5A50,
// convert both world endpoints to cells, iterate, and return whether the
// walk reported no hit.

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

class Rva003E5A50Info
{
public:
	Rva003E5A50Info(Pathfinder *pathfinder, Object *obj, Int value);

	unsigned char m_body[0x54];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E5A50Info *info);
	Bool lineClear(Object *obj, Int value, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end);
};

// ?lineClear@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2@Z
Bool Pathfinder::lineClear(Object *obj, Int value, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x54];
	Rva003E5A50Info *payload = new (storage) Rva003E5A50Info(this, obj, value);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}
