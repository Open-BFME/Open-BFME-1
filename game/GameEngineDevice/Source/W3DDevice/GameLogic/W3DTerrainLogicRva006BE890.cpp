// ?rva006BE890@W3DTerrainLogic@@UBE_NPBUCoord2D@@@Z
// BFME retail 0x006BE890 (239 bytes).
//
// The body is the last slot (47) of the 48-entry W3DTerrainLogic primary
// table at 0x0111D090.  Its public source name is not present in the shipped
// references, so the method keeps a truthful RVA-derived identity.  It
// translates a world Coord2D into the terrain bit plane after applying the
// virtual map-origin offset and clamping to the map dimensions.

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord2D
{
	Real x;
	Real y;
};

class Rva006BE630
{
public:
	Bool bfmeBitA(Int x, Int y) const;
};

class BfmeA1087
{
private:
	unsigned char m_bfmeHead[0x2ff4];

public:
	Rva006BE630 *m_bfmeTerrainMap;
};

extern BfmeA1087 *g_bfmeA1087;
extern const Real BfmeZeroRange;
extern const Real g_bfmeDirectionWeight1285;
extern const Real g_bfmeScaleBK;
extern "C" __declspec(dllimport) double __cdecl floor(double value);

// Retail converts each floored Real with WWMath::Float_To_Long.  The
// shipped helper uses x87 round-to-integer semantics, which is distinct from
// the compiler's normal floating-to-integer lowering on this path.
static inline Int bfmeFloatToLong(Real value)
{
	Int result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

// MSVC 7.1 lowers a plain C++ multiply differently here (216B versus
// retail 239B). This minimal x87 load/multiply preserves the proven order.
static inline Real bfmeScaleXForIndex(Real value)
{
	__asm {
		fld [value]
		fmul dword ptr [g_bfmeScaleBK]
	}
}

// Only declarations are needed for the virtual calls.  Keeping the slice
// abstract prevents this TU from emitting a replacement vtable.
#define BFME_UNUSED16(prefix) \
	virtual void prefix##00() const = 0; virtual void prefix##04() const = 0; \
	virtual void prefix##08() const = 0; virtual void prefix##0c() const = 0; \
	virtual void prefix##10() const = 0; virtual void prefix##14() const = 0; \
	virtual void prefix##18() const = 0; virtual void prefix##1c() const = 0; \
	virtual void prefix##20() const = 0; virtual void prefix##24() const = 0; \
	virtual void prefix##28() const = 0; virtual void prefix##2c() const = 0; \
	virtual void prefix##30() const = 0; virtual void prefix##34() const = 0; \
	virtual void prefix##38() const = 0; virtual void prefix##3c() const = 0

class W3DTerrainLogic
{
public:
	virtual void unused00() const = 0;
	virtual void unused04() const = 0;
	virtual void unused08() const = 0;
	virtual void unused0c() const = 0;
	virtual void unused10() const = 0;
	virtual void unused14() const = 0;
	virtual void unused18() const = 0;
	virtual void unused1c() const = 0;
	virtual void unused20() const = 0;
	virtual void unused24() const = 0;
	virtual void unused28() const = 0;
	virtual Real getMapOrigin() const = 0; // retail slot 11 (+0x2c)
	BFME_UNUSED16(unused040_);
	BFME_UNUSED16(unused080_);
	virtual void unused0c000() const = 0;
	virtual void unused0c004() const = 0;
	virtual void unused0c008() const = 0;

	virtual Bool rva006BE890(const Coord2D *point) const;

private:
	unsigned char m_bfmeHead[0x0c];
	Int m_mapDX;
	Int m_mapDY;
};

Bool W3DTerrainLogic::rva006BE890(const Coord2D *point) const
{
	Real origin = getMapOrigin();
	Real x = origin + point->x;
	Real y = origin + point->y;

	if (x < BfmeZeroRange)
		x = 0.0f;
	else if (x > (Real)m_mapDX * g_bfmeDirectionWeight1285)
		x = (Real)m_mapDX * g_bfmeDirectionWeight1285;

	if (y < BfmeZeroRange)
		y = BfmeZeroRange;
	else if (y > (Real)m_mapDY * g_bfmeDirectionWeight1285)
		y = (Real)m_mapDY * g_bfmeDirectionWeight1285;

	y *= g_bfmeScaleBK;
	Int yIndex = bfmeFloatToLong((Real)floor((double)y));
	x = bfmeScaleXForIndex(x);
	Int xIndex = bfmeFloatToLong((Real)floor((double)x));

	return g_bfmeA1087->m_bfmeTerrainMap->bfmeBitA(xIndex, yIndex);
}
