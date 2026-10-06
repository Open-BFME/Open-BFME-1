// cl: /DNDEBUG /MD /EHsc
// Retail 0x0074B480 (1179 bytes, RET 0Ch): write a circular footprint into
// the WorldHeightMap byte-packed bit plane at +0x50, then notify the terrain
// render object of the touched cell region.
//
// Receiver: both callers load it from TheTerrainRenderObject (0x012F7FE0)
// +0x2FF4, the render object's map pointer -- the matched W3DModelDraw
// destructor (0x0077B1CE, via ILT 0x0001B572, value 1) and 0x00763620 (twice,
// old/new position with value 1/0).  They pass a Coord3D pointer, a Real
// radius and a Bool.  Width/height/border at +0x08/+0x0C/+0x10 are the
// WorldHeightMap fields TaintBufferInit.cpp uses (m_width witnessed).  The row
// stride at +0x34 and the bit-plane vector at +0x50 have no witness, so they
// keep offset names.  No caller or symbol names the method, so it keeps the
// address token; so does the terrain-object slot it calls (vtable slot 137,
// +0x224, which the HeightMapRenderObjClass vtable 0x0111DC88 routes to the
// anonymous body 0x006D1D80 through ILT 0x0002E087).
//
// Shape notes: the centre is a Coord3D with z never written (retail's frame
// holds its third slot at esp+0x34); the per-cell bit write is an inline
// setter with the same bounds tests as the matched getters in
// BfmeBitPlaneQueries.cpp.

#include <math.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

// Retail calls the CRT floor()/ceil() through the import table here.
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))
#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)ceil((double)(x))))

struct BitPlaneBytes0074B480
{
	UnsignedByte *m_begin;
	UnsignedByte *m_end;
	UnsignedByte *m_capacity;

	UnsignedInt size() const { return (UnsignedInt)(m_end - m_begin); }
	UnsignedByte &operator[](Int index) { return m_begin[index]; }
};

class WorldHeightMap;

template <int N>
class TerrainSlots0074B480 : public TerrainSlots0074B480<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class TerrainSlots0074B480<0>
{
};

// The terrain render object as this body sees it: only slot 137 is called.
class Rva0074B480TerrainAbi : public TerrainSlots0074B480<137>
{
public:
	virtual void rva006D1D80(IRegion2D *region, WorldHeightMap *map, Int mode) = 0;
};

// BaseHeightMap.cpp owns the pointer (data_rows.csv, VA 012F7FE0).
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class WorldHeightMap
{
public:
	void rva0074B480(const Coord3D *pos, Real radius, Bool value);

private:
	void setPlane50Bit(Int x, Int y, Bool value)
	{
		if (x < 0 || y < 0 || y >= m_height || x >= m_width)
			return;
		Int index = m_stride34 * y + (x >> 3);
		if ((UnsignedInt)index >= m_plane50.size())
			return;
		UnsignedByte &cell = m_plane50[index];
		if (value)
			cell |= (1 << (x & 7));
		else
			cell &= ~(1 << (x & 7));
	}

	void *m_vftable;
	Int m_numRefs;
	Int m_width;			// +0x08
	Int m_height;			// +0x0C
	Int m_borderSize;		// +0x10
	char m_pad14[0x20];
	Int m_stride34;			// +0x34
	char m_pad38[0x18];
	BitPlaneBytes0074B480 m_plane50;	// +0x50
};

void WorldHeightMap::rva0074B480(const Coord3D *pos, Real radius, Bool value)
{
	Int minX = REAL_TO_INT_FLOOR((pos->x - radius) * 0.1f) + m_borderSize;
	Int minY = REAL_TO_INT_FLOOR((pos->y - radius) * 0.1f) + m_borderSize;
	if (minX < 0)
		minX = 0;
	if (minY < 0)
		minY = 0;
	Int maxX = REAL_TO_INT_CEIL((pos->x + radius) * 0.1f) + m_borderSize;
	Int maxY = REAL_TO_INT_CEIL((pos->y + radius) * 0.1f) + m_borderSize;
	if (maxX > m_width)
		maxX = m_width;
	if (maxY > m_height)
		maxY = m_height;

	radius *= radius;
	Coord3D center;
	center.x = pos->x;
	center.y = pos->y;
	center.x += m_borderSize * 10.0f;
	center.y += m_borderSize * 10.0f;

	for (Int x = minX; x < maxX; ++x)
	{
		for (Int y = minY; y < maxY; ++y)
		{
			Real dx = ((Real)x + 0.5f) * 10.0f - center.x;
			Real dy = ((Real)y + 0.5f) * 10.0f - center.y;
			if (dx * dx + dy * dy < radius)
				setPlane50Bit(x, y, value);
		}
	}

	IRegion2D region;
	region.lo.x = minX;
	region.lo.y = minY;
	region.hi.x = maxX;
	region.hi.y = maxY;
	if (TheTerrainRenderObject != 0)
		reinterpret_cast<Rva0074B480TerrainAbi *>(TheTerrainRenderObject)
			->rva006D1D80(&region, this, 0);
}
