// cl: /EHsc /GR-
// Pathfinder::tightenPath — BFME retail shape (RVA 0x003F5FD0, 143 bytes).
// Isolated TU: ZH AIPathfind.cpp still carries the Generals-era 5-arg iterate
// and a smaller TightenPathStruct; retail uses a 0x34-byte info block, a
// 2-arg TerrainLogic::getLayerForDestination, a 4-arg ICoord2D iterate that
// hardcodes the tighten callback, and an out-of-line info initializer.

typedef int Int;
typedef bool Bool;
typedef float Real;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

class Object;
class LocomotorSet;
class Pathfinder;

// Retail TerrainLogic::getLayerForDestination takes a nullable first arg
// (often 0/NULL, or an Object*) plus the destination Coord3D*. ret 0x8.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

// Retail info block for the harden-coded iterate callback at 0x003F1840.
// Layout proven from the sole initializer body at 0x003E1720:
//   +0x00 pathfinder, +0x04 obj, +0x08 locomotorSet, +0x0c radius,
//   +0x10 center, +0x14 layer, +0x18 foundDest, +0x1c initial/scratch Coord3D,
//   +0x28 destPos Coord3D.  sizeof 0x34.
struct TightenPathStruct
{
	Pathfinder *pathfinder;
	Object *obj;
	const LocomotorSet *locomotorSet;
	Int radius;
	Bool center;
	PathfindLayerEnum layer;
	Bool foundDest;
	Coord3D scratch;
	Coord3D destPos;

	// Out-of-line: retail emits a call to the initializer at thunk 0x0002D7F9
	// (body 0x003E1720). Declared only; REL32 pinned in symbols.csv.
	TightenPathStruct(Pathfinder *pf, Object *o, const LocomotorSet *ls,
		PathfindLayerEnum lay, const Coord3D *to);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);

protected:
	// 4-arg BFME iterate (no CellAlongLineProc): always invokes the tighten
	// callback body with userData as ecx. Thunk 0x000190B0 / body 0x003F1F00.
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, void *userData);

	void tightenPath(Object *obj, const LocomotorSet &locomotorSet,
		Coord3D *from, const Coord3D *to);
};

// ?tightenPath@Pathfinder@@IAEXPAVObject@@ABVLocomotorSet@@PAUCoord3D@@PBU4@@Z
void Pathfinder::tightenPath(Object *obj, const LocomotorSet &locomotorSet,
	Coord3D *from, const Coord3D *to)
{
	// Local order chosen so MSVC 7.1 places two ICoord2D cells below the 0x34
	// info block inside a 0x44-byte frame (retail: end@+0x10, start@+0x18,
	// info@+0x20 after the four saved registers).
	ICoord2D end;
	ICoord2D start;
	// RTL ctor-arg eval pushes `to` first, then getLayer(obj,from) (which
	// leaves `to` under the layer result for the 5-arg initializer), matching
	// retail's intentional leftover-stack setup between the two calls.
	TightenPathStruct info(this, obj, &locomotorSet,
		TheTerrainLogic->getLayerForDestination(obj, from), to);

	// Pull layer into a register before the worldToCell calls so it survives
	// in ebp across them (retail: mov ebp,[esp+0x34] immediately after ctor).
	PathfindLayerEnum layer = info.layer;
	worldToCell(from, &start);
	worldToCell(to, &end);
	iterateCellsAlongLine(start, end, layer, &info);
	if (info.foundDest)
	{
		// Three dword loads/stores (eax,ecx,edx) — matches retail's unrolled
		// Coord3D copy through edi rather than a block move.
		*from = info.destPos;
	}
}
