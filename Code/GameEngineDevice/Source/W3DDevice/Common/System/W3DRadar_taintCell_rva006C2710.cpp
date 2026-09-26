// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x006C2710, 626 bytes: W3DRadar vtable 0x0111D7B4 slot 11 (+0x2C),
// the vtable the matched W3DRadar constructor 0x006C1D70 and destructor
// 0x006C1780 install.  It is the taint counterpart of the radar's shroud
// setter in slot 9 (0x006C23B0, Zero Hour's W3DRadar::setShroudLevel shape on
// the terrain's W3DShroud at +0x30B8): the only caller, 0x001072F0, forwards
// (x, y, level) to W3DDisplay slot +0x118 (setShroudLevel30BC, 0x006EA700)
// and then here, exactly as 0x001072A0 pairs W3DDisplay::setShroudLevel
// (slot +0x10C) with radar slot 9.  This body reads the terrain's TaintBuffer
// (+0x30BC), gates on TaintOn and tints the cell from TaintColor below level
// 128 and ElvenWoodColor above it.  The method name is not known, so it keeps
// the address.

typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef Int Color;

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

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

// INI FieldParse table 0x00C77018 (reverse/field_names.csv): TaintColor +0xC88,
// ElvenWoodColor +0xC94, TaintOn +0xCF5.
class GlobalData
{
	unsigned char m_unmodelled_000[0xc88];

public:
	RGBColor m_taintColor;
	RGBColor m_elvenWoodColor;

private:
	unsigned char m_unmodelled_ca0[0xcf5 - 0xca0];

public:
	UnsignedByte m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

// The two floats scale a cell index to world units; retail reads each through
// a by-value accessor (the fld / fmul st(1) / fstp st(0) shape).
class TaintBuffer
{
	unsigned char m_unmodelled_00[0x10];
	Real m_real10;
	Real m_real14;

public:
	Real getReal10() const { return m_real10; }
	Real getReal14() const { return m_real14; }
};

// reverse/identity_evidence/0071a0d0.md: the TaintBuffer lives at +0x30BC.
class BaseHeightMapRenderObjClass
{
	unsigned char m_unmodelled_00[0x30bc];
	TaintBuffer *m_taintBuffer;

public:
	TaintBuffer *getTaintBuffer() const { return m_taintBuffer; }
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);

// Unwind state 0 releases this scope lock; retail inlines both halves.
class Rva006C2710Lock
{
public:
	Rva006C2710Lock() { W3DRadarResetLock(); }
	~Rva006C2710Lock() { bfmeUnlock1179(); }
};

class SurfaceClass
{
public:
	void DrawPixel(const unsigned int x, const unsigned int y, unsigned int color);
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel(void);

	void *m_texture;
};

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | (blue);
}

inline bool legalRadarPoint(Int px, Int py)
{
	if (px < 0 || py < 0 || px >= 128 || py >= 128)
		return false;

	return true;
}

class Radar
{
public:
	virtual ~Radar();

	bool worldToRadar(const Coord3D *world, ICoord2D *radar);
};

class W3DRadar : public Radar
{
public:
	virtual void rva006C2710(Int cellX, Int cellY, UnsignedByte level);

private:
	unsigned char m_unmodelled_004[0x14a0 - 4];
	W3DRadarResetTexture m_texture14a0;
};

// ?rva006C2710@W3DRadar@@UAEXHHE@Z
void W3DRadar::rva006C2710(Int cellX, Int cellY, UnsignedByte level)
{
	if (!TheWritableGlobalData->m_taintOn)
		return;

	TaintBuffer *taint = TheTerrainRenderObject ? TheTerrainRenderObject->getTaintBuffer() : 0;
	if (!taint)
		return;

	Rva006C2710Lock lock;
	W3DRadarResetSurface surface = m_texture14a0.getSurfaceLevel();

	Int mapMinX = cellX * taint->getReal10();
	Int mapMinY = cellY * taint->getReal14();
	Int mapMaxX = (cellX + 1) * taint->getReal10();
	Int mapMaxY = (cellY + 1) * taint->getReal14();

	ICoord2D radarPoint;
	Coord3D worldPoint;

	worldPoint.x = mapMinX;
	worldPoint.y = mapMinY;
	worldToRadar(&worldPoint, &radarPoint);
	Int radarMinX = radarPoint.x;
	Int radarMinY = radarPoint.y;

	worldPoint.x = mapMaxX;
	worldPoint.y = mapMaxY;
	worldToRadar(&worldPoint, &radarPoint);
	Int radarMaxX = radarPoint.x;
	Int radarMaxY = radarPoint.y;

	Int alpha;
	Int red;
	Int green;
	Int blue;
	if (level < 128)
	{
		alpha = (127 - level) * 2;
		red = alpha * TheWritableGlobalData->m_taintColor.red;
		green = alpha * TheWritableGlobalData->m_taintColor.green;
		blue = alpha * TheWritableGlobalData->m_taintColor.blue;
	}
	else if (level > 128)
	{
		alpha = level * 2 - 256;
		red = alpha * TheWritableGlobalData->m_elvenWoodColor.red;
		green = alpha * TheWritableGlobalData->m_elvenWoodColor.green;
		blue = alpha * TheWritableGlobalData->m_elvenWoodColor.blue;
	}
	else
	{
		alpha = 0;
		red = 255;
		green = 255;
		blue = 255;
	}

	for (Int y = radarMinY; y <= radarMaxY; y++)
	{
		for (Int x = radarMinX; x <= radarMaxX; x++)
		{
			if (legalRadarPoint(x, y))
				((SurfaceClass *)&surface)->DrawPixel(x, y, GameMakeColor(red, green, blue, alpha));
		}
	}
}
