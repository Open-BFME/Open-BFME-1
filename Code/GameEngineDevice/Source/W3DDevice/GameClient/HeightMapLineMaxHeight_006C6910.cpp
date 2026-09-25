// cl: /DNDEBUG /MD /EHsc
// Retail 0x006C6910: walk a Bresenham line between two points over the
// terrain height samples and return the highest cell corner crossed.
// The owner keeps its height map at +0x2FF4 (the BaseHeightMap m_map slot
// isClearLineOfSight and getMaxCellHeight use); the only caller is the
// global-object forwarder bfmeGoUDB at 0x006BE230, so the method name keeps
// the address token.

#include <math.h>
#include <stdlib.h>

typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

struct Coord3D { Real x, y, z; };

// BFME's REAL_TO_INT_FLOOR: CRT floor() then the engine's x87 round.
__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))
#define __max(a,b) (((a) > (b)) ? (a) : (b))

class HeightSamples006C6910
{
public:
	unsigned char m_pad00[0x08];
	Int m_xExtent;
	Int m_yExtent;
	Int m_borderSize;
	unsigned char m_pad14[0x10];
	UnsignedShort *m_data;
};

class HeightMapOwner006C6910
{
public:
	Real maxHeightAlongLine(const Coord3D *pos, const Coord3D *posOther) const;

private:
	unsigned char m_pad00[0x2ff4];
	HeightSamples006C6910 *m_map;
};

Real HeightMapOwner006C6910::maxHeightAlongLine(const Coord3D *pos, const Coord3D *posOther) const
{
	if (m_map == 0)
		return 0.0f;

	const Real MAP_XY_FACTOR_INV = 0.1f;
	Int borderSize = m_map->m_borderSize;
	Real maxHeight = 0.0f;
	Int start_x = REAL_TO_INT_FLOOR(pos->x * MAP_XY_FACTOR_INV) + borderSize;
	Int start_y = REAL_TO_INT_FLOOR(pos->y * MAP_XY_FACTOR_INV) + borderSize;
	Int end_x = REAL_TO_INT_FLOOR(posOther->x * MAP_XY_FACTOR_INV) + borderSize;
	Int end_y = REAL_TO_INT_FLOOR(posOther->y * MAP_XY_FACTOR_INV) + borderSize;
	Int delta_x = abs(end_x - start_x);
	Int delta_y = abs(end_y - start_y);
	Int x = start_x;
	Int y = start_y;

	Int xinc1, xinc2;
	if (end_x >= start_x)
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	Int yinc1, yinc2;
	if (end_y >= start_y)
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	Int den, num, numadd, numpixels;
	if (delta_x >= delta_y)
	{
		xinc1 = 0;
		yinc2 = 0;
		den = delta_x;
		num = delta_x / 2;
		numadd = delta_y;
		numpixels = delta_x;
	}
	else
	{
		xinc2 = 0;
		yinc1 = 0;
		den = delta_y;
		num = delta_y / 2;
		numadd = delta_x;
		numpixels = delta_y;
	}

	const UnsignedShort *data = m_map->m_data;
	Int xExtent = m_map->m_xExtent;
	Int yExtent = m_map->m_yExtent;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		if (x < 0 ||
				y < 0 ||
				x >= xExtent-1 ||
				y >= yExtent-1)
		{
			break;
		}

		Int idx = x + y*xExtent;
		float height = data[idx];
		height = __max(height, data[idx + 1]);
		height = __max(height, data[idx + xExtent]);
		height = __max(height, data[idx + xExtent + 1]);
		height *= 0.0390625f;

		if (height > maxHeight)
			maxHeight = height;

		num += numadd;
		if (num >= den)
		{
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}

	return maxHeight;
}
