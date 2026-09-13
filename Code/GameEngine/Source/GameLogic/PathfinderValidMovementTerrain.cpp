// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/pathfind
// BFME Pathfinder::validMovementTerrain, retail RVA 0x003D85C0.
//
// The retail ABI takes the layer as an Int, even though the Zero Hour header
// spells the corresponding parameter as PathfindLayerEnum.  Keep this body in
// the retail-layout shim TU so the decorated name and PathfindCell offsets are
// both correct without changing the shared AIPathfind.cpp declarations.

#include "GameLogic/AIPathfind.h"

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride(void);
	LocomotorOverridable *getNextOverride(void) const { return m_nextOverride; }

private:
	void *m_vtable;
	LocomotorOverridable *m_nextOverride;
};

class LocomotorTemplate : public LocomotorOverridable
{
private:
	unsigned char m_opaque[8];

public:
	int m_surfaces;
};

template <class T>
class LocomotorOverride
{
public:
	const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		LocomotorOverridable *next = m_overridable->getNextOverride();
		if (next)
			return (const T *)next->friend_getFinalOverride();
		return m_overridable;
	}

private:
	const T *m_overridable;
};

typedef int LocomotorSurfaceTypeMask;

class Locomotor
{
public:
	LocomotorSurfaceTypeMask getLegalSurfaces(void) const
	{
		return m_template->m_surfaces;
	}

private:
	void *m_vtable;
	LocomotorOverride<LocomotorTemplate> m_template;
};

extern int g_Va012B49FC[];

Bool Pathfinder::validMovementTerrain(Int layer, const Locomotor *locomotor,
	const Coord3D *pos)
{
	Int x = REAL_TO_INT_FLOOR(pos->x / PATHFIND_CELL_SIZE);
	Int y = REAL_TO_INT_FLOOR(pos->y / PATHFIND_CELL_SIZE);

	PathfindCell *toCell = getCell((PathfindLayerEnum)layer, x, y);
	if (toCell == 0)
		return false;

	Int type = toCell->getType();
	if (type == 4)
		return true;
	if (type == 5)
		return true;

	Int cellLayer = toCell->getLayer();
	if (cellLayer != 1 && cellLayer == 0)
		return true;

	LocomotorSurfaceTypeMask acceptableSurfaces = g_Va012B49FC[type];
	if ((locomotor->getLegalSurfaces() & acceptableSurfaces) == 0)
		return false;
	return true;
}
