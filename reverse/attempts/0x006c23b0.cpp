// ?refreshCells@Rva006C23B0@@QAEXHHH@Z
// partial score=0.3 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Revised from the saved 0x006C23B0 body using the current matched helper contracts.

class BfmeA1087;
extern BfmeA1087 *g_bfmeA1087;

struct Rva006C23B0Grid
{
	unsigned char pad00[0x10];
	float cellWidth;
	float cellHeight;
};

struct Rva006C23B0GlobalView
{
	unsigned char pad00[0x30b8];
	Rva006C23B0Grid *grid;
};

class Coord3D;
class ICoord2D;

class Radar
{
public:
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);
};

#pragma comment(linker, "/alternatename:?worldToRadar@Radar@@QAE_NPBUCoord3D@@PAUICoord2D@@@Z=?j_00026099@@YAXXZ")

class Rva00106F20Radar
{
public:
	void computeAspect(float *xRatio, float *yRatio);

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

#pragma comment(linker, "/alternatename:?computeAspect@Rva00106F20Radar@@QAEXPAM0@Z=?j_0000827e@@YAXXZ")

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

private:
	void *surface;
};

typedef char CheckResetSurfaceSize[sizeof(W3DRadarResetSurface) == 4 ? 1 : -1];

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel();

private:
	void *texture;
};

typedef char CheckResetTextureSize[sizeof(W3DRadarResetTexture) == 4 ? 1 : -1];

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

private:
	void *D3DSurface;
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
extern const float g_bfmeK1253;

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

class Rva006C23B0
{
public:
	void refreshCells(int cellX, int cellY, int status);

private:
	unsigned char pad00[0x1494];
	W3DRadarResetTexture texture;
};

void Rva006C23B0::refreshCells(int cellX, int cellY, int status)
{
	BfmeA1087 *global = g_bfmeA1087;
	Rva006C23B0Grid *grid = 0;
	if (global != 0)
		grid = ((Rva006C23B0GlobalView *)global)->grid;
	if (grid == 0)
		return;

	Rva006C23B0Lock lock;

	W3DRadarResetSurface surface = texture.getSurfaceLevel();

	int mapMinX = (int)(grid->cellWidth * (float)cellX);
	int mapMinY = (int)(grid->cellHeight * (float)cellY);
	int mapMaxX = (int)(grid->cellWidth * (float)(cellX + 1));
	int mapMaxY = (int)(grid->cellHeight * (float)(cellY + 1));

	Rva006C23B0WorldPoint world;
	Rva006C23B0RadarPoint radar;
	Radar *radarThis = (Radar *)this;
	world.x = (float)mapMinX;
	world.y = (float)mapMinY;
	radarThis->worldToRadar((const Coord3D *)&world, (ICoord2D *)&radar);
	int radarMinX = radar.x;
	int radarMinY = radar.y;

	world.x = (float)mapMaxX;
	world.y = (float)mapMaxY;
	radarThis->worldToRadar((const Coord3D *)&world, (ICoord2D *)&radar);
	int radarMaxX = radar.x;
	int radarMaxY = radar.y;

	float xRatio;
	float yRatio;
	((Rva00106F20Radar *)this)->computeAspect(&xRatio, &yRatio);

	if (xRatio > yRatio)
	{
		radarMinY = (int)(radarMinY * yRatio);
		radarMaxY = (int)(radarMaxY * yRatio);
		int north = ((BfmeThingGN *)&texture)->bfmeAskGN();
		if (north < 0)
		{
			float correction = ((float)north + g_bfmeUint32Scale) *
				((g_bfmeDefaultBU - yRatio) * g_bfmeK1253);
			radarMinY = (int)(radarMinY + correction);
			radarMaxY = (int)(radarMaxY + correction);
		}
	}

	radarMinX = (int)(radarMinX * xRatio);
	radarMaxX = (int)(radarMaxX * xRatio);
	int east = ((BfmeThingEF *)&texture)->bfmeAskEF();
	if (east < 0)
	{
		float correction = ((float)east + g_bfmeUint32Scale) *
			((g_bfmeDefaultBU - xRatio) * g_bfmeK1253);
		radarMinX = (int)(radarMinX + correction);
		radarMaxX = (int)(radarMaxX + correction);
	}

	unsigned char alpha;
	if (status == 2)
		alpha = 0xff;
	else
		alpha = status == 1 ? 0x7f : 0;

	for (int y = radarMinY; y <= radarMaxY; ++y)
	{
		for (int x = radarMinX; x <= radarMaxX; ++x)
		{
			if (x < 0 || y < 0 || x >= 0x80 || y >= 0x80)
				continue;
			((SurfaceClass *)&surface)->rva008FCF40(x, y, alpha);
		}
	}

}
