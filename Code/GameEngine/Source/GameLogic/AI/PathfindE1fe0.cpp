// cl: /DNDEBUG /MD
//
// Retail 0x003E1FE0: BFME's line-walk that pulls a destination back onto the
// last cell the walk could reach -- Zero Hour's Pathfinder::tightenPath
// (AIPathfind.cpp:8438) reduced to a single line segment.
//
// Same opening as 0x003E1F10: ask the pathfinder for the object's radius and
// centre flag through Pathfinder::bfmeQuery (BFME's out-of-line form of ZH's
// inlined getRadiusAndCenter), and when the object does not centre in its cell
// nudge both endpoints by half a cell.  The nudge on `to` is done in place on
// the caller's Coord3D and is undone again on the way out.
//
// The user data is BFME's Rva003D7680Struct: pathfinder at +0x00, a pointer to
// the working position at +0x04 and the layer at +0x08 -- the same "Pathfinder*
// first" shape every other converted callback payload in this region uses.
//
// Frame notes (retail gets by with exactly 0x2C bytes of locals):
//   * the radius output and the destination cell both live on top of the local
//     copy of `from`, so both are expressed as aliases of it;
//   * `pos` and the payload are the only other locals.
//
// No /EHsc: retail registers no handler for the body.

typedef int Int;
typedef unsigned char Bool;

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

enum PathfindLayerEnum { LAYER_GROUND = 1 };

#define PATHFIND_CELL_SIZE_F 10.0f

class Pathfinder;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Int getLayer(void) const;							///< ILT thunk at 0x0003A391
};

// BFME's replacement for ZH's TightenPathStruct.
struct Rva003D7680Struct
{
	Pathfinder *m_pathfinder;							///< retail this+0x00
	Coord3D *m_pos;										///< retail this+0x04
	Int m_layer;										///< retail this+0x08
};

struct TightenLineWork
{
	Coord3D adjFrom;									///< frame esp+0x00
	ICoord2D fromCell;									///< frame esp+0x0C
	Coord3D pos;										///< frame esp+0x14
	Rva003D7680Struct info;								///< frame esp+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void tightenLine(Object *obj, const Coord3D *from, Coord3D *to);

	void bfmeQuery(Object *obj, Int *radius, Bool *center);	///< ILT thunk at 0x000461FF
	bool worldToCell(const Coord3D *world, ICoord2D *cell);	///< ILT thunk at 0x000171E8
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003D7680Struct *info);	///< ILT thunk at 0x00048419
};

// ?tightenLine@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@PAU2@@Z
void Pathfinder::tightenLine(Object *obj, const Coord3D *from, Coord3D *to)
{
	TightenLineWork w;
	Bool center;
	bfmeQuery(obj, (Int *)&w.adjFrom.x, &center);
	Bool centerInCell = *(volatile Bool *)&center;

	w.adjFrom.x = from->x;
	w.adjFrom.y = from->y;
	w.adjFrom.z = from->z;

	if (!centerInCell) {
		w.adjFrom.x += PATHFIND_CELL_SIZE_F/2;
		w.adjFrom.y += PATHFIND_CELL_SIZE_F/2;
		to->x += PATHFIND_CELL_SIZE_F/2;
		to->y += PATHFIND_CELL_SIZE_F/2;
	}

	w.pos.x = w.adjFrom.x;
	w.pos.y = w.adjFrom.y;
	w.pos.z = w.adjFrom.z;

	w.info.m_pos = &w.pos;
	w.info.m_pathfinder = this;
	w.info.m_layer = obj->getLayer();

	worldToCell(&w.adjFrom, &w.fromCell);

	ICoord2D &toCell = *(ICoord2D *)&w.adjFrom;
	worldToCell(to, &toCell);

	if (iterateCellsAlongLine(w.fromCell, toCell, LAYER_GROUND, &w.info)) {
		*to = w.pos;
	}

	if (!centerInCell) {
		to->x -= PATHFIND_CELL_SIZE_F/2;
		to->y -= PATHFIND_CELL_SIZE_F/2;
	}
}
