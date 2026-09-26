// WorldHeightMap::getTerrainTexture, RVA 0x0074CFA0..0x0074D190 (496B).
// Matched alpha/edge getters name this call; WorldHeightMap.cpp supplies the
// literal and field sequence. BFME returns an owning four-byte handle.
// Retail EH states destroy handles at frame -0x58, -0x58 and -0x54.
// Native copy/assignment/destruction reproduces the three release lifetimes.
//
// RVA 0x00747400 is an existing 113B helper. Its complete noinline body must
// be visible here: it ignores the pointer parameter. VC7.1 then reuses the
// hidden return argument home for edgeHeight, exactly as retail does. The
// helper is kept address-named because the legacy render-state-list name
// does not prove its identity. Its emitted bytes are verified independently;
// this definition makes no additional coverage claim.
// RVA 0x0074CDD0 computes a triangle flip from terrain data; it is not the
// cached-bit getFlipState accessor in the Zero Hour header. Keep it opaque.

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "texture.h"
#include <stdio.h>

class WorldHeightMap;
class Rva0074CDD0
{
public:
    bool test(int, int);
};
class Rva00747400
{
public:
    int apply(int *);
};

class TerrainTextureRef
{
public:
    TerrainTextureRef() : m_p(0) {}
    TerrainTextureRef(const TerrainTextureRef &other) : m_p(other.m_p)
    {
        if (m_p) m_p->Add_Ref();
    }
    ~TerrainTextureRef()
    {
        if (m_p) m_p->Release_Ref();
    }
    TerrainTextureRef &operator=(const TerrainTextureRef &other)
    {
        if (other.m_p) other.m_p->Add_Ref();
        if (m_p) m_p->Release_Ref();
        m_p = other.m_p;
        return *this;
    }
    TextureBaseClass *m_p;
};

class Rva006D51B0 : public TerrainTextureRef
{
public:
    Rva006D51B0(unsigned, unsigned);
};

class BfmeSrcSJ;
class BfmeHostSJ : public TerrainTextureRef
{
public:
    BfmeHostSJ(BfmeSrcSJ *);
};

class Rva006D6050 : public TerrainTextureRef
{
public:
    Rva006D6050(int, int);
};

class Rva006D5390
{
public:
    int update(WorldHeightMap *);
};

class AlphaEdgeTextureClass
{
public:
    int update(WorldHeightMap *);
};

class WorldHeightMap
{
public:
    TerrainTextureRef getTerrainTexture();
private:
    char m_base[8];
    int m_width;
    int m_height;
    char m_gap10[0x18];
    unsigned char *m_cellFlipState;
    char m_gap2c[8];
    int m_flipStateWidth;
    char m_gap38[0x1208c];
    TerrainTextureRef m_terrainTex;
    int m_terrainTexHeight;
    TerrainTextureRef m_alphaTerrainTex;
    int m_alphaTexHeight;
    TerrainTextureRef m_alphaEdgeTex;
    int m_alphaEdgeHeight;
};


struct Rva00747400Tile
{
    char opaque[0x555C];
    int field555C;
    int field5560;
};

struct Rva00747400Class
{
    int field00;
    int field04;
    char opaque[0x20];
};

struct Rva00747400Fields
{
    char opaque00[0x9C];
    int count09C;
    int opaque0A0;
    Rva00747400Tile *items[0x2006];
    int count80BC;
    char opaque80C0[0x18];
    Rva00747400Class classes[1];
};

__declspec(noinline) int Rva00747400::apply(int *)
{
    Rva00747400Fields *fields = reinterpret_cast<Rva00747400Fields *>(this);
    for (int i=0; i<fields->count09C; ++i)
    {
        if (fields->items[i])
        {
            fields->items[i]->field555C = 2;
            fields->items[i]->field5560 = 2;
        }
    }
    for (int j=0; j<fields->count80BC; ++j)
    {
        fields->classes[j].field00 = 2;
        fields->classes[j].field04 = 2;
    }
    return 0x800;
}

TerrainTextureRef WorldHeightMap::getTerrainTexture()
{
    if (m_terrainTex.m_p == 0)
    {
        int edgeHeight;
        int height = reinterpret_cast<Rva00747400 *>(this)->apply(&edgeHeight);
        int pow2Height = 1;
        while (pow2Height < height)
            pow2Height *= 2;

        m_terrainTex = Rva006D51B0(pow2Height, 0x19);
        m_terrainTexHeight = reinterpret_cast<Rva006D5390 *>(&m_terrainTex)->update(this);
        char buf[64];
        sprintf(buf, "Base tex height %d\n", pow2Height);
        m_alphaTerrainTex = BfmeHostSJ(reinterpret_cast<BfmeSrcSJ *>(&m_terrainTex));

        pow2Height = 1;
        while (pow2Height < edgeHeight)
            pow2Height *= 2;
        m_alphaEdgeTex = Rva006D6050(pow2Height, 3);
        m_alphaEdgeHeight = reinterpret_cast<AlphaEdgeTextureClass *>(&m_alphaEdgeTex)->update(this);

        for (int y = 0; y < m_height - 1; ++y)
        {
            for (int x = 0; x < m_width - 1; ++x)
            {
                m_cellFlipState[y * m_flipStateWidth + (x >> 3)] |=
                    static_cast<unsigned char>(reinterpret_cast<Rva0074CDD0 *>(this)->test(x,y) << (x & 7));
            }
        }
    }
    return m_terrainTex;
}
