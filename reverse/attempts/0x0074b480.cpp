// ?rva0074B480@Rva0074B480WorldHeightMap@@QAEXPBUCoord3D@@M_N@Z
// partial score=0.48 date=2026-09-18
// ?rva0074B480@Rva0074B480WorldHeightMap@@QAEXPBUCoord3D@@M_N@Z
// Retail 0x0074B480, 1179 bytes.  The receiver is proven to be the map
// returned by TheTerrainRenderObject->getMap(), but no canonical BFME method
// name is established by the callers or the vtable evidence.  Keep the owner
// and method address-derived until that identity is independently proven.
//
// The body rasterizes a circular footprint into the byte-packed bit plane at
// +0x50.  The witnessed BFME map fields used here are width/height/border at
// +0x08/+0x0c/+0x10, row width at +0x34, and the bit-plane begin/end pair at
// +0x50/+0x54.

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

struct Rva0074B480Center
{
	Real x;
	Real y;
};

extern "C" __declspec(dllimport) double __cdecl BfmeFloorER(double value);
extern "C" __declspec(dllimport) double __cdecl bfmeMathVE(double value);

#define RVA0074B480_SCALE (*(const Real *)0x01075C70)
#define RVA0074B480_CELL_SIZE (*(const Real *)0x01075C74)
#define RVA0074B480_HALF_CELL (*(const Real *)0x0107533C)

static __forceinline Int rva0074B480FloatToInt(Real value)
{
	Int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

static __forceinline Int rva0074B480Floor(Real value)
{
	return rva0074B480FloatToInt((Real)BfmeFloorER((double)value));
}

static __forceinline Int rva0074B480Ceil(Real value)
{
	return rva0074B480FloatToInt((Real)bfmeMathVE((double)value));
}

class Rva0074B480WorldHeightMap
{
public:
	void rva0074B480(const Coord3D *position, Real radius, Bool value);

private:
	char m_padding00[0x08];
	Int m_width;
	Int m_height;
	Int m_borderSize;
	char m_padding14[0x20];
	Int m_flipStateWidth;
	char m_padding38[0x18];
	struct ByteVector
	{
		UnsignedByte *m_start;
		UnsignedByte *m_finish;
		UnsignedByte *m_endOfStorage;
	} m_bits;
};

struct Rva0074B480Bounds
{
	Int loX;
	Int loY;
	Int hiX;
	Int hiY;
};

template <int N>
class Rva0074B480CallbackSlots : public Rva0074B480CallbackSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva0074B480CallbackSlots<0>
{
};

class Rva0074B480Callback : public Rva0074B480CallbackSlots<137>
{
public:
	virtual void update(const Rva0074B480Bounds *bounds,
		Rva0074B480WorldHeightMap *map, Int mode) = 0;
};

#define Rva0074B480TheCallback (*(Rva0074B480Callback **)0x012F7FE0)

// ?rva0074B480@Rva0074B480WorldHeightMap@@QAEXPBUCoord3D@@M_N@Z
void Rva0074B480WorldHeightMap::rva0074B480(const Coord3D *position,
	Real radius, Bool value)
{
	const Coord3D *p = position;
	Int minX;
	Int minY;
	Int maxX;
	Int maxY;
	minX = rva0074B480Floor((p->x - radius) *
		RVA0074B480_SCALE) + m_borderSize;
	minY = rva0074B480Floor((p->y - radius) *
		RVA0074B480_SCALE) + m_borderSize;
	if (minX < 0)
		minX = 0;
	if (minY < 0)
		minY = 0;

	maxX = rva0074B480Ceil((p->x + radius) *
		RVA0074B480_SCALE) + m_borderSize;
	maxY = rva0074B480Ceil((p->y + radius) *
		RVA0074B480_SCALE) + m_borderSize;
	if (maxX > m_width)
		maxX = m_width;
	if (maxY > m_height)
		maxY = m_height;

	radius *= radius;
	Rva0074B480Center center = { p->x, p->y };
	center.x += (Real)m_borderSize * RVA0074B480_CELL_SIZE;
	center.y += (Real)m_borderSize * RVA0074B480_CELL_SIZE;

	for (Int x = minX; x < maxX; ++x)
	{
		for (Int y = minY; y < maxY; ++y)
		{
			Real dx = ((Real)x + RVA0074B480_HALF_CELL) *
				RVA0074B480_CELL_SIZE - center.x;
			Real dy = ((Real)y + RVA0074B480_HALF_CELL) *
				RVA0074B480_CELL_SIZE - center.y;
			if (dx * dx + dy * dy <= radius)
			{
				if (x >= 0 && y >= 0 && y < m_height && x < m_width)
				{
					Int byteIndex = m_flipStateWidth * y + (x >> 3);
					if ((UnsignedInt)byteIndex <
						(UnsignedInt)(m_bits.m_finish - m_bits.m_start))
					{
						UnsignedByte *cell = m_bits.m_start + byteIndex;
						UnsignedByte bit = (UnsignedByte)(1 << (x & 7));
						if (value)
							*cell |= bit;
						else
							*cell &= (UnsignedByte)~bit;
					}
				}
			}
		}
	}

	Rva0074B480Bounds bounds;
	bounds.loX = minX;
	bounds.loY = minY;
	bounds.hiX = maxX;
	bounds.hiY = maxY;

	if (Rva0074B480TheCallback != 0)
		Rva0074B480TheCallback->update(&bounds, this, 0);
}
