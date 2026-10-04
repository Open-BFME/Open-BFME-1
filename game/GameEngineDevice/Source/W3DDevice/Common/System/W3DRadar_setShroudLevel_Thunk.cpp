// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "W3DDevice/Common/W3DRadar.h"

// Retail 0x012F7FE0: BaseHeightMapRenderObjClass *TheTerrainRenderObject
// (W3DDevice/GameClient/BaseHeightMap.h). This lane only needs the shroud grid
// out of it, so the object stays opaque and the cast happens at the one use.
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

struct Rva006C23B0Grid
{
	unsigned char pad00[0x10];
	float cellWidth;
	float cellHeight;
	float getCellWidth() const { return cellWidth; }
	float getCellHeight() const { return cellHeight; }
};

struct BfmeA1087ShroudView
{
	unsigned char pad00[0x30b8];
	Rva006C23B0Grid *grid;
	Rva006C23B0Grid *getShroud() const { return grid; }
};

// Retail reaches both radar helpers through incremental-link thunks:
// ILT 0x26099 -> Radar::worldToRadar (0x106D20), ILT 0x827E -> the aspect
// helper (0x106F20). The calls are routed through the thunks directly.
extern void j_00026099();
extern void j_0000827e();

class Route012F7FE0 {};

class Rva00106F20Radar
{
private:
	struct Coord3D
	{
		float x;
		float y;
		float z;
	};

	struct Region3D
	{
		Coord3D lo;
		Coord3D hi;
	};

	unsigned char pad00[0x143c];
	Region3D mapExtent;
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

private:
	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel();

private:
	void *m_texture;
};

class BfmeThingGN
{
public:
	int bfmeAskGN();
};

class BfmeThingEF
{
public:
	int bfmeAskEF();
};

class SurfaceClass
{
public:
	void rva008FCF40(unsigned x, unsigned y, unsigned value);
};

extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);

class Rva006C23B0Lock
{
public:
	Rva006C23B0Lock() { W3DRadarResetLock(); }
	~Rva006C23B0Lock() { bfmeUnlock1179(); }
};

extern float g_bfmeUint32Scale;
extern float g_bfmeDefaultBU;
extern const float g_rva0107533C;

struct Rva006C23B0WorldPoint
{
	float x;
	float y;
	float z;
};

struct Rva006C23B0RadarPoint
{
	int x;
	int y;
};

static __forceinline void bfmeJ00026099(void *self, const Coord3D *world, ICoord2D *out)
{
	typedef bool (Route012F7FE0::*WorldToRadar)(const Coord3D *, ICoord2D *);
	union { void (*fn)(); WorldToRadar call; } toRadar = { j_00026099 };
	(((Route012F7FE0 *)self)->*toRadar.call)(world, out);
}

static __forceinline void bfmeJ0000827e(void *self, float *xRatio, float *yRatio)
{
	typedef int (Rva00106F20Radar::*ComputeAspect)(float *, float *) const;
	union { void (*fn)(); ComputeAspect call; } aspect = { j_0000827e };
	(((Rva00106F20Radar *)self)->*aspect.call)(xRatio, yRatio);
}

void W3DRadar::setShroudLevel(Int cellX, Int cellY, CellShroudStatus status)
{
	BfmeA1087ShroudView *terrain = (BfmeA1087ShroudView *)TheTerrainRenderObject;
	Rva006C23B0Grid *grid = terrain ? terrain->getShroud() : 0;
	if (grid == 0)
		return;

	Rva006C23B0Lock lock;

	W3DRadarResetSurface surface =
		((W3DRadarResetTexture *)((char *)this + 0x1494))->getSurfaceLevel();

	int mapMinX = (int)(cellX * grid->getCellWidth());
	int mapMinY = (int)(cellY * grid->getCellHeight());
	int mapMaxX = (int)((cellX + 1) * grid->getCellWidth());
	int mapMaxY = (int)((cellY + 1) * grid->getCellHeight());

	Rva006C23B0WorldPoint world;
	Rva006C23B0RadarPoint radar;
	Radar *radarThis = (Radar *)this;
	world.x = (float)mapMinX;
	world.y = (float)mapMinY;
	bfmeJ00026099(radarThis, (const Coord3D *)&world, (ICoord2D *)&radar);
	int radarMinX = radar.x;
	int radarMinY = radar.y;

	world.x = (float)mapMaxX;
	world.y = (float)mapMaxY;
	bfmeJ00026099(radarThis, (const Coord3D *)&world, (ICoord2D *)&radar);
	int radarMaxX = radar.x;
	int radarMaxY = radar.y;

	float xRatio;
	float yRatio;
	bfmeJ0000827e(this, &xRatio, &yRatio);

	if (xRatio > yRatio)
	{
		radarMinY = (int)(radarMinY * yRatio);
		radarMaxY = (int)(radarMaxY * yRatio);
		unsigned north = ((BfmeThingGN *)((char *)this + 0x1494))->bfmeAskGN();
		float northFactor = (float)north;
		float correction = northFactor *
			((g_bfmeDefaultBU - yRatio) * g_rva0107533C);
		radarMinY = (int)(radarMinY + correction);
		radarMaxY = (int)(radarMaxY + correction);
	}
	else
	{
		radarMinX = (int)(radarMinX * xRatio);
		radarMaxX = (int)(radarMaxX * xRatio);
		unsigned east = ((BfmeThingEF *)((char *)this + 0x1494))->bfmeAskEF();
		float eastFactor = (float)east;
		float correction = eastFactor *
			((g_bfmeDefaultBU - xRatio) * g_rva0107533C);
		radarMinX = (int)(radarMinX + correction);
		radarMaxX = (int)(radarMaxX + correction);
	}

	unsigned char &alpha = *(unsigned char *)&status;
	if (status == 2)
		alpha = 0xff;
	else if (status == 1)
		alpha = 0x7f;
	else
		alpha = 0;

	for (int y = radarMinY; y <= radarMaxY; ++y)
	{
		for (int x = radarMinX; x <= radarMaxX; ++x)
		{
			if (x < 0 || y < 0 || x >= 0x80 || y >= 0x80)
				continue;
			((SurfaceClass *)&surface)->rva008FCF40(x, y, status);
		}
	}
}
