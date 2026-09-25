// cl: /DNDEBUG /MD
//
// Retail 0x003D7010: the packed-cell line walk used by a BFME Pathfinder
// overload.  The user-data pointer is part of the ABI but is not read by this
// body; the walk returns a hit when a cell is neither clear nor occupied, or
// when its bit-18 state is set.

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
	char m_unreconstructed[0x0c];
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	char m_unreconstructed[0x44];
};

struct Rva003D7010Struct;

class Pathfinder
{
public:
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003D7010Struct *unusedContext );

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

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell,
	const ICoord2D &destinationCell, PathfindLayerEnum layer,
	Rva003D7010Struct *unusedContext )
{
	const ICoord2D *start_ptr = &startCell;
	const ICoord2D *end_ptr = &destinationCell;
	Int end_x = end_ptr->x;
	Int x = start_ptr->x;
	Int delta_x = abs( end_x - x );
	Int y = start_ptr->y;
	Int end_y = end_ptr->y;
	Int delta_y = abs( end_y - y );

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

	if (startCell.x > end_x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (startCell.y > end_y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *cell = getCell( layer, x, y );
		if (cell == 0)
			return 0;

		unsigned int flags = cell->m_packed;
		if ((flags & 7) != 0 && (flags & 7) != 1)
			return 1;
		flags >>= 18;
		if (((unsigned char)flags & 1) != 0)
			return 1;

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
