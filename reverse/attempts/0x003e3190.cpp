// ?iterateCellsAlongLine@Pathfinder@@QAEHABUICoord2D@@0W4PathfindLayerEnum@@PAUViewAttackBlockedStruct@@@Z
// partial score=0.93 date=2026-09-09
// cl: /DNDEBUG /MD
//
// Retail 0x003E3190: the cell-space Bresenham line walk that
// Pathfinder::iterateCellsAlongLine(world-space, ViewAttackBlockedStruct*)
// (0x003E7E60) forwards to.  Same doubled-error Bresenham setup already
// proven at 0x003D7010 (PathfinderIterateCellsAlongLineRva003D7010.cpp), but
// the per-cell test is a callback through the user-data pointer rather than
// an inline flag test: userData->process(from, to, x, y), stopping the walk
// as soon as it returns non-zero.

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

class PathfindCell
{
public:
	char m_unreconstructed[0x10];
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	char m_unreconstructed[0x44];
};

struct ViewAttackBlockedStruct
{
	Int process( PathfindCell *from, PathfindCell *to, Int x, Int y );
};

class Pathfinder
{
public:
	Int iterateCellsAlongLine( const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, ViewAttackBlockedStruct *userData );

private:
	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeLayers[0x85c - 0x24];
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

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &start,
	const ICoord2D &end, PathfindLayerEnum layer,
	ViewAttackBlockedStruct *userData )
{
	const ICoord2D *start_ptr = &start;
	const ICoord2D *end_ptr = &end;
	Int end_x = end_ptr->x;
	Int x = start_ptr->x;
	Int delta_x = abs( end_x - x );
	Int y = start_ptr->y;
	Int end_y = end_ptr->y;
	Int delta_y = abs( end_y - y );

	Int numpixels, num, numadd, den;
	Int xinc1, xinc2, yinc1, yinc2;
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

	if (start.x > end_x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (start.y > end_y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	PathfindCell *from = 0;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *to = getCell( layer, x, y );
		if (to == 0)
			return 0;

		Int ret = userData->process( from, to, x, y );
		if (ret != 0)
			return ret;

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
		from = to;
	}

	return 0;
}
