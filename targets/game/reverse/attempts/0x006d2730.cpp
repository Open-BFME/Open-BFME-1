// ?initializeTiles@Rva006D2730Owner@@QAEHHHPAVWorldHeightMap@@PAX@Z
// partial score=0.97 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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
    int m_xExtent;
    int m_yExtent;
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

class Rva006D2730Owner
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
    int (Rva006D2730Owner::*m)(int, int, WorldHeightMap *, void *);
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
    int (Rva006D2730Owner::*m)();
};

// ?initializeTiles@Rva006D2730Owner@@QAEHHHPAVWorldHeightMap@@PAX@Z
int Rva006D2730Owner::initializeTiles(int x, int y, WorldHeightMap *map, void *lights)
{
    BaseCall base;
    base.f = &j_0003a328;
    bool same = (map == m_map);
    (this->*base.m)(x, y, map, lights);
    int width = (map->m_xExtent + 14) / 16;
    int height = (map->m_yExtent + 14) / 16;
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
