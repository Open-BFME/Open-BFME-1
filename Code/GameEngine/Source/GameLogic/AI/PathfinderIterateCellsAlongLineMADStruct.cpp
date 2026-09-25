// cl: /DNDEBUG /MD
//
// Retail 0x003ED9F0, 478 bytes: the cell-space line walk used by
// Pathfinder::moveAlliesAwayFromDestination. The two byte-true callers name
// this private overload, and its callback is MADStruct::cellCallback at
// 0x003EC070. Same Bresenham shape as PathfinderGroundCellsAlongLineRva003E2620.cpp.

extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)

typedef int Int;

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
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	char m_unreconstructed[0x44];
};

struct MADStruct
{
	Int cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

class Pathfinder
{
private:
	Int iterateCellsAlongLine( const ICoord2D *startCell, const ICoord2D *destinationCell,
		PathfindLayerEnum layer, MADStruct *callbackInfo );

	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeLayers[0x85c - 0x24];
	PathfindLayer m_layers[16];

	__forceinline PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY )
	{
		if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
			cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell( cellX, cellY );
				if (cell)
					return cell;
			}
			return &m_map[cellX][cellY];
		}
		return 0;
	}
};

Int Pathfinder::iterateCellsAlongLine( const ICoord2D *startCell,
	const ICoord2D *destinationCell, PathfindLayerEnum layer,
	MADStruct *callbackInfo )
{
	Int delta_x = abs( destinationCell->x - startCell->x );
	Int delta_y = abs( destinationCell->y - startCell->y );

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

	if (startCell->x > destinationCell->x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (startCell->y > destinationCell->y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	Int x = startCell->x;
	Int y = startCell->y;
	PathfindCell *from = 0;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *to = getCell( layer, x, y );
		if (to == 0)
			return 0;

		Int ret = callbackInfo->cellCallback( from, to, x, y );
		if (ret != 0)
			return ret;
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
