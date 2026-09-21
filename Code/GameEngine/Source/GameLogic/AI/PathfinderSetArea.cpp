// cl: /DNDEBUG /MD /EHsc
// Pathfinder::setArea, retail RVA 0x003F7AB0, 424 bytes.
// The caller through ILT 0x00030B98 and the adjacent classifyFence method
// prove the Pathfinder identity and the receiver offsets used here.

typedef int Int;
typedef bool Bool;

struct ICoord3D
{
	Int x, y, z;
};

struct IRegion2D
{
	Int loX, loY, hiX, hiY;
};

struct Region2D
{
	Int loX, loY, hiX, hiY;
};

class Bridge
{
public:
	void getBounds(Region2D *bounds) const;
	
};

class PolygonTrigger : public Bridge
{
public:
	Bool pointInTrigger(ICoord3D &point) const;
};

class PathfindCell
{
public:
	void setAircraftGoal(Bool blocked) { m_aircraftGoal = blocked; }

private:
	char m_pad[0xc];
	unsigned int m_reserved : 21;
	unsigned int m_aircraftGoal : 1;
	unsigned int m_tail : 10;
};

class PathfindZoneManager
{
public:
	void markZonesDirty(const IRegion2D *bounds, Bool force);
};

class Pathfinder
{
public:
	void setArea(PolygonTrigger *area, Bool blocked);

private:
	char m_pad00[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	char m_pad24[0xc9c - 0x24];
	PathfindZoneManager m_zoneManager;
};

void Pathfinder::setArea(PolygonTrigger *area, Bool blocked)
{
	Pathfinder *self = this;
	IRegion2D bounds;
	area->getBounds((Region2D *)&bounds);

	bounds.loX /= 10;
	bounds.loY /= 10;
	bounds.hiX /= 10;
	bounds.hiY /= 10;

	IRegion2D cellBounds;
	cellBounds.loY = 0x7fffffff;
	cellBounds.loX = 0x7fffffff;
	cellBounds.hiY = -1;
	cellBounds.hiX = -1;

	for (Int cx = bounds.loX; cx <= bounds.hiX; ++cx)
	{
		ICoord3D cellPos;
		cellPos.x = cx * 10 + 5;
		for (Int cy = bounds.loY; cy <= bounds.hiY; ++cy)
		{
			cellPos.y = cy * 10 + 5;

			if (!area->pointInTrigger(cellPos))
				continue;

			if (cx < self->m_extent.loX || cx > self->m_extent.hiX ||
				cy < self->m_extent.loY || cy > self->m_extent.hiY)
				continue;

			PathfindCell *cell = (PathfindCell *)((char *)self->m_map[cx] + cy * 0x10);
			if (!cell)
				continue;

			cell->setAircraftGoal(blocked);

			if (cx < cellBounds.loX)
				cellBounds.loX = cx;
			if (cy < cellBounds.loY)
				cellBounds.loY = cy;
			if (cx > cellBounds.hiX)
				cellBounds.hiX = cx;
			if (cy > cellBounds.hiX)
				cellBounds.hiY = cy;
		}
	}

	if (cellBounds.hiX != -1)
		self->m_zoneManager.markZonesDirty(&cellBounds, false);
}
