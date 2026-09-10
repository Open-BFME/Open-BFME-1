// ?classifyMapCell@Pathfinder@@SAXHHPAVPathfindCell@@@Z
// partial score=0.22 date=2026-09-10
// ?classifyMap@Pathfinder@@IAEXXZ

#include <math.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

// BFME keeps the cell spacing in the same singleton storage used by the
// terrain scorers.  These unnamed fields are read-only here; the slope
// parser owns the actual limit storage at 0x012F1064.
#define BFME_CELL_SIZE (*(Real *)0x01075C74)
#define BFME_ZERO_RANGE (*(const Real *)0x01075350)
#define BFME_DEFAULT_BU (*(Real *)0x01075334)
#define BFME_LIFT_ZT (*(const double *)0x0107FD90)
#define BFME_SLOPE_INIT (*(unsigned int *)0x012F10A0)
#define BFME_SLOPE_LIMITS ((Real *)0x012F1064)
#define BFME_SLOPE_MULTIPLIERS ((Real *)0x012B4BFC)
#define BFME_SLOPE_THRESHOLD (*(Real *)0x012B4C04)


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

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PathfindCell
{
public:
		enum CellType
	{
		CELL_CLEAR = 0,
		CELL_WATER = 1,
		CELL_CLIFF = 2,
		CELL_OBSTACLE = 4
	};

	CellType getType(void) const { return (CellType)m_type; }
	unsigned int getBits(void) const { return *(const unsigned int *)((const char *)this + 0x0c); }
	void setBits(unsigned int bits) { *(unsigned int *)((char *)this + 0x0c) = bits; }
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

// Only the retail slots used by classifyMapCell are named.  The intervening
// slots are authentic vtable positions, not callable fallback bodies.
__declspec(novtable) class TerrainLogic
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2C(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot3C(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot48(void) = 0;
	virtual bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ) = 0;
	virtual bool isCliffCell(Real x, Real y) const = 0;
	virtual void slot54(void) = 0;
	virtual bool bfmeTerrainFlag58(Real x, Real y) = 0;
	virtual bool bfmeTerrainFlag5C(Real x, Real y) = 0;
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder;

class AI
{
private:
	char m_bfmeHead[0x14];

public:
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

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

void Pathfinder::classifyMapCell(Int i, Int j, PathfindCell *cell)
{
	Coord3D topLeftCorner, bottomRightCorner;
	Bool hasObstacle = (cell->getType() == PathfindCell::CELL_OBSTACLE);

	topLeftCorner.y = (Real)j * BFME_CELL_SIZE;
	bottomRightCorner.y = topLeftCorner.y + BFME_CELL_SIZE;
	topLeftCorner.x = (Real)i * BFME_CELL_SIZE;
	bottomRightCorner.x = topLeftCorner.x + BFME_CELL_SIZE;
	cell->setPinched(false);

	PathfindCell::CellType type = PathfindCell::CELL_CLEAR;
	if (TheTerrainLogic->isCliffCell(topLeftCorner.x, topLeftCorner.y))
	{
		type = PathfindCell::CELL_CLIFF;
	}

	unsigned int bits = cell->getBits();
	if (TheTerrainLogic->bfmeTerrainFlag58(topLeftCorner.x, topLeftCorner.y))
		bits |= 0x00200000;
	else
		bits &= 0xffdfffff;
	cell->setBits(bits);

	bits = cell->getBits();
	if (TheTerrainLogic->bfmeTerrainFlag5C(topLeftCorner.x, topLeftCorner.y))
		bits |= 0x01000000;
	else
		bits &= 0xfeffffff;
	cell->setBits(bits);

	if (type != PathfindCell::CELL_CLIFF)
	{
		Real terrainZ;
		Real waterZ;
		Real waterDepth = *(Real *)((char *)TheAI->m_pathfinder + 0x9c);

		if (TheTerrainLogic->isUnderwater(topLeftCorner.x, topLeftCorner.y,
			&waterZ, &terrainZ) && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (TheTerrainLogic->isUnderwater(topLeftCorner.x, bottomRightCorner.y,
			&waterZ, &terrainZ) && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (TheTerrainLogic->isUnderwater(bottomRightCorner.x, bottomRightCorner.y,
			&waterZ, &terrainZ) && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
		if (TheTerrainLogic->isUnderwater(bottomRightCorner.x, topLeftCorner.y,
			&waterZ, &terrainZ) && waterZ - terrainZ > waterDepth)
			type = PathfindCell::CELL_WATER;
	}

	if (hasObstacle)
		type = PathfindCell::CELL_OBSTACLE;
	cell->setType(type);

	if ((BFME_SLOPE_INIT & 1) == 0)
	{
		BFME_SLOPE_INIT |= 1;
		BFME_SLOPE_THRESHOLD = BFME_DEFAULT_BU /
			((Real)sqrt(BFME_LIFT_ZT) * BFME_CELL_SIZE);
	}

	Real heights[4];
	heights[0] = TheTerrainLogic->getGroundHeight(topLeftCorner.x,
		topLeftCorner.y, 0);
	heights[1] = TheTerrainLogic->getGroundHeight(topLeftCorner.x,
		bottomRightCorner.y, 0);
	heights[2] = TheTerrainLogic->getGroundHeight(bottomRightCorner.x,
		topLeftCorner.y, 0);
	heights[3] = TheTerrainLogic->getGroundHeight(bottomRightCorner.x,
		bottomRightCorner.y, 0);

	cell->setBits(cell->getBits() & 0xff3fffff);
	unsigned int slopeMask = 0x00400000;
	for (Real *slopeLimit = BFME_SLOPE_LIMITS;
		slopeLimit < BFME_SLOPE_LIMITS + 3;
		++slopeLimit, slopeMask += 0x00400000)
	{
		if (*slopeLimit == BFME_ZERO_RANGE)
		{
			Bool sloped = false;
			for (Int corner = 0; corner < 3 && !sloped; ++corner)
			{
				if (fabs((heights[corner + 1] - heights[0]) *
					BFME_SLOPE_MULTIPLIERS[corner]) > *slopeLimit)
					sloped = true;
			}
			if (sloped)
				cell->setBits(cell->getBits() ^
					((cell->getBits() ^ slopeMask) & 0x00c00000));
		}
	}
}

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
