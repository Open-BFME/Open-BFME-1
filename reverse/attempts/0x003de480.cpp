// ?d_003de480@@YAXXZ
// partial score=0.94 date=2026-09-18
// cl: /DNDEBUG /MD /EHs-c- /Ireference/shims/pathfind
// Retail 0x003DE480 is Pathfinder's cell-space Bresenham walk for snapLine.
// The two callers and ILT 0x00005713 identify the Rva003DE480Struct overload.

typedef int Int;
typedef bool Bool;

#include <stdlib.h>

struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class PathfindCell
{
	unsigned char m_body[0x10];
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);

private:
	unsigned char m_body[0x44];
};

class Pathfinder;

class Rva003D61C0
{
public:
	Int cellCallback(PathfindCell *from, PathfindCell *to, Int to_x,
		Int to_y);

	Pathfinder *m_pathfinder;
	Int m_diameter;
	float m_last_x;
	float m_last_y;
	float m_last_z;
};

struct Rva003DE480Struct : Rva003D61C0
{
};

class Pathfinder
{
public:
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003DE480Struct *userData);

	private:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);

	public:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	struct
		{
			ICoord2D lo;
			ICoord2D hi;
		} m_extent;
		unsigned char m_mid[0x85c - 0x24];
		PathfindLayer m_layers[16];
};

__forceinline PathfindCell *Pathfinder::getCell(PathfindLayerEnum layer,
	Int x, Int y)
{
	if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
		y >= m_extent.lo.y && y <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell(x, y);
			if (cell)
				return cell;
		}
		return &m_map[x][y];
	}
	return 0;
}

Int Pathfinder::iterateCellsAlongLine(const ICoord2D &start,
	const ICoord2D &end, PathfindLayerEnum layer,
	Rva003DE480Struct *userData)
{
	const ICoord2D *start_ptr = &start;
	const ICoord2D *end_ptr = &end;
	Int end_x = end_ptr->x;
	Int x = start_ptr->x;
	Int delta_x = abs(end_x - x);
	Int y = start_ptr->y;
	Int end_y = end_ptr->y;
	Int delta_y = abs(end_y - y);

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
		PathfindCell *to = getCell(layer, x, y);
		if (to == 0)
			return 0;

		Int ret = userData->cellCallback(from, to, x, y);
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
