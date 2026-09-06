// ?classifyMap@Pathfinder@@IAEXXZ

typedef int Bool;
typedef int Int;


struct ICoord2D
{
	Int x;
	Int y;
};

struct BfmePathfindExtent
{
	ICoord2D lo;
	ICoord2D hi;
};

class PathfindCell
{
public:
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_CLIFF = 2
	};

	CellType getType(void) const { return (CellType)m_type; }
	unsigned int getBits(void) const { return *(const unsigned int *)((const char *)this + 0x0c); }
	Bool getPinched(void) const { return m_pinched; }
	void setPinched(Bool pinch) { m_pinched = pinch; }
	void setType(CellType type);

private:
	char m_bfmeHead[0x0c];
	unsigned int m_type : 3;
	unsigned int m_flags : 4;
	unsigned int m_connectsToLayer : 4;
	unsigned int m_layer : 4;
	unsigned int m_unused : 3;
	unsigned int m_pinched : 1;
	unsigned int m_rest : 12;
};

struct BfmePathfindLayer44
{
	char value[0x44];
};

class BfmePathfindZoneManager
{
public:
	void bfmeRebuildZones(void *map, BfmePathfindLayer44 *layers,
		BfmePathfindExtent *extent);
};

class Pathfinder
{
public:
	static void classifyMapCell(Int x, Int y, PathfindCell *cell);

	void bfmePrepareRefresh(void);

	protected:
	void classifyMap(void);

	private:
	char m_bfmeHead[0x10];
	PathfindCell **m_map;
	BfmePathfindExtent m_extent;
	char m_bfmeToLayers[0x85c - 0x24];
	BfmePathfindLayer44 m_layers[16];
	BfmePathfindZoneManager m_zoneManager;
};

void Pathfinder::classifyMap(void)
{
	for (Int j=m_extent.lo.y; j<=m_extent.hi.y; j++)
	{
		for (Int i=m_extent.lo.x; i<=m_extent.hi.x; i++)
		{
			classifyMapCell(i, j, &m_map[i][j]);
		}
	}

	for (Int j=m_extent.lo.y; j<=m_extent.hi.y; j++)
	{
		for (Int i=m_extent.lo.x; i<=m_extent.hi.x; i++)
		{
			if (m_map[i][j].getType() == PathfindCell::CELL_CLIFF)
			{
				for (Int k=i-1; k<i+2; k++)
				{
					if (k<m_extent.lo.x || k>m_extent.hi.x) continue;
					for (Int l=j-1; l<j+2; l++)
					{
						if (l<m_extent.lo.y || l>m_extent.hi.y) continue;
						if (m_map[k][l].getType() == PathfindCell::CELL_CLEAR)
						{
							m_map[k][l].setPinched(true);
						}
					}
				}
			}
		}
	}

	for (Int j=m_extent.lo.y; j<=m_extent.hi.y; j++)
	{
		for (Int i=m_extent.lo.x; i<=m_extent.hi.x; i++)
		{
			unsigned int bits = m_map[i][j].getBits();
			unsigned char pinched = (unsigned char)(bits >> 18);
			if (pinched & 1)
			{
				if ((bits & 7) == PathfindCell::CELL_CLEAR)
				{
					m_map[i][j].setType(PathfindCell::CELL_CLIFF);
				}
			}
		}
	}

	bfmePrepareRefresh();
	m_zoneManager.bfmeRebuildZones(m_map, m_layers, &m_extent);
}
