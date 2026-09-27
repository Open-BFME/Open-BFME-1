// ?initializeTiles@TerrainTiles006D2730@@QAEHHHPAVWorldHeightMap@@PAX@Z
// RVA 0x006D2730: full 576-byte body ending in ret 16.
// ZH FlatHeightMap::initHeightData establishes the tile-allocation algorithm.
// Keep address identity: BFME owner/signature is not asserted by this shim.
// BaseHeightMapRenderObjClass +0x2FF4 m_map and WorldHeightMap +8 m_width
// are layout witnesses; +0xC is only an observed extent here.
// The landed freeMapResources at 0x006D2690 independently witnesses
// tile storage +0x30D8 with 0xC4-byte elements and indices +0x30D4.
// The six address-named ILTs retain independently decoded callee identities.
// oldMap keeps the comparison input alive and recovers retail argument scheduling.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail calls the array allocator 0x00881F70 at both new[] sites.
void *__cdecl operator new[](unsigned int);

extern void j_0003a328(void);
extern void j_00014c5e(void);
extern void j_0003a82d(void);
extern void j_00047668(void);
extern void j_000225d4(void);
extern void j_0003902c(void);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

class WorldHeightMap
{
public:
    char m_unreconstructed[8];
    int m_width;
    int m_at0C;
};

class W3DTerrainBackground
{
public:
    W3DTerrainBackground();
    ~W3DTerrainBackground();
    void reset();
    void setFlip(WorldHeightMap *map);
    void allocateTerrainBuffers(WorldHeightMap *map, int x, int y, int width);
private:
    char m_body[0xc4];
};

class TerrainTiles006D2730
{
public:
    int initializeTiles(int x, int y, WorldHeightMap *map, void *lights);
    int freeMapResources();
private:
    char m_pad[0x2ff4];
    WorldHeightMap *m_map;
    char m_pad2[0x30d4 - 0x2ff8];
    short *m_flagArray;
    W3DTerrainBackground *m_tiles;
    int m_numTiles;
    int m_tilesWidth;
    int m_tilesHeight;
    char m_pad3[0x3174 - 0x30e8];
    char m_finalFlag;
};

union BaseCall {
    void (*f)();
    int (TerrainTiles006D2730::*m)(int, int, WorldHeightMap *, void *);
};
union MapCall {
    void (*f)();
    void (WorldHeightMap::*m)();
};
union TileCall0 {
    void (*f)();
    void (W3DTerrainBackground::*m)();
};
union TileCall1 {
    void (*f)();
    void (W3DTerrainBackground::*m)(WorldHeightMap *);
};
union TileCall4 {
    void (*f)();
    void (W3DTerrainBackground::*m)(WorldHeightMap *, int, int, int);
};
union FreeCall {
    void (*f)();
    int (TerrainTiles006D2730::*m)();
};

// ?initializeTiles@TerrainTiles006D2730@@QAEHHHPAVWorldHeightMap@@PAX@Z
int TerrainTiles006D2730::initializeTiles(int x, int y, WorldHeightMap *map, void *lights)
{
    BaseCall base;
    base.f = &j_0003a328;
    WorldHeightMap *oldMap = m_map;
    bool same = map == oldMap;
    (this->*base.m)(x, y, map, lights);
    int width = (map->m_width + 14) / 16;
    int height = (map->m_at0C + 14) / 16;
    int count = width * height;
    MapCall clear;
    clear.f = &j_00014c5e;
    (map->*clear.m)();
    if (same && m_tiles && m_tilesWidth == width && m_tilesHeight == height) {
        for (int i = 0; i < m_tilesWidth; ++i) {
            for (int j = 0; j < m_tilesHeight; ++j) {
                W3DTerrainBackground *tile = m_tiles + j * m_tilesWidth + i;
                TileCall0 reset;
                reset.f = &j_0003a82d;
                (tile->*reset.m)();
                TileCall1 flip;
                flip.f = &j_00047668;
                (tile->*flip.m)(map);
            }
        }
    } else {
        FreeCall freeCall;
        freeCall.f = &j_000225d4;
        (this->*freeCall.m)();
        m_tiles = new W3DTerrainBackground[count];
        m_numTiles = count;
        m_tilesWidth = width;
        m_tilesHeight = height;
        for (int i = 0; i < m_tilesWidth; ++i) {
            for (int j = 0; j < m_tilesHeight; ++j) {
                Sleep(0);
                W3DTerrainBackground *tile = m_tiles + j * m_tilesWidth + i;
                TileCall4 alloc;
                alloc.f = &j_0003902c;
                (tile->*alloc.m)(map, i * 16, j * 16, 16);
                TileCall1 flip;
                flip.f = &j_00047668;
                (tile->*flip.m)(map);
            }
        }
        m_flagArray = new short[count * 4];
    }
    m_finalFlag = 0;
    return 0;
}

// ?rva006D2480@Rva006D2480Owner@@QAEXPAVRenderInfoClass@@_N1PAH222@Z
// RVA 0x006D2480: 249-byte tile-state scan with conditional render (ret 0x1c).
// The three pushed call arguments are the first three stack slots (info,
// second, flag); the max slots are the last four. The emit call dispatches
// through the 0x000085F8 ILT to the matched W3DTerrainBackground::rva0072DC30
// (RenderInfoClass &, Bool, Bool) at 0x0072DC30.
class RenderInfoClass;
typedef bool Bool;
class Rva006D2480Tile
{
public:
	void rva0072DC30(RenderInfoClass &, Bool, Bool);
	int m_state;
	char m_pad[0x50];
	float m_54;
	char m_tail[0xc4 - 0x58];
};
extern void j_000085f8(void);
union Rva006D2480Call {
	void (*f)();
	void (Rva006D2480Tile::*m)(RenderInfoClass &, Bool, Bool);
};
class Rva006D2480Owner
{
public:
	void rva006D2480(RenderInfoClass *info, Bool second, Bool flag, int *maxX, int *maxA, int *maxY, int *maxB);
private:
	char m_pad[0x30d8];
	Rva006D2480Tile *m_tiles;
	int m_limit;
	int m_width;
	int m_height;
	char m_pad2[0x30f8 - 0x30e8];
	unsigned char m_flag;
	char m_pad3[3];
	int m_count;
	float m_heightF;
};
void Rva006D2480Owner::rva006D2480(RenderInfoClass *info, Bool second, Bool flag, int *maxX, int *maxA, int *maxY, int *maxB)
{
	int x = 0;
	int xOff = 0;
	if (m_width <= 0)
		return;
	for (; x < m_width; ++x, xOff += 0x10)
	{
		int y = 0;
		if (y >= m_height)
			continue;
		int yOff = 0;
		do
		{
			Rva006D2480Tile *tile = m_tiles + y * m_width + x;
			if (tile->m_state != 2)
			{
				if (m_flag == 0 || m_count >= m_limit || !(m_heightF < tile->m_54))
				{
					Rva006D2480Call emit;
					emit.f = &j_000085f8;
					(tile->*emit.m)(*info, second, flag);
					if (xOff < *maxX)
						*maxX = xOff;
					if (yOff < *maxY)
						*maxY = yOff;
					if (xOff + 0x10 > *maxA)
						*maxA = xOff + 0x10;
					if (yOff + 0x10 > *maxB)
						*maxB = yOff + 0x10;
				}
			}
			++y;
			yOff += 0x10;
		} while (y < m_height);
	}
}
