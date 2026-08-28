// Compact the zone equivalency IDs, then rewrite every PathfindCell in the
// supplied global region. The large local array is BFME's fixed 24,000-zone
// scratch space.

typedef int Int;
typedef unsigned short zoneStorageType;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct PathfindCell
{
	unsigned char m_prefix[10];
	zoneStorageType m_zone;
	unsigned char m_tail[4];
};

#pragma pack(push, 1)
class PathfindZoneManager
{
public:
	void bfmeCollapseZones(PathfindCell **map,
		const IRegion2D &globalBounds, bool unused);

private:
	unsigned char m_beforeEquivalency[0x18];
	zoneStorageType m_zoneEquivalency[24000];
	unsigned char m_beforeMaxZone[0x23298 - 0x18 - 24000 * 2];
	Int m_maxZone;
};
#pragma pack(pop)

// ?bfmeCollapseZones@PathfindZoneManager@@QAEXPAPAUPathfindCell@@ABUIRegion2D@@_N@Z
void PathfindZoneManager::bfmeCollapseZones(PathfindCell **map,
	const IRegion2D &globalBounds, bool unused)
{
	const Int maxZones = 24000;
	Int totalZones = m_maxZone;
	m_maxZone = 1;
	zoneStorageType collapsedZones[maxZones];
	collapsedZones[0] = 0;

	Int i = 1;
	while (i < totalZones)
	{
		Int zone = m_zoneEquivalency[i];
		if (zone == i)
		{
			collapsedZones[i] = m_maxZone;
			++m_maxZone;
		}
		else
		{
			collapsedZones[i] = collapsedZones[zone];
		}
		++i;
	}

	Int j = globalBounds.lo.y;
	while (j <= globalBounds.hi.y)
	{
		i = globalBounds.lo.x;
		while (i <= globalBounds.hi.x)
		{
			PathfindCell &cell = map[i][j];
			cell.m_zone = collapsedZones[cell.m_zone];
			++i;
		}
		++j;
	}
}
