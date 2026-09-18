// ?iterateCellsAlongLine@Pathfinder@@QAEHABUICoord2D@@0W4PathfindLayerEnum@@PAVRva003E5A50Info@@@Z
// partial score=0.85 date=2026-09-18
// cl: /DNDEBUG /MD
//
// Retail 0x003E8440: the cell-space line walk used by Pathfinder::lineClear.
// The shared ILT at 0x0001DAA2 and the lineClear caller identify this overload.

extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)

extern void j_0001b5b8( void );

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
	char m_unreconstructed[0x0c];
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	char m_unreconstructed[0x44];
};

class Rva003E5A50Info
{
public:
	Int cellCallback( PathfindCell *from, PathfindCell *to, Int x, Int y );

	unsigned char m_body[0x54];
};
#pragma comment(linker, "/alternatename:?cellCallback@Rva003E5A50Info@@QAEHPAVPathfindCell@@0HH@Z=?j_0001b5b8@@YAXXZ")

class Pathfinder
{
public:
	Int iterateCellsAlongLine( const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E5A50Info *userData );

private:
	__forceinline PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y );

	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeLayers[0x85c - 0x24];
	PathfindLayer m_layers[16];

};

__forceinline PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer,
	Int x, Int y )
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

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &start,
	const ICoord2D &end, PathfindLayerEnum layer,
	Rva003E5A50Info *userData )
{
	const ICoord2D *start_ptr = &start;
	const ICoord2D *end_ptr = &end;
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
	PathfindCell *to;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		to = getCell( layer, x, y );
		if (to == 0)
			return 0;

		Int ret = userData->cellCallback( from, to, x, y );
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
