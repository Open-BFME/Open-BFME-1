// cl: /DNDEBUG /MD
//
// Retail 0x003E2620, 773 bytes, reached from Pathfinder::findGroundPath through
// ILT 0x00035A2B with ECX = the pathfinder and a stack struct holding
// {this, false, goalCell, pathDiameter} -- the BFME form of ZH's
// iterateCellsAlongLine(start, end, parentCell->getLayer(), groundCellsCallback,
// &info) with the callback inlined into the same Bresenham walk as
// PathfinderIterateCellsAlongLineRva003D7440.cpp.
// IDENTITY IS NOT RECOVERED: the method and struct names are address-derived.

extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)

typedef int Int;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class PathfindCell;

class PathfindCellInfo
{
public:
	static void allocateCellInfos( void );

	char m_unreconstructed00[0x0c];
	PathfindCellInfo *m_prevOpen;
	unsigned short m_totalCost;
	unsigned short m_costSoFar;
	char m_unreconstructed14[0x10];
	unsigned int m_flags;
};

extern PathfindCellInfo *g_bfmePathfindFreeList;

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *pos );

class PathfindCell
{
public:
	void setParentCellHierarchical( PathfindCell *parent );

	Bool getOpen() const { return m_info ? ((m_info->m_flags >> 3) & 1) : false; }
	Bool getClosed() const { return m_info ? ((m_info->m_flags >> 4) & 1) : false; }
	Int getLayer() const { return (m_packed >> 6) & 0x3f; }

	PathfindCellInfo *m_info;
	char m_unreconstructed04[0x08];
	unsigned int m_packed;
};

class BfmeThingBRE
{
public:
	void bfmeGoBRE( void *what );
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	char m_unreconstructed[0x44];
};

class Pathfinder;

struct Rva003E2620GroundCellsStruct
{
	Pathfinder *thePathfinder;
	Bool centerInCell;
	PathfindCell *goalCell;
	Int pathDiameter;
};

class Pathfinder
{
public:
	Int groundCellsAlongLine003E2620( const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E2620GroundCellsStruct *info );
	Int clearCellForDiameter( Int crusher, Int cellX, Int cellY, Int layer,
		Int pathDiameter, Int attackerOnWall );
	Int rva003db900( PathfindCell *cell, PathfindCell *goalCell );

	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeBuckets[0x34 - 0x24];
	PathfindCellInfo *m_bucketHeads034[(0x834 - 0x34) / 4];
	Int m_lowestBucket834;
	char m_beforeLayers[0x85c - 0x838];
	PathfindLayer m_layers[16];

	__forceinline PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y )
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell( x, y );
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}
};

Int Pathfinder::groundCellsAlongLine003E2620( const ICoord2D &start,
	const ICoord2D &end, PathfindLayerEnum layer, Rva003E2620GroundCellsStruct *info )
{
	Int delta_x = abs( end.x - start.x );
	Int delta_y = abs( end.y - start.y );

	Int xinc2, yinc1, xinc1, numpixels, numadd, den;
	Int yinc2, num;
	if (delta_x >= delta_y)
	{
		numpixels = delta_x + 1;
		num = 2 * delta_y - delta_x;
		numadd = delta_y << 1;
		den = 2 * (delta_y - delta_x);
		xinc2 = 1;
		yinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}
	else
	{
		numpixels = delta_y + 1;
		num = 2 * delta_x - delta_y;
		numadd = delta_x << 1;
		den = 2 * (delta_x - delta_y);
		yinc2 = 1;
		xinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}

	if (start.x > end.x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (start.y > end.y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	Int x = start.x;
	Int y = start.y;
	PathfindCell *from = 0;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *to = getCell( layer, x, y );
		if (to == 0)
			return 0;

		if (from)
		{
			if (to->getOpen() || to->getClosed())
				return 1;

			if (info->thePathfinder->clearCellForDiameter( 0, x, y, to->getLayer(),
				info->pathDiameter, 1 ) != info->pathDiameter)
				return 1;

			ICoord2D newCellCoord;
			newCellCoord.x = x;
			newCellCoord.y = y;
			if (to->m_info == 0)
			{
				if (g_bfmePathfindFreeList == 0)
					PathfindCellInfo::allocateCellInfos();
				to->m_info = bfmeAcquirePathfindCellInfo( &g_bfmePathfindFreeList, to, &newCellCoord );
			}
			else
			{
				to->m_info->m_prevOpen = 0;
			}
			to->m_info->m_flags &= ~1u;

			Int costRemaining = info->thePathfinder->rva003db900( to, info->goalCell );
			to->m_info->m_costSoFar = from->m_info->m_costSoFar + (((to->m_packed >> 24) & 1) ? 2 : 5);
			to->setParentCellHierarchical( from );
			to->m_info->m_totalCost = to->m_info->m_costSoFar + costRemaining;

			Int bucket = to->m_info->m_totalCost >> 7;
			Pathfinder *pathfinder = info->thePathfinder;
			((BfmeThingBRE *)to)->bfmeGoBRE( &pathfinder->m_bucketHeads034[bucket] );
			if (bucket < pathfinder->m_lowestBucket834)
				pathfinder->m_lowestBucket834 = bucket;
		}
		from = to;

		if (num < 0)
		{
			num += numadd;
			x += xinc2;
			y += yinc2;
		}
		else
		{
			num += den;
			x += xinc1;
			y += yinc1;
		}
	}

	return 0;
}
