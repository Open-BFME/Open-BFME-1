// ?d_003e2620@@YAXXZ
// partial score=0.98 date=2026-09-17
// cl: /DNDEBUG /MD
//
// Retail 0x003E2620.  The findGroundPath caller and its ILT prove this as the
// BFME ground-cell line walk.  The retail body keeps the address-derived name
// because the binary exposes no semantic symbol for this overload.

typedef int Int;

extern "C" int __cdecl abs(int value);
#pragma intrinsic(abs)

struct ICoord2D
{
	Int x;
	Int y;
};

class PathfindCell;

class PathfindCellInfo
{
public:
	static void allocateCellInfos(void);

	Int m_posX;
	Int m_posY;
	PathfindCellInfo *m_nextOpen;
	PathfindCellInfo *m_prevOpen;
	unsigned short m_totalCost;
	unsigned short m_costSoFar;
	unsigned char m_pad14[0x10];
	unsigned int m_flags;
};

extern PathfindCellInfo *g_bfmePathfindFreeList;

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *pos);

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);
};

class PathfindCell
{
public:
	PathfindCellInfo *m_info;
	unsigned char m_pad04[8];
	unsigned int m_flags;

	void setParentCellHierarchical(PathfindCell *parent);
};

class BfmeThingBRE
{
public:
	void bfmeGoBRE(void *what);
};

struct Rva003E2620Info
{
	class Pathfinder *m_pathfinder;
	Int m_unused;
	PathfindCell *m_goalCell;
	Int m_diameter;
};

class Pathfinder
{
public:
	Int rva003e2620GroundCellsWalk(const ICoord2D &start,
		const ICoord2D &end, Int layer, Rva003E2620Info *info);
	Int rva003db900(PathfindCell *cell, PathfindCell *goal);

	Int clearCellForDiameter(Int crusher, Int cellX, Int cellY, Int layer,
		Int diameter, Int attackerOnWall);

private:
	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeSlots[0x810];
	Int m_watermark;
	char m_beforeLayers[0x18];
	PathfindLayer m_layers[16];

	__forceinline PathfindCell *getCell(Int cellX, Int cellY, Int cellLayer)
	{
		if (cellX < m_extent.lo.x || cellX > m_extent.hi.x ||
			cellY < m_extent.lo.y || cellY > m_extent.hi.y)
			return 0;

		if (cellLayer > 1 && cellLayer <= 15)
		{
			PathfindCell *cell = m_layers[cellLayer].getCell(cellX, cellY);
			if (cell)
				return cell;
		}

		return (PathfindCell *)((char *)m_map[cellX] + cellY * 16);
	}
};

// The dump-backed callee has no recovered signature.  The call site proves
// this Pathfinder receiver and its two PathfindCell arguments.
#pragma comment(linker, "/alternatename:?rva003db900@Pathfinder@@QAEHPAVPathfindCell@@0@Z=?d_003db900@@YAXXZ")

Int Pathfinder::rva003e2620GroundCellsWalk(const ICoord2D &start,
	const ICoord2D &end, Int layer, Rva003E2620Info *info)
{
	const ICoord2D *endPtr = &end;
	const ICoord2D *startPtr = &start;
	Int endX = endPtr->x;
	Int x = startPtr->x;
	Int deltaX = abs(endX - x);
	Int y = startPtr->y;
	Int endY = endPtr->y;
	Int deltaY = abs(endY - y);

	Int xIncrement2;
	Int yIncrement1;
	Int xIncrement1;
	Int numPixels;
	Int numAdd;
	Int denominator;
	Int yIncrement2;
	Int numerator;

	if (deltaX >= deltaY)
	{
		numPixels = deltaX + 1;
		numerator = 2 * deltaY - deltaX;
		numAdd = 2 * deltaY;
		denominator = 2 * (deltaY - deltaX);
		xIncrement2 = 1;
		yIncrement2 = 0;
		yIncrement1 = 1;
		xIncrement1 = 1;
	}
	else
	{
		numPixels = deltaY + 1;
		numerator = 2 * deltaX - deltaY;
		numAdd = 2 * deltaX;
		denominator = 2 * (deltaX - deltaY);
		yIncrement2 = 1;
		xIncrement2 = 0;
		yIncrement1 = 1;
		xIncrement1 = 1;
	}

	if (startPtr->x > endX)
	{
		xIncrement2 = -xIncrement2;
		xIncrement1 = -1;
	}
	if (startPtr->y > endY)
	{
		yIncrement2 = -yIncrement2;
		yIncrement1 = -1;
	}

	PathfindCell *from = 0;
	for (Int currentPixel = 0; currentPixel < numPixels; ++currentPixel)
	{
		PathfindCell *cell = getCell(x, y, layer);
		if (!cell)
			return 0;

		if (from)
		{
			PathfindCellInfo *cellInfo = cell->m_info;
			if (cellInfo)
			{
				if (((cellInfo->m_flags >> 3) & 1) != 0 ||
					((cellInfo->m_flags >> 4) & 1) != 0)
					return 1;
			}

			Int cellLayer = (cell->m_flags >> 6) & 0x3f;
			if (clearCellForDiameter(0, x, y, cellLayer,
				info->m_diameter, 1) != info->m_diameter)
				return 1;

			if (!cellInfo)
			{
				ICoord2D pos;
				pos.x = x;
				pos.y = y;
				if (!g_bfmePathfindFreeList)
					PathfindCellInfo::allocateCellInfos();
				cell->m_info = bfmeAcquirePathfindCellInfo(
					&g_bfmePathfindFreeList, cell, &pos);
				cellInfo = cell->m_info;
			}

			cellInfo->m_prevOpen = 0;
			cellInfo->m_flags &= ~1u;
			Int remainingCost = info->m_pathfinder->rva003db900(
				cell, info->m_goalCell);

			Int stepCost = (cell->m_flags & 1) ? 2 : 5;
			cellInfo->m_costSoFar = from->m_info->m_costSoFar + stepCost;
			cell->setParentCellHierarchical(from);
			cellInfo->m_totalCost = cellInfo->m_costSoFar + remainingCost;

			Int bucket = cellInfo->m_totalCost >> 7;
			((BfmeThingBRE *)cell)->bfmeGoBRE(
				(char *)info->m_pathfinder + 0x34 + bucket * 4);
			if (bucket < info->m_pathfinder->m_watermark)
				info->m_pathfinder->m_watermark = bucket;
		}

		from = cell;
		if (numerator < 0)
		{
			numerator += numAdd;
			x += xIncrement2;
			y += yIncrement2;
		}
		else
		{
			numerator += denominator;
			x += xIncrement1;
			y += yIncrement1;
		}
	}

	return 0;
}
