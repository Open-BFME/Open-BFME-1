// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003D93A0: Pathfinder::getLayer(const Coord3D *).
//
// PathfindCell's retail layout is the one established by
// reference/shims/pathfind/GameLogic/AIPathfind.h: the packed dword is at
// +0x0c and its layer occupies bits 6..11.  This TU keeps the declaration
// local because the canonical shim does not declare this Pathfinder method.
// getGroundCell is only the ground-map subset of the layer-aware
// Pathfinder::getCell(layer,x,y) contract; it is not a new exported identity.

typedef int Int;
typedef bool Bool;

struct Coord3D;

struct ICoord2D
{
	Int x;
	Int y;
};

class PathfindCell
{
public:
	Int getLayer(void) const
	{
		return (Int)((m_packed >> 6) & 0x3f);
	}

private:
	void *m_info;
	Int m_unused1;
	Int m_unused2;
	unsigned int m_packed;
};

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *position, ICoord2D *cell);
	Int getLayer(const Coord3D *worldPosition);

private:
	__forceinline PathfindCell *getGroundCell(Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
			return (PathfindCell *)((unsigned char *)m_map[x] +
				y * sizeof(PathfindCell));
		return 0;
	}

	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
};

Int Pathfinder::getLayer(const Coord3D *worldPosition)
{
	if (m_map == 0)
		return 1;

	ICoord2D cell;
	if (worldToCell(worldPosition, &cell))
		return 1;

	PathfindCell *pathCell = getGroundCell(cell.x, cell.y);
	if (pathCell != 0)
		return pathCell->getLayer();
	return 1;
}
