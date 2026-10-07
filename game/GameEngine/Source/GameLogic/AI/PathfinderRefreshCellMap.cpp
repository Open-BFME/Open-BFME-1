// Refreshes Pathfinder's derived map state after either late dirty flag is set.

struct BfmePathfindExtent
{
	int value[4];
};

struct BfmePathfindLayer44
{
	char value[0x44];
};

class PathfindCell;
class PathfindLayer;
struct IRegion2D;

// Retail calls ILT 0x00020A13 -> 0x00408F80, the matched calculateZones.
class PathfindZoneManager
{
public:
	void calculateZones(PathfindCell **map, PathfindLayer layers[],
		const IRegion2D &extent);
	char m_bfmeOpaque;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void bfmeRefreshCellMap(void);
	void bfmePrepareRefresh(void);

private:
	char m_bfmeHead[0x10];
	void *m_bfmeMap;                         // +0x10
	BfmePathfindExtent m_bfmeExtent;         // +0x14
	char m_bfmeToLayers[0x85c - 0x24];
	BfmePathfindLayer44 m_bfmeLayers[16];    // +0x85c
	PathfindZoneManager m_bfmeZones;     // +0xc9c
	char m_bfmeToFlags[0x243f4 - 0xc9d];
	unsigned char m_bfmeDirtyA;              // +0x243f4
	unsigned char m_bfmeDirtyB;              // +0x243f5
};

// ?bfmeRefreshCellMap@Pathfinder@@QAEXXZ
void Pathfinder::bfmeRefreshCellMap(void)
{
	if (m_bfmeMap != 0)
	{
		if (m_bfmeDirtyA || m_bfmeDirtyB)
			bfmePrepareRefresh();
		m_bfmeZones.calculateZones((PathfindCell **)m_bfmeMap, (PathfindLayer *)m_bfmeLayers, *(const IRegion2D *)&m_bfmeExtent);
	}
}
