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
	void getBoundsIlt(Region2D *bounds) const;
};

class PolygonTrigger : public Bridge
{
public:
	Bool pointInTriggerIlt(ICoord3D &point) const;
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
	void markZonesDirtyIlt(const IRegion2D *bounds, Bool force);
};

// Retail calls ILT 0x00015307, which the ledger defines as ?j_00015307@@YAXXZ.
extern void j_00015307();
typedef void (PathfindZoneManager::*MarkZonesDirtyIlt)(const IRegion2D *bounds, Bool force);
// Retail calls ILT 0x0000FEE8 (getBounds) and ILT 0x0004AB6F (pointInTrigger), both defined in the ledger.
extern void j_0000fee8();
extern void j_0004ab6f();
typedef void (Bridge::*GetBoundsIlt)(Region2D *bounds) const;
typedef Bool (PolygonTrigger::*PointInTriggerIlt)(ICoord3D &point) const;
template<class T> T iltMemberCall(void (*p)()) { union { void (*plain)(); T member; } call; call.plain = p; return call.member; }

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
	(area->*iltMemberCall<GetBoundsIlt>(j_0000fee8))((Region2D *)&bounds);

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

			if (!(area->*iltMemberCall<PointInTriggerIlt>(j_0004ab6f))(cellPos))
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
		(self->m_zoneManager.*iltMemberCall<MarkZonesDirtyIlt>(j_00015307))(&cellBounds, false);
}
