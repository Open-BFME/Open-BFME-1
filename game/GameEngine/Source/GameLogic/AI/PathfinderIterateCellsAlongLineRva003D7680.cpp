// cl: /DNDEBUG /MD
//
// Retail 0x003D7680, 666 bytes: the cell-space Pathfinder::iterateCellsAlongLine
// instance reached through ILT 0x00048419 from its world-space forwarder and from
// Pathfinder::tightenLine (PathfindE1fe0.cpp). The shared Bresenham walk of
// PathfinderIterateCellsAlongLineCallbacks.cpp with its callback inlined: cell
// types 2, 4 and 5, flag bit 21, or (on the ground layer) a layer field inside
// 0x11..0x40 stop the walk; every other cell records its layer and its
// cell-size-scaled position in the user data.

extern "C" int __cdecl abs(int n);
#pragma intrinsic(abs)

typedef int Int;
typedef bool Bool;
typedef float Real;

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

	Bool getFlagBit21() const { return ((m_packed >> 21) & 1) != 0; }

};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int cellX, Int cellY);

private:
	char m_unreconstructed[0x44];
};

class Pathfinder;

struct Coord3D
{
	Real x, y, z;
};

struct Rva003D7680Struct
{
	Pathfinder *m_pathfinder;
	Coord3D *m_pos;
	Int m_layer;
};

class Pathfinder
{
public:
	Int iterateCellsAlongLine(const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003D7680Struct *callbackData);

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

	__forceinline PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY)
	{
		if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
			cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell(cellX, cellY);
				if (cell)
					return cell;
			}
			return &m_map[cellX][cellY];
		}
		return 0;
	}
};

Int Pathfinder::iterateCellsAlongLine(const ICoord2D &startCell,
	const ICoord2D &destinationCell, PathfindLayerEnum layer,
	Rva003D7680Struct *callbackData)
{
	Int delta_x = abs( destinationCell.x - startCell.x );
	Int delta_y = abs( destinationCell.y - startCell.y );

	Int xinc2, yinc1, xinc1, numpixels, numadd, den;
	Int yinc2, num;
	if (delta_x >= delta_y)
	{
		numpixels = delta_x + 1;
		num = 2 * delta_y - delta_x;
		numadd = delta_y << 1;
		den = 2 * (delta_y - delta_x);
		yinc1 = 1;
		xinc1 = 1;
		xinc2 = 1;
		yinc2 = 0;
	}
	else
	{
		numpixels = delta_y + 1;
		num = 2 * delta_x - delta_y;
		numadd = delta_x << 1;
		den = 2 * (delta_x - delta_y);
		yinc1 = 1;
		yinc2 = 1;
		xinc1 = 1;
		xinc2 = 0;
	}

	if (startCell.x > destinationCell.x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (startCell.y > destinationCell.y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	Int x = startCell.x;
	Int y = startCell.y;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *currentCell = getCell( layer, x, y );
		if (currentCell == 0)
			return 0;

		unsigned int flags = currentCell->m_packed;
		Int type = flags & 7;
		if (type == 5 || type == 2 || type == 4)
			return 1;
		if (currentCell->getFlagBit21())
			return 1;
		if (callbackData->m_layer == 1)
		{
			Int cellLayer = (flags >> 6) & 0x3f;
			if (cellLayer >= 0x11 && cellLayer <= 0x40)
				return 1;
		}
		callbackData->m_layer = (flags >> 6) & 0x3f;
		callbackData->m_pos->x = (Real)(x * 10);
		callbackData->m_pos->y = (Real)(y * 10);

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
