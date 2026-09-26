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
