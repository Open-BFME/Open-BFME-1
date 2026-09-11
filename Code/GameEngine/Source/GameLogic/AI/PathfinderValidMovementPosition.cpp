// cl: /DNDEBUG /MD
//
// Retail 0x003DB520: Pathfinder::validMovementPosition.  The exact
// four-argument BFME ABI is anchored by AIUpdateInterface's matched caller at
// 0x0026F280 and by the ILT at 0x0003B359; BFME puts the position first and
// the moving object last, unlike the related Zero Hour overload.
//
// The second matched caller is Pathfinder::internalFindPath at 0x003F0340.
// Both call sites agree with the upstream operation: convert the destination
// to pathfind coordinates, enforce the requested layer, then test the cell
// using the moving object's template and player properties.  The views below
// name only fields and methods exercised by this retail body.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

class PathfindCell
{
public:
	Int getLayer(void) const
	{
		return (m_packed >> 6) & 0x3f;
	}

private:
	void *m_info;
	Int m_unused04;
	Int m_unused08;
	UnsignedInt m_packed;
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
	unsigned char m_aircraftGoalFlag;
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

class Object
{
public:
	Bool bfmeIsComputerControlled(void) const;
	const BfmeThingTemplate *getTemplate(void) const
	{
		return m_template.operator->();
	}

private:
	void *m_vtable;
	BfmeOverride<BfmeThingTemplate> m_template;
};

// Retail layout consumed by the already matched per-cell predicate at
// 0x003D4F90.
struct BfmeMovementPositionInfo
{
	UnsignedInt m_surfaces;
	unsigned char m_allowAircraftGoal;
	unsigned char m_computerControlled;
	unsigned char m_pad06[2];
	Int m_maxLayer;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool bfmeStepD4F90(void *state, PathfindCell *cell);
	Bool validMovementPosition(const Coord3D *pos, PathfindLayerEnum layer,
		UnsignedInt validSurfaces, Object *object);
};

Bool Pathfinder::validMovementPosition(const Coord3D *pos,
	PathfindLayerEnum layer, UnsignedInt validSurfaces, Object *object)
{
	Int x = (Int)(pos->x * 0.1f);
	Int y = (Int)(pos->y * 0.1f);

	PathfindCell *cell = getCell(layer, x, y);
	if (cell == 0)
		return false;
	if (layer >= 17 && layer <= 64 && cell->getLayer() != layer)
		return false;

	BfmeMovementPositionInfo info;
	Int maxLayer = object->getTemplate()->m_pathfindMaxLayer;
	unsigned char aircraftGoalFlag =
		object->getTemplate()->m_aircraftGoalFlag;
	info.m_surfaces = validSurfaces;
	info.m_allowAircraftGoal = aircraftGoalFlag == 0;
	info.m_computerControlled = object->bfmeIsComputerControlled();
	info.m_maxLayer = maxLayer - 1;

	return bfmeStepD4F90(&info, getCell(layer, x, y));
}
