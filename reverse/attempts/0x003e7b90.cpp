// ?rva003e7b90@Pathfinder@@QAEEPAVObject@@PBUCoord3D@@11@Z
// partial score=0.19 date=2026-09-16
// cl: /DNDEBUG /MD
//
// Retail 0x003E7B90 is the Pathfinder cell/layer transition callback.  The
// surrounding caller proves the Pathfinder receiver, but no semantic method
// name is established; retain the address in the method name.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

struct BfmeMovementPositionInfo
{
	UnsignedInt m_surfaces;
	Bool m_allowAircraftGoal;
	Bool m_computerControlled;
	Bool m_pad06[2];
	Int m_maxLayer;
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);
	BfmeOverridable *getNextOverride(void) const
	{
		return m_nextOverride;
	}

private:
	void *m_vtable;
	BfmeOverridable *m_nextOverride;
};

class BfmeThingTemplate
{
public:
	unsigned char m_opaque000[0x444];
	Int m_pathfindMaxLayer;
	unsigned char m_opaque448[0x4cc - 0x448];
	Bool m_aircraftGoalFlag;
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		BfmeOverridable *next = m_overridable->getNextOverride();
		if (next)
			return (const T *)next->friend_getFinalOverride();
		return (const T *)m_overridable;
	}

private:
	BfmeOverridable *m_overridable;
};

struct AIUpdateInterface
{
	unsigned char m_pad000[0x1b8];
	UnsignedInt m_validSurfaces;
};

class Object
{
public:
	Bool bfmeIsComputerControlled(void) const;

	const BfmeThingTemplate *getTemplate(void) const
	{
		return m_template.operator->();
	}

	void *m_vtable;
	BfmeOverride<BfmeThingTemplate> m_template;
	unsigned char m_pad008[0x1fc];
	AIUpdateInterface *m_ai;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;
extern const Real g_bfmeK1266C;

class PathfindCell
{
public:
	unsigned char m_pad00[0xc];
	UnsignedInt m_word;
};

class Pathfinder
{
public:
	Bool sameCell(Object *object, Coord3D from, Coord3D to);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool bfmeQuery(Object *object, Int *radius, Bool *center);
	Bool worldToCell(const Coord3D *position, ICoord2D *cell);
	Bool bfmeStepD4F90(void *state, PathfindCell *cell);
	Bool rva003e7b90(Object *object, const Coord3D *layerPosition,
		const Coord3D *from, const Coord3D *to);
};

extern bool rva3d5170(Int value);

Bool Pathfinder::rva003e7b90(Object *object,
	const Coord3D *layerPosition, const Coord3D *from,
	const Coord3D *to)
{
	Pathfinder *pathfinder = this;
	Object *obj = object;
	if (pathfinder->sameCell(obj, *from, *to))
		goto success;

	Int maxLayer = obj->getTemplate()->m_pathfindMaxLayer;
	Bool aircraftGoal = obj->getTemplate()->m_aircraftGoalFlag;
	AIUpdateInterface *ai = obj->m_ai;
	Bool computerControlled = obj->bfmeIsComputerControlled();
	UnsignedInt surfaces = ai->m_validSurfaces;

	BfmeMovementPositionInfo info;
	info.m_surfaces = surfaces;
	info.m_allowAircraftGoal = aircraftGoal == 0;
	info.m_computerControlled = computerControlled;
	info.m_maxLayer = maxLayer - 1;

	PathfindLayerEnum layer =
		TheTerrainLogic->getLayerForDestination(obj, from);

	Int radius;
	Bool center;
	bfmeQuery(obj, &radius, &center);

	Coord3D adjusted = *from;
	if (!center)
	{
		adjusted.x += g_bfmeK1266C;
		adjusted.y += g_bfmeK1266C;
	}

	ICoord2D cell;
	PathfindCell *pathCell;
	if (worldToCell(&adjusted, &cell))
		pathCell = 0;
	else
		pathCell = getCell(layer, cell.x, cell.y);

	if (!bfmeStepD4F90(&info, pathCell))
		return false;

	PathfindLayerEnum targetLayer =
		TheTerrainLogic->getLayerForDestination(obj, layerPosition);
	if (targetLayer == layer)
		goto success;

	UnsignedInt word = pathCell->m_word;
	Int connection = (word >> 12) & 0x3f;
	if (connection == 0)
		return false;
	Int cellLayer = (word >> 6) & 0x3f;
	if (cellLayer == targetLayer && connection != layer)
		return false;
	if (connection == targetLayer && cellLayer != layer)
		return false;

	if (targetLayer == 1)
		goto success;
	if (targetLayer == 0x10)
		goto success;
	if (!rva3d5170(targetLayer))
		goto success;
	if (layer == 0x10)
		goto success;
	return false;

success:
	return true;
}
